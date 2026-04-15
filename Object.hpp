#pragma once
#include <SFML/Graphics.hpp>
#include <vector>

// ...existing code...
class Object {
protected:
    sf::Vector2f position;
    sf::Vector2f vitesse;
    sf::Vector2f acceleration;
    sf::Color color;
    bool depandof;
    bool isMovable;

public:
    Object(float x, float y, sf::Color c = sf::Color::White, bool movable = true);
    Object(sf::Vector2f pos, sf::Color c = sf::Color::White, bool movable = true);
    virtual ~Object() = default;
    // Changement critique : on ne peut pas stocker des instances d'une classe abstraite (Object)
    // dans std::vector<Object>. On utilise donc des pointeurs vers Object pour les dépendances.
    virtual void update(float deltaTime, std::vector<Object*> dependancies = std::vector<Object*>());
    virtual void draw(sf::RenderWindow& window) const = 0;

    void applyForce(const sf::Vector2f& force);
    sf::Vector2f getPosition() const;
    void setPosition(float x, float y);
    sf::Vector2f getVitesse() const;
    void setVitesse(float vx, float vy);
    void setColor(const sf::Color& c) { color = c; }
    sf::Color getColor() const { return color; }

    void setMovable(bool movable) { isMovable = movable; }
    bool getMovable() const { return isMovable; }
};