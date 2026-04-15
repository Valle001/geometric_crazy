#include "MPoint.hpp"

MPoint::MPoint(float x, float y, float r, sf::Color c, bool movable)
    : Object(x, y, c, movable), radius(r) {}

void MPoint::draw(sf::RenderWindow& window) const {
    sf::CircleShape shape(radius);
    shape.setPosition(position - sf::Vector2f(radius, radius));
    shape.setFillColor(color);
    window.draw(shape);
}
