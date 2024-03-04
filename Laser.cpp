#include "Laser.hpp"
#include <cmath>
Laser::Laser(const sf::Vector2f& position, float rotation, float speed): speed(speed){
    shape.setSize(sf::Vector2f(10.f,2.f));
    shape.setOrigin(shape.getSize().x/2, shape.getSize().y/2);
    shape.setPosition(position);
    shape.setRotation(rotation);
    shape.setFillColor(sf::Color::Blue);
}

void Laser::Update(){
    float angle=shape.getRotation()*3.14159f/180.f; //radians
    shape.move(speed*cos(angle), speed*sin(angle));
}

void Laser::draw(sf::RenderWindow& window){
    window.draw(shape);
}

bool Laser::offScreen(const sf::RenderWindow & window) const{
    sf::Vector2f position = shape.getPosition();
    return position.x <0 || position.x>window.getSize().x ||
           position.y<0  || position.y >window.getSize().y;
}