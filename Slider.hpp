#ifndef SLIDER_HPP
#define SLIDER_HPP

#include <SFML/Graphics.hpp>

class Slider{
    public:
        //Slider constructor
        Slider(float x, float y, float w, float h);
        void draw(sf::RenderWindow &window);
        float getValue() const;

    private:
        sf::RectangleShape track;
        sf::CircleShape handle;
        bool isDrag;
        float value;
};

#include "Slider.cpp"
#endif
