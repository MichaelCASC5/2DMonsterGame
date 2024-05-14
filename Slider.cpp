#include <SFML/Graphics.hpp>
#include "Slider.hpp"

//constructor slider position, size
Slider::Slider(float x, float y, float w, float h){
    // //slider position, size
    // track.setSize(sf::Vector2f(w,h));
    // track.setPosition(x,y);
    // track.setFillColor(sf::Color::White);
    // //size, position slider handle
    // handle.setRadius(h/2);
    // handle.setPosition(x-handle.getRadius(), y-handle.getRadius()/2);
    // handle.setFillColor(sf::Color::Red);

    //slider value, dragging state
    value=0.0f;
    isDrag=false;
}

//draw slider on widnow
void Slider::draw(sf::RenderWindow &window){
    window.draw(track);
    window.draw(handle);
}

//return current value of slider
float Slider::getValue() const {
    return value;
}