#ifndef LASER_HPP
#define LASER_HPP

#include <SFML/Graphics.hpp>

class Laser{
    public:
        Laser(const sf::Vector2f& position, float rotation, float speed);

        void Update();
        void draw(sf::RenderWindow& window);

        bool offScreen(const sf::RenderWindow & window) const;
    
    private:
        sf::RectangleShape shape;
        float speed;
};

#include "Laser.cpp"
#endif