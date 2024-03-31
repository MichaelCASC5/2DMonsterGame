#ifndef POWERUP_HPP
#define POWERUP_HPP

#include <SFML/Graphics.hpp>

enum class PowerUpType{
    SpeedBoost,
    RapidFire,
    DoubleScore
};

class PowerUp{
    public:
        PowerUp(PowerUpType, const sf::Vector2f& position, const std::string &texturePath);
        void draw(sf::RenderWindow& window) const;
        sf::FloatRect getGlobalBounds() const;
        PowerUpType getType() const;
    
    private:
        PowerUpType type;
        sf::Sprite sprite;
        sf::Texture texture;
};

#include "Powerup.cpp"
#endif