// This interface file simply specifies the class’s functions and structure (the ‘what’)

// Tells the compiler to read the file once and compile it, ignoring subsequent reads
#pragma once

#include <SFML/Graphics.hpp>

class Particle {
private:
    sf::Vector2f currentPosition;
    sf::Vector2f currentVelocity;
    sf::CircleShape graphicShape;
    float collisionRadius;

public:
    // Constructor and Destructor
    Particle(float initialX, float initialY, float initialVelocityX, float initialVelocityY);
    ~Particle();

    // Logical methods
    void applyForce(const sf::Vector2f& appliedForce);
    void updatePosition(float deltaTimeSeconds);
    void bounceOnXAxis(float energyRetentionFactor = 0.7f);
    void bounceOnYAxis(float energyRetentionFactor = 0.7f);

    // Constant getters for rendering and collisions
    // Const - correctness: first 'const' protects the data returned by the function
    // second 'const' protects the class's internal data (currentPosition, currentVelocity...)
    const sf::Vector2f& getPosition() const;
    const sf::CircleShape& getShape() const;
    const sf::Vector2f& getVelocity() const;
    float getRadius() const;

    // Setters for changing position
    void setPosition(const sf::Vector2f& newPosition);
};