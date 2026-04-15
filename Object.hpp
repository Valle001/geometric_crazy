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
    // Ajout d'un paramètre par défaut pour permettre les appels sans dépendances.
    // On garde le passage par valeur (comme dans la version originale) pour éviter
    // d'introduire des incompatibilités avec le reste du code.
    virtual void update(float deltaTime, std::vector<Object> dependancies = std::vector<Object>());
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