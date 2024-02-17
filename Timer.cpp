#include "Timer.hpp"
#include <iostream>

Timer::Timer(unsigned int timer):timer(timer), finish(false){
    text.setFont(font);
    text.setCharacterSize(10);
    text.setFillColor(sf::Color::Red);
    text.setPosition(20,20);
}

void Timer::update(){
    sf::Time durationtook = clock.getElapsedTime();

    if(durationtook.asSeconds()>timer && !finish){
        int lefttime=timer-static_cast<int>(durationtook.asSeconds());
        text.setString("Time left: " +std::to_string(lefttime)+" seconds");
    }
    else if(!finish){
        text.setString("Ran out of Time");
        finish=true;
    }
}

void Timer::draw(sf::RenderWindow& window){
    window.draw(text);
}
