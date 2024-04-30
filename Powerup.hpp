#ifndef POWERUP_HPP
#define POWERUP_HPP

#include <SFML/Graphics.hpp>

enum class PowerUpType{
    SpeedBoost,
    RapidFire,
    DoubleScore,
    HealthBoost
};

class PowerUp{
    public:
        PowerUp(PowerUpType, const sf::Vector2f& position);
        void draw(sf::RenderWindow& window) const;
        sf::FloatRect getGlobalBounds() const;
        PowerUpType getType() const;
    
    private:
        PowerUpType type;
        sf::CircleShape circle;
};

#include "Powerup.cpp"
#endif