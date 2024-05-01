#ifndef TIMER_HPP
#define TIMER_HPP

//utuilized resources from SFML docs https://www.sfml-dev.org/learn.php

#include <SFML/Graphics.hpp>
#include <string>

class Timer{
    public:
        //constructor of timer
        Timer(unsigned int timer);
        //update and draw timer
        void update();
        void draw(sf::RenderWindow& window);
        void reset(unsigned int newTime);
        
    private:
        sf::Clock clock;
        sf::Text text;
        sf::Font font;
        unsigned int timer;
        bool finish;
};

#include "Timer.cpp"
#endif
