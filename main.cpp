#include <SFML/Graphics.hpp>
#include <vector>
#include <memory>
#include <chrono>
#include "MPoint.hpp"
#include "Line.hpp" // Now contains Line
#include "PhysicsEngine.hpp"

int main() {
    int maxFPS = 120;
    sf::RenderWindow window(sf::VideoMode(800, 600), "App0");
    window.setFramerateLimit(60);

    std::vector<MPoint> MPoints;
    MPoints.push_back(MPoint(100, 100, 5, sf::Color::Red));
    MPoints.push_back(MPoint(20, 200, 5, sf::Color::Blue));
    MPoints.push_back(MPoint(100, 100, 5, sf::Color::Red));
    MPoints.push_back(MPoint(20, 200, 5, sf::Color::Blue));
    MPoints.push_back(MPoint(500, 100, 5, sf::Color::Red));
    MPoints.push_back(MPoint(260, 200, 5, sf::Color::White));

    std::vector<Line> lines;
    lines.push_back(Line(&MPoints[0],&MPoints[1], 2, sf::Color::Green, true));
    lines.push_back(Line(&MPoints[2],&MPoints[3], 4, sf::Color::Green, true));
    lines.push_back(Line(&MPoints[4],&MPoints[5], 4, sf::Color::Green, true));

    // Donne une vitesse initiale à certains objets
    MPoints[0].setVitesse(1, -0.5f);
    MPoints[1].setVitesse(1, 2);
    MPoints[2].setVitesse(-1, 1);
    MPoints[3].setVitesse(0, 0);
    MPoints[4].setVitesse(2, -2);
    MPoints[5].setVitesse(1, 2);


    

    PhysicsEngine physics(sf::Vector2f(0, 0));
    while (window.isOpen()) 
    {  
  
        static auto lastTime = std::chrono::high_resolution_clock::now();
        auto currentTime = std::chrono::high_resolution_clock::now();
        double elapsed = std::chrono::duration_cast<std::chrono::microseconds>(currentTime - lastTime).count() / 1e6;

        if (elapsed >= 1.0 / maxFPS)
        {
            lastTime = currentTime;

            sf::Event event;
            while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
            }

            float deltaTime = elapsed;

            physics.updateMPoints(MPoints, deltaTime);
            physics.updateLines(lines, deltaTime);

            window.clear(sf::Color::Black);

            for (const auto& obj : MPoints)
            obj.draw(window);

            for (const auto& obj : lines)
            obj.draw(window);

            window.display();
        }
    }

    return 0;
}