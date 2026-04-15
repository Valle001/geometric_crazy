#include "PhysicsEngine.hpp"


void PhysicsEngine::updateMPoints(std::vector<MPoint>& objects, float deltaTime)
{
    float xmoy = 0.0f;
    float ymoy = 0.0f;
    int count = 0;

    for (auto& obj : objects)
    {
        count ++;
        xmoy+= obj.getPosition().x;
        ymoy+= obj.getPosition().y;
    }

    xmoy /= count;
    ymoy /= count;
    gravity = sf::Vector2f((xmoy), (ymoy));

    for (auto& obj : objects) 
    {
        obj.applyForce((obj.getPosition() - gravity) * -0.01f * gravityStrenght); // Applique la gravité
        obj.setVitesse(obj.getVitesse().x * friction - 0.1f, obj.getVitesse().y * friction - 0.1f); // Simule une légère friction avec un - pour l'arret complet
        obj.update(deltaTime);
    }
}

void PhysicsEngine::updateLines(std::vector<Line>& objects, float deltaTime) 
{
    float xmoy = 0.0f;
    float ymoy = 0.0f;
    int count = 0;

    for (auto& obj : objects)
    {
        count ++;
        xmoy+= obj.getPosition().x;
        ymoy+= obj.getPosition().y;
    }

    xmoy /= count;
    ymoy /= count;
    gravity = sf::Vector2f((xmoy), (ymoy));

    for (auto& obj : objects) {
        obj.applyForce((obj.getPosition() - gravity) * -0.01f * gravityStrenght);
        obj.setVitesse(obj.getVitesse().x * friction - 0.1f, obj.getVitesse().y * friction - 0.1f); // Simule une légère friction avec un - pour l'arret complet
        obj.update(deltaTime);
    }
}

