#pragma once
#include <vector>
#include <memory>
#include "Object.hpp"
#include "MPoint.hpp"
#include "Line.hpp"
#include <SFML/Graphics.hpp>

class PhysicsEngine {
    float gravityStrenght = 0.0f;// 100, pour l'instant j'essaie juste d'afficher
    sf::Vector2f gravity;
    float friction = 0.8f; // Coefficient de friction pour simuler la résistance de l'air
public:
    PhysicsEngine(const sf::Vector2f& g = sf::Vector2f(0, 98.1f)) : gravity(g) {}
    void setGravityStrenght(const float g) { gravityStrenght = g; }
    void updateMPoints(std::vector<MPoint>& objects, float deltaTime);
    void updateLines(std::vector<Line>& objects, float deltaTime);

};
