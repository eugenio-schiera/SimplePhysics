// This file implements the logic of the header – i.e. the interface (the ‘how’)

#include "Particle.hpp"

// Constructor with a member initialiser list: initialises the data BEFORE executing the body
// Much more efficient because the object is constructed directly with those values, rather than being created ...
// ... empty and then overwritten with an assignment.
Particle::Particle(float initialX, float initialY, float initialVelocityX, float initialVelocityY) 
    : currentPosition(initialX, initialY), currentVelocity(initialVelocityX, initialVelocityY), collisionRadius(10.f) 
{
    graphicShape.setRadius(collisionRadius);
    graphicShape.setFillColor(sf::Color::Cyan);
    graphicShape.setOrigin(collisionRadius, collisionRadius);
    graphicShape.setPosition(currentPosition);
}
// Destructor (empty because I don't use manual “new” statements, but it's important to have one)
Particle::~Particle() {}

void Particle::applyForce(const sf::Vector2f& appliedForce) { 
    currentVelocity += appliedForce; 
}
void Particle::updatePosition(float deltaTimeSeconds) {
    currentPosition += currentVelocity * deltaTimeSeconds;
    graphicShape.setPosition(currentPosition);
}
// Methods for bouncing off the edges of the screen
void Particle::bounceOnXAxis(float energyRetentionFactor) {
    currentVelocity.x *= -energyRetentionFactor;
}

void Particle::bounceOnYAxis(float energyRetentionFactor) {
    currentVelocity.y *= -energyRetentionFactor;
}

// Getters
const sf::Vector2f& Particle::getPosition() const { return currentPosition; }
const sf::CircleShape& Particle::getShape() const { return graphicShape; }
const sf::Vector2f& Particle::getVelocity() const { return currentVelocity; }
float Particle::getRadius() const { return collisionRadius; }
// Setters
// Update both the logic and the graphics
void Particle::setPosition(const sf::Vector2f& newPosition) { 
    currentPosition = newPosition; 
    graphicShape.setPosition(currentPosition); 
}