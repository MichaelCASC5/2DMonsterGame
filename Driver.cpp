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
Driver::Driver() : window(sf::VideoMode::getDesktopMode(), "2D Graphics", sf::Style::Fullscreen), runProgram(true), GameState(MENU), maze(10, 10), player(sf::Vector2f(2.0f, 2.0f)), lives(3, "heart.png"), Timers(30), brightnessAdjust(100, 100, 200, 10)
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

    // creating enemy
    enemies.push_back(Enemy(sf::Vector2f(700.0f, 150.0f), sf::Vector2f(60, 60)));
    // enemies.push_back(Enemy(sf::Vector2f(300,200), sf::Vector2f(40,40)));
    // enemies.push_back(Enemy(sf::Vector2f(400,200), sf::Vector2f(10,10)));
    enemies.push_back(Enemy(sf::Vector2f(700.0f, 100.0f), sf::Vector2f(20, 20)));
    // enemies.push_back(Enemy(sf::Vector2f(600,700), sf::Vector2f(30,30)));

    // powerups
    const float scales = 20.0f;
    const sf::Vector2f offsets = {250.0f, 0.0f};
    std::vector<std::pair<sf::Vector2f,PowerUpType>> powerUpInfo={
       {{7.0f,8.0f}, PowerUpType::SpeedBoost},
       {{10.0f,8.0f}, PowerUpType::RapidFire},
       {{15.0f,8.0f}, PowerUpType::DoubleScore}
    };

    for (const auto& [pos,type] : powerUpInfo)
    {
        sf::Vector2f adjustedPowerUpPos = {(pos.x * scales) + offsets.x, pos.y * scales};
        powerUps.push_back(PowerUp(type, adjustedPowerUpPos));
    };

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

    // score
    playerScore.setFont(font);
    playerScore.setCharacterSize(20);
    playerScore.setFillColor(sf::Color::White);
    playerScore.setPosition(1000, 20);

    // heart pickups
    const float scale = 20.0f;
    const sf::Vector2f offset = {250.0f, 0.0f};
    sf::Vector2f heartPos = sf::Vector2f(700.0f, 800.0f);
    sf::Vector2f adjustedHeartPos = {(heartPos.x - offset.x) / scale, heartPos.y / scale};
    HealthPickups.push_back(HealthPickup(adjustedHeartPos, "heart.png"));
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
    sf::Event event;
    // running game, menu screen first comes up
    while (runProgram)
    {
        sf::Time deltaTime = clock.restart();

        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::KeyPressed)
            {
                if (GameState == MENU)
                {
                    if (event.key.code == sf::Keyboard::Enter)
                    {
                        GameState = PLAY;
                    }
                    else if (event.key.code == sf::Keyboard::Escape)
                    {
                        runProgram = false;
                    }
                    else if (GameState == PLAY || GameState == PAUSED)
                    {
                        if (event.key.code == sf::Keyboard::P)
                        {
                            GameState = (GameState == PLAY) ? PAUSED : PLAY;
                        }
                    }
                }
            }
        }

        if (GameState == MENU)
        {
            handleMenu();
        }

        else if (GameState == PLAY)
        {
            /**
             * LOOPED GAME LOGIC GOES HERE
             */

            // get player position
            sf::Vector2f playerPosition = player.getPosition();

            // BROKEN LASER of ENEMY, but tracking works
            for (Enemy &enemy : enemies)
            {
                enemy.update(deltaTime, playerPosition);
                //     enemy.shoot(playerPosition);
                //    enemy.updateLasers(deltaTime, window);
            }

            for (auto &enemy : enemies)
            {
                if (!enemy.isAlive())
                {
                    player.increaseScore(100);
                }
            }

            enemies.erase(std::remove_if(enemies.begin(), enemies.end(),
                                         [](const Enemy &enemy)
                                         { return !enemy.isAlive(); }),
                          enemies.end());

            // invinsibility of player
            player.updateInvinsiblity(deltaTime);

            // if not invinsible and collides with enemy looses life
            if (!player.isInvinsible())
            {
                for (auto &enemy : enemies)
                {
                    if (player.collidesWith(enemy))
                    {
                        // std::cout << "Collision detectedm reducing life" << std::endl;
                        player.loseLife();
                        lives.setLives(player.getHealth());
                        break;
                    }
                }
            }

            // collision with health pickups
            for (size_t i = 0; i < HealthPickups.size();)
            {
                if (player.getGlobalBounds().intersects(HealthPickups[i].getGlobalBounds()))
                {
                    if (player.getHealth() < Player::getMaxLives())
                    {
                        player.increaseHealth(1);
                    }
                    HealthPickups.erase(HealthPickups.begin() + i);
                }
                else
                {
                    ++i;
                }
            }

            // powerups
            for (size_t i = 0; i < powerUps.size();)
            {
                if (player.getGlobalBounds().intersects(powerUps[i].getGlobalBounds()))
                {
                    switch (powerUps[i].getType())
                    {
                    case PowerUpType::SpeedBoost:
                        player.activateSpeedBoost();
                        break;
                    case PowerUpType::RapidFire:
                        player.activateRapidFire();
                        break;
                    case PowerUpType::DoubleScore:
                        player.activateDoubleScore();
                        break;
                    }
                    powerUps.erase(powerUps.begin() + i);
                }
                else
                {
                    ++i;
                }
                player.updatePowerUps(deltaTime);
            }

            // Move bot
            bot.move();

            // ANTON CODE LOGIC
            Timers.update();
            // Player can move
            player.handleMovement(deltaTime, map);
            player.handleRotation();

            // player.isCollision(map);

            // player looses all lives, end game
            if (player.getHealth() <= 0)
            {
                runProgram = false;
                break;
            }

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
                    player.updateCooldown();
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

            playerScore.setString("Score: " + std::to_string(player.getScore()));
            window.draw(playerScore);

            // updates Laser positions
            player.updateLasers(window, enemies);

            lives.setLives(player.getHealth());
            lives.draw(window);

            for (Enemy &enemy : enemies)
            {
                enemy.draw(window);
            }

            // healthpickups
            for (const auto &pickup : HealthPickups)
            {
                pickup.draw(window);
            }

            //  powerups
            for (const auto &powerUp : powerUps)
            {
                powerUp.draw(window);
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
        else if (event.type == sf::Event::KeyPressed && GameState == MENU)
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
        }
    }
}
