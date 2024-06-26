#include "HealthPickup.hpp"

HealthPickup::HealthPickup(const sf::Vector2f& position, const std::string &texturePath){
    if(!texture.loadFromFile("heart.png")){
        throw std::runtime_error("Failed to load heart Image");
    }
    sprite.setTexture(texture);
    const float scale=20.0f;
    const sf::Vector2f offset={250.0f,0.0f};
    

    sprite.setScale(0.02f,0.02f);

    sf::Vector2f adjustedPos={position.x*scale+offset.x, position.y * 4.0f +offset.y};
    sprite.setPosition(adjustedPos);
}

void HealthPickup::draw(sf::RenderWindow& window) const{
    window.draw(sprite);
}

sf::FloatRect HealthPickup::getGlobalBounds() const{
    return sprite.getGlobalBounds();
}