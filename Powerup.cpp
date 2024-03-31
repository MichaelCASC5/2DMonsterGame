#include "Powerup.hpp"

PowerUp::PowerUp(PowerUpType type, const sf::Vector2f& position, const std::string &texturePath):type(type){
    if(!texture.loadFromFile(texturePath)){
        throw std::runtime_error("Failed to load heart Image");
    }
    sprite.setTexture(texture);
    sprite.setPosition(position);
    sprite.setScale(0.02f,0.02f);

    switch (type)
    {
    case PowerUpType::SpeedBoost:
        sprite.setColor(sf::Color::Red);
        break;
    case PowerUpType::RapidFire:
        sprite.setColor(sf::Color::Green);
        break;
    case PowerUpType::DoubleScore:
        sprite.setColor(sf::Color::Blue);
        break;
    
    default:
        break;
    }
}

void PowerUp::draw(sf::RenderWindow& window) const{
    window.draw(sprite);
}

sf::FloatRect PowerUp::getGlobalBounds() const{
    return sprite.getGlobalBounds();
}

PowerUpType PowerUp::getType() const {
    return type;
}