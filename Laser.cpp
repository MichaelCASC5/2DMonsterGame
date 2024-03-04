#include "Laser.hpp"

//utuilized resources from SFML docs https://www.sfml-dev.org/learn.php

#include <cmath>

//laser with position, rotation, speed
Laser::Laser(const sf::Vector2f& position, float rotation, float speed): speed(speed){
    shape.setSize(sf::Vector2f(10.f,2.f)); //size of laser
    shape.setOrigin(shape.getSize().x/2, shape.getSize().y/2); //origin of laser
    shape.setPosition(position);
    shape.setRotation(rotation);
    shape.setFillColor(sf::Color::Blue);
}

//update laser with speed, direction
void Laser::Update(){
    float angle=shape.getRotation()*3.14159f/180.f; //change rotation angle to radians
    shape.move(speed*cos(angle), speed*sin(angle)); //move the laser in direction its pointing
}

//draw laser in sfml
void Laser::draw(sf::RenderWindow& window){
    window.draw(shape);
}

//check if ofscreen
bool Laser::offScreen(const sf::RenderWindow & window) const{
    sf::Vector2f position = shape.getPosition();
    //returns true if laser is offscreen
    return position.x <0 || position.x>window.getSize().x ||
           position.y<0  || position.y >window.getSize().y;
}
