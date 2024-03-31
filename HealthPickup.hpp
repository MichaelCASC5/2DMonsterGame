#ifndef HEALTH_PICKUP_HPP
#define HEALTH_PICKUP_HPP

#include <SFML/Graphics.hpp>

class HealthPickup{
    public:
        HealthPickup(const sf::Vector2f& position, const std::string &texturePath);
        void draw(sf::RenderWindow& window) const;
        sf::FloatRect getGlobalBounds() const;

    private:
        sf::Sprite sprite;
        sf::Texture texture;
};

#include "HealthPickup.cpp"
#endif