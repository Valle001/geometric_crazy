#include "Line.hpp"
#include "MPoint.hpp"
#include "Object.hpp"
#include <cmath>
#include <vector>
#include <queue>
#include <unordered_set>

Line::Line(MPoint* MPoint1, MPoint* MPoint2, float t, sf::Color c, bool movable)
    : Object(MPoint1->getPosition(), c , movable), _MPoint1(MPoint1), _MPoint2(MPoint2)
{
    // On enregistre la ligne dans les MPoints (la méthode MPoint::addLine prend un Line&, d'après le code existant).
    _MPoint1->addLine(*this);
    _MPoint2->addLine(*this);

    end = _MPoint2->getPosition();
    thickness = t;

    // Calcul de la longueur initiale entre les deux MPoints
    lenght = std::sqrt(std::pow(end.x - position.x, 2) + std::pow(end.y - position.y, 2));
}

void Line::draw(sf::RenderWindow& window) const {
    sf::Vertex line[] = {
        sf::Vertex(position, color),
        sf::Vertex(end, color)
    };
    // On dessine avec 2 vertices (début et fin).
    window.draw(line, 2, sf::Lines);
}

// Implémentation BFS pour récupérer tous les MPoints reliés au point de départ.
// On itère sur cur->getLines() qui retourne des Object* ; on cast dynamiquement en Line*.
std::vector<MPoint*> Line::getAllRelatedMPoints(MPoint* start, Line* alreadyGet) {
    std::vector<MPoint*> relatedMPoints;
    if (start == nullptr) return relatedMPoints;

    std::queue<MPoint*> q;
    std::unordered_set<MPoint*> visited;

    q.push(start);
    visited.insert(start);

    while (!q.empty()) {
        MPoint* cur = q.front();
        q.pop();
        relatedMPoints.push_back(cur);

        // Parcours des lignes (stockées comme Object*) attachées au MPoint courant
        for (Object* objLine : cur->getLines()) {
            Line* l = dynamic_cast<Line*>(objLine);
            if (!l) continue;              // ce n'est pas une Line
            if (l == alreadyGet) continue; // ignorer la ligne fournie si nécessaire

            // Pour chaque MPoint connecté par la ligne, l'ajouter si non visité.
            for (MPoint* p : l->getMPoints()) {
                if (!p) continue;
                if (visited.find(p) == visited.end()) {
                    visited.insert(p);
                    q.push(p);
                }
            }
        }
    }

    return relatedMPoints;
}

void Line::update(float deltaTime, std::vector<Object*> dependancies) {
    // Appel à la logique de base (position/vitesse) puis synchronisation des extrémités.
    Object::update(deltaTime, dependancies);
    position = _MPoint1->getPosition();
    end = _MPoint2->getPosition();
}

// Retourne les deux MPoints liés par la ligne.
std::vector<MPoint*> Line::getMPoints() const {
    return std::vector<MPoint*>{ _MPoint1, _MPoint2 };
}