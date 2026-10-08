/// \file main.cpp
/// \brief Entry point per la simulazione del motore fisico 2D.
/// \author Eugenio Schiera
/// \date Latest modified 19\01\2026
///
/// This file contains the main simulation loop, particle definitions,
/// and collision resolution logic.

#include <SFML/Graphics.hpp>
#include <vector>
#include <cmath>
#include "Particle.hpp"
#include "MathUtils.hpp"

void solveCollisions(std::vector<Particle>& particles) {
    for (size_t i = 0; i < particles.size(); ++i) {
        for (size_t j = i + 1; j < particles.size(); ++j) {
            Particle& firstParticle = particles[i];
            Particle& secondParticle = particles[j];

            // 1. Distance calculation
            sf::Vector2f vectorBetweenCenters = firstParticle.getPosition() - secondParticle.getPosition();
            float squaredDistance = vectorBetweenCenters.x * vectorBetweenCenters.x + vectorBetweenCenters.y * vectorBetweenCenters.y;
            float minimumDistanceForCollision = firstParticle.getRadius() + secondParticle.getRadius();
            
            // Collision detection
            if (squaredDistance < minimumDistanceForCollision * minimumDistanceForCollision) {
                float actualDistance = std::sqrt(squaredDistance);
                if (actualDistance == 0.0f) continue;

                // --- 1. STATIC RESOLUTION (Separation) ---
                float penetrationDepth = minimumDistanceForCollision - actualDistance;
                sf::Vector2f collisionNormal = vectorBetweenCenters / actualDistance; 
                
                // Move particles apart
                firstParticle.setPosition(firstParticle.getPosition() + collisionNormal * (penetrationDepth * 0.5f));
                secondParticle.setPosition(secondParticle.getPosition() - collisionNormal * (penetrationDepth * 0.5f));

                // --- 2. DYNAMIC RESOLUTION (Real Impulse) ---
                sf::Vector2f relativeVelocity = firstParticle.getVelocity() - secondParticle.getVelocity();
                float velocityAlongNormal = dotProduct(relativeVelocity, collisionNormal);

                // Prevent "sticky particles"
                if (velocityAlongNormal > 0) continue;

                float coefficientOfRestitution = 0.75f; 

                // Calculate scalar impulse
                float scalarImpulse = -(1.0f + coefficientOfRestitution) * velocityAlongNormal;
                scalarImpulse /= 2.0f; // Assuming equal masses

                // Apply the impulse
                sf::Vector2f impulseVector = collisionNormal * scalarImpulse;
                firstParticle.applyForce(impulseVector);
                secondParticle.applyForce(-impulseVector);
            }
        }
    }
}

int main() {
    sf::RenderWindow window(sf::VideoMode(800, 600), "Physics Engine: Collisions");
    window.setFramerateLimit(60);

    std::vector<Particle> particles;
    sf::Vector2f gravity(0.0f, 1000.0f);
    sf::Clock clock;

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) window.close();
            
            if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
                float mousePositionX = static_cast<float>(event.mouseButton.x);
                float mousePositionY = static_cast<float>(event.mouseButton.y);
                particles.emplace_back(mousePositionX, mousePositionY, (rand()%200)-100.f, (rand()%200)-100.f);
            }
        }

        sf::Time frameDeltaTime = clock.restart();
        float deltaTimeSeconds = frameDeltaTime.asSeconds();

        // --- UPDATE ---
        for (auto& currentParticle : particles) {
            currentParticle.applyForce(gravity * deltaTimeSeconds);
            currentParticle.updatePosition(deltaTimeSeconds);

            sf::Vector2f currentPosition = currentParticle.getPosition();

            // Wall collisions
            if (currentPosition.y > 590.f) { 
                currentParticle.setPosition({currentPosition.x, 590.f});
                currentParticle.bounceOnYAxis();
            }
            if (currentPosition.x < 10.f)  { 
                currentParticle.setPosition({10.f, currentPosition.y});
                currentParticle.bounceOnXAxis();
            }
            if (currentPosition.x > 790.f) { 
                currentParticle.setPosition({790.f, currentPosition.y}); 
                currentParticle.bounceOnXAxis(); 
            }
        }

        solveCollisions(particles);

        window.clear(sf::Color::Black);
        for (const auto& currentParticle : particles) {
            window.draw(currentParticle.getShape());
        }
        window.display();
    }
    return 0;
}