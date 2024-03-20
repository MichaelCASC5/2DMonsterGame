#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include "Driver.hpp"
#include <SFML/Audio.hpp>
/**
 * Constructor
 *
 * This sets up the SFML window and all relevant information.
 * At the bottom the initial game logic that isn't meant to be looped
 * continuously is placed.
 */
Driver::Driver() : window(sf::VideoMode::getDesktopMode(), "2D Graphics", sf::Style::Fullscreen), runProgram(true), GameState(MENU), maze(10, 10), player(sf::Vector2f(100.0f, 100.0f)), lives(3, "heart.png"), Timers(30), brightnessAdjust(100, 100, 200, 10)
{

    // loading font
    if (!font.loadFromFile("Roboto-Bold.ttf"))
    {
        std::cerr << "Failed to load font" << std::endl;
    }

    // loading menu background
    if (!backgroundMenu.loadFromFile("maze.jpg"))
    {
        std::cerr << "Failed to load menu image" << std::endl;
    }


    //creating enemy
    enemies.push_back(Enemy(sf::Vector2f(200, 150), sf::Vector2f(60, 60)));
    // enemies.push_back(Enemy(sf::Vector2f(300,200), sf::Vector2f(40,40)));
    // enemies.push_back(Enemy(sf::Vector2f(400,200), sf::Vector2f(10,10)));
    enemies.push_back(Enemy(sf::Vector2f(150,450), sf::Vector2f(20,20)));
    // enemies.push_back(Enemy(sf::Vector2f(600,700), sf::Vector2f(30,30)));

    // setting up Menu background and size
    backgroundSprite.setTexture(backgroundMenu);
    backgroundSprite.setScale(3.3f, 2.0f);

    // start game text
    startGame.setFont(font);
    startGame.setString("Start Adventure");
    startGame.setCharacterSize(20);
    startGame.setFillColor(sf::Color::White);
    startGame.setPosition(200, 200);

    // exit text
    Exit.setFont(font);
    Exit.setString("Exit");
    Exit.setCharacterSize(24);
    Exit.setFillColor(sf::Color::White);
    Exit.setPosition(200, 250);

    /**
     * INITIAL GAME LOGIC
     */
    std::vector<Vertex> path = {Vertex(10, 10), Vertex(40, 2), Vertex(50, 5), Vertex(70, 50), Vertex(20, 20), Vertex(20, 50)};
    bot.setPath(path);

    // Setup maze
    maze.buildMaze();
    map.buildMap(maze);

    // ANTON CODE ASSIGNMENT
    // Make a Player position, size
    player.setHealth(3);
    player.loadSprite("slime1.png");
    player.setSize(30.0f, 30.0f);

    // position size of lives top right
    heartWidth = lives.getHeartWidth();
    livesX = 790;
    livesY = 30;
    lives.setPosition(livesX, livesY);
    lives.setLives(player.getHealth());
}

/**
 * Destructor lets loop() loopThread to catch up and close with everything else
 */
Driver::~Driver()
{
    loopThread.join();
}

/**
 * Start the program
 *
 * This is the jumping-off point where the threaded game logic and screen
 * drawing will begin.
 */
void Driver::start()
{
    /**
     * Launch paintComponent after threading loop()
     * https://www.reddit.com/r/cpp_questions/comments/p4z5nv/invalid_use_of_nonstatic_member_function/
     * https://stackoverflow.com/questions/266168/simple-example-of-threading-in-c
     */
    loopThread = std::thread(&Driver::loop, this);
    paintComponent();
}

/**
 * Performs all game logic
 *
 * This consists of a while loop that works so long as runProgram is true
 * The loop is threaded so that it runs alongside the paintComponent
 * All relevant game logic is run from here.
 * At the bottom a thread sleep causes the loop to run at 60 updates per second
 */
void Driver::loop()
{
    sf::Clock clock;
    // running game, menu screen first comes up
    while (runProgram)
    {
        sf::Time deltaTime = clock.restart();
        if (GameState == MENU)
        {
            handleMenu();
        }
        else if (GameState == PLAY)
        {
            /**
             * LOOPED GAME LOGIC GOES HERE
             */

            //get player position
            sf::Vector2f playerPosition = player.getPosition();

            //BROKEN LASER of ENEMY, but tracking works
            for (Enemy &enemy : enemies)
            {
                enemy.update(deltaTime, playerPosition);
           //     enemy.shoot(playerPosition);
            //    enemy.updateLasers(deltaTime, window);
            }

            //invinsibility of player
            player.updateInvinsiblity(deltaTime);

            //if not invinsible and collides with enemy looses life
            if (!player.isInvinsible())
            {
                for (auto &enemy : enemies)
                {
                    if (player.collidesWith(enemy))
                    {
                        std::cout << "Collision detectedm reducing life" << std::endl;
                        player.loseLife();
                        lives.setLives(player.getHealth());
                        break;
                    }
                }
            }

            // Move bot
            bot.move();

            // ANTON CODE LOGIC
            Timers.update();
            // Player can move
            player.handleMovement(deltaTime, map);
            player.handleRotation();

            // player.isCollision(map);

            //...END LOOPED GAME LOGIC

            /**
             * Handle keypresses
             */
            sf::Event event;
            while (window.pollEvent(event))
            {

                if (event.type == sf::Event::Closed)
                {
                    window.close();
                    // If ESCAPE is pressed set runProgram to false
                }
                else if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape)
                {
                    runProgram = false;
                    // If SPACE is pressed rebuild the maze, then rebuild the map around that maze
                }
                else if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Space)
                {
                    maze.buildMaze();
                    map.buildMap(maze);
                }
                // if F is pressed player shoots lazer in direction he us facing
                else if (sf::Keyboard::isKeyPressed(sf::Keyboard::F))
                {
                    player.shoot();
                }
            }
        }
        // Sleep the thread to allow for 60 updates per second logic
        std::this_thread::sleep_for(std::chrono::milliseconds(1000 / 60)); // 60 ups
    }
}

/**
 * Performs all rendering
 *
 * This consists of a while loop that continually renders onto the canvas
 * The condition is so long as runProgram is true, and so long as the
 * window is open.
 * During execution a mutex locks and unlocks the thread while drawing is
 * happening to ensure no thread can access this code at the same time.
 */
void Driver::paintComponent()
{
    while (window.isOpen() && runProgram)
    {
        // Prevent other threads from simultaneously accessing the window
        mutex.lock();

        // Clear the screen to black
        window.clear(sf::Color::Black);

        // if in Menu Screen draw backgorund imagae, startGame and Exit buttons
        if (GameState == MENU)
        {

            window.draw(backgroundSprite);
            window.draw(startGame);
            window.draw(Exit);
            brightnessAdjust.draw(window);
        }
        else if (GameState == PLAY)
        {

            // updates Laser positions
            player.updateLasers(window);

            lives.setLives(player.getHealth());
            lives.draw(window);

            for (Enemy &enemy : enemies)
            {
                enemy.draw(window);
            }

            /**
             * DRAW OBJECTS HERE
             */

            // Draw bot
            bot.draw(window);

            // Draw maze
            maze.draw(window);

            // Draw map
            map.draw(window);

            // ANTON CODE DRAW
            player.drawPlayer(window);
            Timers.draw(window);
            lives.draw(window);

            //...END DRAW OBJECTS
        }
        // Display the window
        window.display();

        // Unlock the mutex
        mutex.unlock();

        // Sleep the loop to allow for X frames per second rendering
        std::this_thread::sleep_for(std::chrono::milliseconds(1000 / 60)); // 60 fps
    }
}

// handling menu screen
void Driver::handleMenu()
{
    sf::Event event;

    // DOSENT WORK FOR NOW, but gets bounding box of startGame, detecting mouse clicks
    // sf::FloatRect playButtonBounds = startGame.getGlobalBounds();

    // window event queue
    while (window.pollEvent(event))
    {
        // check if winodw close event is triggered, closes game
        if (event.type == sf::Event::Closed)
        {
            window.close();     // window close
            runProgram = false; // stop running game
        }
        else if (event.type == sf::Event::KeyPressed)
        {
            // check if Enter is pressed start game
            if (event.key.code == sf::Keyboard::Enter)
            {
                GameState = PLAY;
            }
            // check if escape pressed to close game
            else if (event.key.code == sf::Keyboard::Escape)
            {
                window.close();     // close window
                runProgram = false; // stop runnign program
            }
            // else if(event.type==sf::Event::MouseButtonPressed){
            //  if(event.mouseButton.button==sf::Mouse::Left){
            // vectorwi stores 2D positions, current position of mosue cursor
            //  sf::Vector2i positionmouse=sf::Mouse::getPosition(window);
            // if(playButtonBounds.contains(static_cast<float>(positionmouse.x), static_cast<float>(positionmouse.y)))
            // GameState=PLAY;
            // }
            // }
            //}
            // sf::Vector2i positionmouse=sf::Mouse::getPosition(window);
            // std::cout<<"Mouse position:"<<positionmouse.x<<","<<positionmouse.y<<std::endl;
            // std::cout<<"Play Button Bounds:"<<playButtonBounds.left<<", "<<playButtonBounds.top<<", "<<playButtonBounds.width<<", "<<playButtonBounds.height<<std::endl;
        }
    }
}