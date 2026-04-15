#pragma once
#include "Object.hpp"
//#include "Line.hpp"
#include <vector>

class MPoint : public Object {
protected:
    float radius;
    std::vector<Object*> relatedLines;
public:
    MPoint(float x, float y, float r = 3.0f, sf::Color c = sf::Color::White, bool movable = true);
    void draw(sf::RenderWindow& window) const override;
    void setRadius(float r) { radius = r; }
    float getRadius() const { return radius; }
    void addLine(Object &line) { relatedLines.push_back(&line);}
    std::vector<Object*> getLines() const {return relatedLines;}

};
