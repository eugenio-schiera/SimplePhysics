#include <gtest/gtest.h>
#include "../src/Particle.hpp"

TEST(ParticleTest, BounceOnXAxisCustomFactor) {
    Particle p(0.0f, 0.0f, 10.0f, 5.0f);
    p.bounceOnXAxis(0.8f);
    EXPECT_FLOAT_EQ(p.getVelocity().x, -8.0f);
    EXPECT_FLOAT_EQ(p.getVelocity().y, 5.0f);
}

TEST(ParticleTest, BounceOnYAxisCustomFactor) {
    Particle p(0.0f, 0.0f, 10.0f, 5.0f);
    p.bounceOnYAxis(0.5f);
    EXPECT_FLOAT_EQ(p.getVelocity().x, 10.0f);
    EXPECT_FLOAT_EQ(p.getVelocity().y, -2.5f);
}

TEST(ParticleTest, BounceOnXAxisDefaultFactor) {
    Particle p(0.0f, 0.0f, 10.0f, 5.0f);
    p.bounceOnXAxis(); // default is 0.7f
    EXPECT_FLOAT_EQ(p.getVelocity().x, -7.0f);
    EXPECT_FLOAT_EQ(p.getVelocity().y, 5.0f);
}

TEST(ParticleTest, BounceOnYAxisDefaultFactor) {
    Particle p(0.0f, 0.0f, 10.0f, 5.0f);
    p.bounceOnYAxis(); // default is 0.7f
    EXPECT_FLOAT_EQ(p.getVelocity().x, 10.0f);
    EXPECT_FLOAT_EQ(p.getVelocity().y, -3.5f);
}

TEST(ParticleTest, BounceOnXAxisZeroRetention) {
    Particle p(0.0f, 0.0f, 10.0f, 5.0f);
    p.bounceOnXAxis(0.0f);
    EXPECT_FLOAT_EQ(p.getVelocity().x, 0.0f);
    EXPECT_FLOAT_EQ(p.getVelocity().y, 5.0f);
}

TEST(ParticleTest, BounceOnYAxisZeroRetention) {
    Particle p(0.0f, 0.0f, 10.0f, 5.0f);
    p.bounceOnYAxis(0.0f);
    EXPECT_FLOAT_EQ(p.getVelocity().x, 10.0f);
    EXPECT_FLOAT_EQ(p.getVelocity().y, 0.0f);
}

TEST(ParticleTest, BounceOnXAxisExtremeNegativeRetention) {
    Particle p(0.0f, 0.0f, 10.0f, 5.0f);
    p.bounceOnXAxis(-2.0f); // multiplying by negative factor makes it positive, meaning it accelerates in same direction
    EXPECT_FLOAT_EQ(p.getVelocity().x, 20.0f);
    EXPECT_FLOAT_EQ(p.getVelocity().y, 5.0f);
}

TEST(ParticleTest, BounceOnYAxisExtremeNegativeRetention) {
    Particle p(0.0f, 0.0f, 10.0f, 5.0f);
    p.bounceOnYAxis(-3.0f);
    EXPECT_FLOAT_EQ(p.getVelocity().x, 10.0f);
    EXPECT_FLOAT_EQ(p.getVelocity().y, 15.0f);
}
