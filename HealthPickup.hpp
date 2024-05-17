#ifndef HEALTH_PICKUP_HPP
#define HEALTH_PICKUP_HPP

#include <SFML/Graphics.hpp>

class HealthPickup
{
public:
    // Constructor, position of initial position of health pickup
    HealthPickup(const sf::Vector2f &position, const std::string &texturePath);
    // draw health pickup on screen
    void draw(sf::RenderWindow &window) const;
    // get bounding box
    sf::FloatRect getGlobalBounds() const;

private:
    sf::Sprite sprite;
    sf::Texture texture;
};

#include "HealthPickup.cpp"
#endif