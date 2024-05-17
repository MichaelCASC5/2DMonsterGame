/**
 * COMPUTER SCIENCE 49900 MAJOR CAPSTONE HUNTER 2024
 *
 * 2D MONSTER GAME
 * CREATED BY ANTON, MICHAEL
 * 01/30/24 Spring Semester
 *
 */

#include "HealthPickup.hpp"

// constructor, position and image used for sprite.
HealthPickup::HealthPickup(const sf::Vector2f &position, const std::string &texturePath)
{
    // load texture from file
    if (!texture.loadFromFile("heart.png"))
    {
        throw std::runtime_error("Failed to load heart Image");
    }
    sprite.setTexture(texture);
    const float scale = 20.0f;
    const sf::Vector2f offset = {250.0f, 0.0f};

    // set scale, adjust position
    sprite.setScale(0.02f, 0.02f);
    sf::Vector2f adjustedPos = {position.x * scale + offset.x, position.y * 4.0f + offset.y};
    sprite.setPosition(adjustedPos);
}

// draw health pickups
void HealthPickup::draw(sf::RenderWindow &window) const
{
    window.draw(sprite);
}
// get global bounds for collision detection
sf::FloatRect HealthPickup::getGlobalBounds() const
{
    return sprite.getGlobalBounds();
}