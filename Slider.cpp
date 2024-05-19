#include <SFML/Graphics.hpp>
#include "Slider.hpp"

//constructor slider position, size
Slider::Slider(float x, float y, float w, float h){
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