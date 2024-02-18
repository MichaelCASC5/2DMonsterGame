/**
 * COMPUTER SCIENCE 49900 MAJOR CAPSTONE HUNTER 2024
 *
 * 2D MONSTER GAME
 * CREATED BY ANTON, ANGELA, MICHAEL
 * 01/30/24 Spring Semester
 */

//External library include
#include <SFML/Graphics.hpp>

//Classes include
#include "Vertex.hpp"
#include "Maze.hpp"
#include "Player.hpp"
#include "Map.hpp"
#include "Bot.hpp"
#include "Timer.hpp"

//C include
#include <iostream>

int main() {
    //Create a maze and build it
    Maze maze(16, 16);
    maze.buildMaze();

    //Create a bot, build its path, and set it
    Bot bot;
    std::vector<Vertex> path = {
        Vertex(10, 10),
        Vertex(20, 2),
        Vertex(5, 5),
        Vertex(2, 20)
    };
    bot.setPath(path);

    //Create a map
    Map map;

    //Make a Player position, size
    Player player(sf::Vector2f(100.0f,100.0f));
    player.loadSprite("slime1.png");
    



    /**
     * SFML 2D LIBRARY GRAPHICS SETUP
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

    //Initiaziaze timer
    Timer Timers(30);

    //Keep the window open
    while (window.isOpen()) {
        sf::Event event;
        //Escape closes the window and spacebar generates a new maze
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            } 
            
            else if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape) {
                window.close();
            } else if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Space) {
                maze.buildMaze();
            }



        
            
        }

        Timers.update();
    
        //Player can move
        player.handleMovement();
        player.handleRotation();
        bot.move();
        
        //Clear the window
        window.clear();

   


        /**
         * GAME DISPLAY
         * 
         * 
         */
        //Draw the maze
        maze.draw(window);
        player.drawPlayer(window);
        bot.draw(window);
        Timers.draw(window);
        map.draw(window);

        //Display the window
        window.display();
    }

    return 0;
}