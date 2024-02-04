/**
    * COMPUTER SCIENCE 49900 MAJOR CAPSTONE HUNTER 2024
    *
    * 2D MONSTER GAME
    * CREATED BY ___LIST ALL YOUR NAMES HERE___
    * 01/30/24 Spring Semester
*/

//External library include
#include <SFML/Graphics.hpp>

//Classes include
#include "Vertex.hpp"
#include "Maze.hpp"

//C include
#include <iostream>

int main() {
    //Create a maze and build it
    Maze maze(16, 16);
    maze.buildMaze();



    /**
        * SFML 2D GRAPHICS LIBRARY SETUP
        *
        *
    */
    //Set up window
    sf::RenderWindow window(sf::VideoMode::getDesktopMode(), "SFML works!", sf::Style::Fullscreen);

    //Enable VSync
    window.setVerticalSyncEnabled(true);
    
    //Gets the desktop resolution
    auto desktop = sf::VideoMode::getDesktopMode();

    //Display window before obtaining desktop
    window.display();

    //Short delay to allow window to be positioned properly
    sf::sleep(sf::milliseconds(100));

    //Center Screen
    sf::Vector2i position(desktop.width/2 - window.getSize().x/2, desktop.height/2 - window.getSize().y/2);
    window.setPosition(position);

    //Keep the window open
    while (window.isOpen()) {
        sf::Event event;
        //Escape closes the window and spacebar generates a new maze
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            } else if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape) {
                window.close();
            } else if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Space) {
                maze.buildMaze();
            }
        }

        //Clear the window
        window.clear();

        /**
            * GAME DISPLAY 
            *
            *
        */
        //Draw the maze
        maze.draw(window);

        //Display the window
        window.display();
    }

    return 0;
}