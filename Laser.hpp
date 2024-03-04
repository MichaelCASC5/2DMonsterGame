#ifndef LASER_HPP
#define LASER_HPP

#include <SFML/Graphics.hpp>

class Laser{
    public:
        //constructor new laser with position, rotation, speed
        Laser(const sf::Vector2f& position, float rotation, float speed);
        //update laser constructor
        void Update();
        //draws laser
        void draw(sf::RenderWindow& window);
        //chekc if laser is off screen then return a boolean
        bool offScreen(const sf::RenderWindow & window) const;
    
    private:
        sf::RectangleShape shape; //laser
        float speed; //speed
};

#include "Laser.cpp"
#endif
