#include "Timer.hpp"
#include <iostream>

Timer::Timer(unsigned int timer):timer(timer), finish(false){
   if(!font.loadFromFile("Roboto-Bold.ttf")){
        std::cerr<<"Failed to load font"<<std::endl;
    }
    text.setFont(font);
    text.setString("Timer");
    text.setCharacterSize(30);
    text.setFillColor(sf::Color::Red);
    text.setPosition(450,30);
}

void Timer::update(){
    sf::Time durationtook = clock.getElapsedTime();
    
    if(durationtook.asSeconds()<timer){
        int lefttime=timer-static_cast<int>(durationtook.asSeconds());
        text.setString("Time Left: "+std::to_string(lefttime)+" seconds");
    }
    
    else if(!finish){
        text.setString("Ran out of Time");
        finish=true;
    }
}

void Timer::draw(sf::RenderWindow& window){
    window.draw(text);
}