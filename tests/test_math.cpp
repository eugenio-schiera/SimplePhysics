#include <gtest/gtest.h>
#include <SFML/System/Vector2.hpp>
#include "../src/MathUtils.hpp"

TEST(MathUtilsTest, DotProduct_PositiveValues) {
    sf::Vector2f v1(2.0f, 3.0f);
    sf::Vector2f v2(4.0f, 5.0f);
    EXPECT_FLOAT_EQ(dotProduct(v1, v2), 23.0f); // 2*4 + 3*5 = 8 + 15 = 23
}

TEST(MathUtilsTest, DotProduct_Orthogonal) {
    sf::Vector2f v1(1.0f, 0.0f);
    sf::Vector2f v2(0.0f, 1.0f);
    EXPECT_FLOAT_EQ(dotProduct(v1, v2), 0.0f);
}

TEST(MathUtilsTest, DotProduct_Zero) {
    sf::Vector2f v1(0.0f, 0.0f);
    sf::Vector2f v2(5.0f, 5.0f);
    EXPECT_FLOAT_EQ(dotProduct(v1, v2), 0.0f);
}

TEST(MathUtilsTest, DotProduct_NegativeValues) {
    sf::Vector2f v1(-2.0f, 3.0f);
    sf::Vector2f v2(4.0f, -5.0f);
    EXPECT_FLOAT_EQ(dotProduct(v1, v2), -23.0f); // -2*4 + 3*-5 = -8 - 15 = -23
}
