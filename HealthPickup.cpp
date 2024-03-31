#include "HealthPickup.hpp"

HealthPickup::HealthPickup(const sf::Vector2f& position, const std::string &texturePath){
    if(!texture.loadFromFile("heart.png")){
        throw std::runtime_error("Failed to load heart Image");
    }
    sprite.setTexture(texture);
    sprite.setPosition(position);
    sprite.setScale(0.02f,0.02f);
}

void HealthPickup::draw(sf::RenderWindow& window) const{
    window.draw(sprite);
}

sf::FloatRect HealthPickup::getGlobalBounds() const{
    return sprite.getGlobalBounds();
}