/**
 * COMPUTER SCIENCE 49900 MAJOR CAPSTONE HUNTER 2024
 *
 * 2D MONSTER GAME
 * CREATED BY ANTON, MICHAEL
 * 01/30/24 Spring Semester
 *
 */

#include "Timer.hpp"
#include <iostream>

// constrcutor for timer, Rovboto font, timer is text for now
Timer::Timer(unsigned int timer) : timer(timer), finish(false)
{
    // load font for timer text
    if (!font.loadFromFile("Roboto-Bold.ttf"))
    {
        std::cerr << "Failed to load font" << std::endl;
    }
    // text properties
    text.setFont(font);
    text.setString("Timer");
    text.setCharacterSize(30);
    text.setFillColor(sf::Color::Red);
    text.setPosition(1370, 10);
}

// update timer, starts from example 30seconds until 0 then "Ran out of Time":
void Timer::update()
{
    sf::Time durationtook = clock.getElapsedTime();

    if (durationtook.asSeconds() < timer)
    {
        int lefttime = timer - static_cast<int>(durationtook.asSeconds());
        text.setString("Time Left: " + std::to_string(lefttime) + " seconds");
    }

    else if (!finish)
    {
        text.setString("Ran out of Time");
        finish = true;
    }
}

// draw timer in game
void Timer::draw(sf::RenderWindow &window)
{
    window.draw(text);
}

// reset the timer
void Timer::reset(unsigned int newTime)
{
    timer = newTime;
    clock.restart();
    finish = false;
    text.setString("Time Left: " + std::to_string(timer) + " seconds");
}
