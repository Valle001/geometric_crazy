#include "Object.hpp"
#include <vector>


Object::Object(float x, float y, sf::Color c, bool movable)
    : position(x, y), vitesse(0, 0), acceleration(0, 0), color(c), isMovable(movable) {}

Object::Object(sf::Vector2f pos, sf::Color c, bool movable)
    : position(pos), vitesse(0, 0), acceleration(0, 0), color(c), isMovable(movable) {}

// On garde la signature par valeur et on ajoute un comportement sûr pour le cas "sans dépendances".
// Utilisation de empty() pour clarifier l'intention (équivalent à la comparaison avec un vecteur vide).
void Object::update(float deltaTime, std::vector<Object*> dependancies) {
    // Si des dépendances sont fournies, on applique la logique de mouvement habituelle.
    if (!dependancies.empty()) {
        if (isMovable) {
            vitesse += acceleration * deltaTime;
            position += vitesse * deltaTime;
            acceleration = sf::Vector2f(0, 0); // Reset after applying
        }
    }
    else {
        // Sinon on calcule une "accélération moyenne" basée sur les dépendances (logique existante).
        sf::Vector2f accelerationMoy(acceleration);
        int length(1);

        for (auto* i: dependancies) {
            if (i) accelerationMoy += i->acceleration; // accès via pointeur
            length ++;
        }
        accelerationMoy.x /= static_cast<float>(length);
        accelerationMoy.y /= static_cast<float>(length);

        for (auto* i: dependancies) {
            if (i) i->acceleration = accelerationMoy; // mise à jour via pointeur
        }
    }
}

void Object::applyForce(const sf::Vector2f& force) {
    if (isMovable) {
        acceleration += force;
    }
}

sf::Vector2f Object::getPosition() const {
    return position;
}

void Object::setPosition(float x, float y) {
    position = sf::Vector2f(x, y);
}

sf::Vector2f Object::getVitesse() const {
    return vitesse;
}

void Object::setVitesse(float vx, float vy) {
    vitesse = sf::Vector2f(vx, vy);
}