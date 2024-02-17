#ifndef TIMER_HPP
#define TIMER_HPP

#include <SFML/Graphics.hpp>
#include <string>

class Timer{
    public:
        Timer(unsigned int timer);

        void update();
        void draw(sf::RenderWindow& window);
    
    private:
        sf::Clock clock;
        sf::Text text;
        sf::Font font;
        unsigned int timer;
        bool finish;
};

#include "Timer.cpp"
#endif