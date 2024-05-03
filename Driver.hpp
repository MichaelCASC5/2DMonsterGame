/**
 * COMPUTER SCIENCE 49900 MAJOR CAPSTONE HUNTER 2024
 *
 * 2D MONSTER GAME
 * CREATED BY ANTON, ANGELA, MICHAEL
 * 01/30/24 Spring Semester
 * 
 * THIS IS THE DRIVER FOR THE GAME.
 * Some code is taken from the SFML tutorial page
 * https://www.sfml-dev.org/tutorials/2.6/start-linux.php
 */

#ifndef DRIVER_HPP
#define DRIVER_HPP

//External library include
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

//Classes include
#include "Vertex.hpp"
#include "Maze.hpp"
#include "Player.hpp"
#include "Map.hpp"
#include "Bot.hpp"
#include "Timer.hpp"
#include "Lives.hpp"
#include "Laser.hpp"
#include "Slider.hpp"
#include "Enemy.hpp"
#include "HealthPickup.hpp"
#include "Powerup.hpp"
#include "Camera.hpp"

//C include
#include <iostream>
#include <thread>
#include <mutex>
#include <chrono>

class Driver {
public:

    enum GameState{
        MENU,
        PLAY,
        PAUSED
    };

    /**
     * Constructor
     */
    Driver();

    /**
     * Destructor
     */
    ~Driver();

    /**
     * Start the threaded game
     */
    void start();

    /**
     * Perform game logic
     */
    void loop();

    /**
     * Paint to screen
     */
    void paintComponent();

    
private:
    /**
     * Threading and window variables
     */
    sf::RenderWindow window;
    std::thread loopThread;
    std::mutex mutex;

    //Program running boolean
    bool runProgram;

    //Game management
    GameState GameState;
    sf::Font font;
    sf::Text startGame;
    sf::Text Exit;
    sf::Text pausedText;

    //enemy
    std::vector<Enemy> enemies;

    //level
    int currentLevel;

    //Game Menu variables
    sf::Texture backgroundMenu;
    sf::Sprite backgroundSprite;

    //brightness
    Slider brightnessAdjust;

    //invulnebility timer
    sf::Clock waitTimer;
    bool wait;

    sf::Text playerScore;
    

    /**
     * GAME PRIVATE MEMBERS
     */
    //Create a maze and map
    Maze maze;
    Map map;

    //Create a bot
    Bot bot;

    //Create camera
    Camera camera;

    //ANTON CODE INITIALIZATION
    //Make a Player position, size
    Player player;
    Lives lives;
    std::vector<HealthPickup> HealthPickups;    
    std::vector<PowerUp> powerUps;

    //Initiaziaze timer
    Timer Timers;

    //position size of lives top right
    float heartWidth;
    float livesX;
    float livesY;

    // sf::Music music;

    //handle meny events
    void handleMenu();
};

#include "Driver.cpp"
#endif
