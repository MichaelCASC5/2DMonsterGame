/**
 * COMPUTER SCIENCE 49900 MAJOR CAPSTONE HUNTER 2024
 *
 * 2D MONSTER GAME
 * CREATED BY ANTON, MICHAEL
 * 01/30/24 Spring Semester
 *
 * // utuilized resources from SFML docs https://www.sfml-dev.org/learn.php
 */

#include "Laser.hpp"

#include <cmath>
#include <random>

// laser with position, rotation, speed
Laser::Laser(const sf::Vector2f &position, float rotation, float speed) : speed(speed)
{

    // used this reosource for random color generator
    //  https://stackoverflow.com/questions/19665818/generate-random-numbers-using-c11-random-library

    std::random_device rd;                         // random number form hardware
    std::mt19937 eng(rd());                        // seed generator
    std::uniform_int_distribution<> distr(0, 255); // range

    // generates randopm color
    sf::Color randomColor(distr(eng), distr(eng), distr(eng));

    shape.setSize(sf::Vector2f(10.f, 2.f));                        // size of laser
    shape.setOrigin(shape.getSize().x / 2, shape.getSize().y / 2); // origin of laser
    shape.setPosition(position);
    shape.setRotation(rotation);
    shape.setFillColor(randomColor);
}

// update laser with speed, direction
void Laser::Update()
{
    float angle = shape.getRotation() * 3.14159f / 180.f; // change rotation angle to radians
    shape.move(speed * cos(angle), speed * sin(angle));   // move the laser in direction its pointing
}

// draw laser in sfmls
void Laser::draw(sf::RenderWindow &window)
{
    window.draw(shape);
}

// check if ofscreen
bool Laser::offScreen(const sf::RenderWindow &window) const
{
    sf::Vector2f position = shape.getPosition();
    // returns true if laser is offscreen
    return position.x < 0 || position.x > window.getSize().x ||
           position.y < 0 || position.y > window.getSize().y;
}

// get bounding box of laser
sf::FloatRect Laser::getBounds() const
{
    return shape.getGlobalBounds();
}
