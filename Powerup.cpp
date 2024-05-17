

#include "Powerup.hpp"

PowerUp::PowerUp(PowerUpType type, const sf::Vector2f &position) : type(type)
{
    circle.setRadius(5.0f);
    circle.setPosition(position);

    // set fill color based on type of powerup
    switch (type)
    {
    case PowerUpType::SpeedBoost:
        circle.setFillColor(sf::Color::Red);
        break;
    case PowerUpType::RapidFire:
        circle.setFillColor(sf::Color::Green);
        break;
    case PowerUpType::DoubleScore:
        circle.setFillColor(sf::Color::Blue);
        break;
    case PowerUpType::HealthBoost:
        circle.setFillColor(sf::Color::Yellow);
        break;

    default:
        break;
    }

    // set outline, thickness of powerups
    circle.setOutlineColor(sf::Color::White);
    circle.setOutlineThickness(2.0f);
}

// draw powerup
void PowerUp::draw(sf::RenderWindow &window) const
{
    window.draw(circle);
}

// get global bounds for collision
sf::FloatRect PowerUp::getGlobalBounds() const
{
    return circle.getGlobalBounds();
}

// get type of powerup
PowerUpType PowerUp::getType() const
{
    return type;
}