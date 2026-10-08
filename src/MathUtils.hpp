#pragma once
#include <SFML/System/Vector2.hpp>

inline float dotProduct(const sf::Vector2f& firstVector, const sf::Vector2f& secondVector) {
    return firstVector.x * secondVector.x + firstVector.y * secondVector.y;
}
