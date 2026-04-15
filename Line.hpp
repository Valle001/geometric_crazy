#pragma once
#include "MPoint.hpp"
#include "Object.hpp"
#include <cmath>
#include <vector>

class Line : public Object {
protected:
    MPoint* _MPoint1;
    MPoint* _MPoint2;
    sf::Vector2f end;
    float thickness;
    float lenght;
    const float ecartRegulation = 0.7f; // l'écart est calculé comme si c = a + b...

public:
    Line(MPoint* MPoint1, MPoint* MPoint2, float t, sf::Color c = sf::Color::White, bool movable = true);
    void draw(sf::RenderWindow& window) const override;
    // Signature alignée avec Object::update : vecteur de pointeurs vers Object.
    void update(float deltaTime, std::vector<Object*> dependancies = std::vector<Object*>()) override;
    // Retourne les deux MPoints reliés par cette ligne.
    std::vector<MPoint*> getMPoints() const;
    // Retourne tous les MPoints connectés (directement ou indirectement) au MPoint 'start'.
    static std::vector<MPoint*> getAllRelatedMPoints(MPoint* start, Line* alreadyGet = nullptr);
    void setEnd(float x, float y) { end = sf::Vector2f(x, y); }
    sf::Vector2f getEnd() const { return end; }
    void setThickness(float t) { thickness = t; }
    float getThickness() const { return thickness; }
};
