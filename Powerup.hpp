/**
 * COMPUTER SCIENCE 49900 MAJOR CAPSTONE HUNTER 2024
 *
 * 2D MONSTER GAME
 * CREATED BY ANTON, MICHAEL
 * 01/30/24 Spring Semester
 *
 */

#ifndef POWERUP_HPP
#define POWERUP_HPP

#include <SFML/Graphics.hpp>

// enumerations for different types of powerUps
enum class PowerUpType
{
    SpeedBoost,
    RapidFire,
    DoubleScore,
    HealthBoost
};

class PowerUp
{
public:
    // Constructor for Powerup, type of powerUp and position of powerup in map
    PowerUp(PowerUpType, const sf::Vector2f &position);
    // draw power up on screen
    void draw(sf::RenderWindow &window) const;
    // get global bounds of power up for collision
    sf::FloatRect getGlobalBounds() const;
    // get type of power up
    PowerUpType getType() const;

private:
    // type of powerup
    PowerUpType type;
    // shape
    sf::CircleShape circle;
};

#include "Powerup.cpp"
#endif