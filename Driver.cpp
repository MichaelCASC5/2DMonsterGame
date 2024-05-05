#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include "Driver.hpp"
/**
 * Constructor
 *
 * This sets up the SFML window and all relevant information.
 * At the bottom the initial game logic that isn't meant to be looped
 * continuously is placed.
 */
Driver::Driver() : window(sf::VideoMode::getDesktopMode(), "2D Graphics", sf::Style::Fullscreen), runProgram(true), GameState(MENU), maze(10, 10), player(sf::Vector2f(2.0f, 2.0f)), lives(3, "heart.png"), Timers(90), brightnessAdjust(100, 100, 200, 10), currentLevel(1)
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

    // background MUSIC
    //  if(!backgroundMusic.openFromFile("magic.mp3")){
    //      std::cerr<<"Failed to load background music"<<std::endl;
    //  }
    //  else{
    //      backgroundMusic.setLoop(true);
    //      backgroundMusic.play();
    //  }

    // creating enemy, position and size
    enemies.push_back(Enemy(sf::Vector2f(1000.0f, 150.0f), sf::Vector2f(60, 60)));
    enemies.push_back(Enemy(sf::Vector2f(300.0f, 800.0f), sf::Vector2f(20, 20)));
    enemies.push_back(Enemy(sf::Vector2f(500.0f, 150.0f), sf::Vector2f(60, 60)));
    enemies.push_back(Enemy(sf::Vector2f(1200.0f, 800.0f), sf::Vector2f(20, 20)));

    // setting up Menu background and size
    backgroundSprite.setTexture(backgroundMenu);
    backgroundSprite.setScale(3.3f, 2.0f);

    // start game text
    startGame.setFont(font);
    startGame.setString("Start Adventure");
    startGame.setCharacterSize(20);
    startGame.setFillColor(sf::Color::White);
    startGame.setPosition(200, 200);

    // pause Text

    pauseText.setFont(font);
    pauseText.setString("PAUSED");
    pauseText.setCharacterSize(50);
    pauseText.setFillColor(sf::Color::White);

    // center Pause Text to Screen
    sf::FloatRect textRect = pauseText.getLocalBounds();
    pauseText.setOrigin(textRect.width / 2, textRect.height / 2);
    pauseText.setPosition(window.getSize().x / 2, window.getSize().y / 2);

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

    /**
     * Powerups makes a vecotor of powerups,
     * finds a openspace in the map,
     * scales the powerups into the map and places it
     * adds the powerup to the vector
     */

    // scaling factor to the map
    const float scales = 20.0f;
    // position shifting by 250 x-axis
    const sf::Vector2f offsets = {250.0f, 0.0f};
    // powerUpTypes, positions in the game
    std::vector<std::pair<sf::Vector2f, PowerUpType>> powerUpInfo = {
        {{7.0f, 8.0f}, PowerUpType::SpeedBoost},
        {{10.0f, 8.0f}, PowerUpType::RapidFire},
        {{15.0f, 8.0f}, PowerUpType::DoubleScore}};

    // vector of open spaces in the map
    std::vector<sf::Vector2f> openSpaces;
    // get open spaces from map, adjust coordinates by scale, offset
    for (auto &vertex : map.getOpenSpaces())
    {
        openSpaces.emplace_back(vertex.getX() * scales + offsets.x, vertex.getY() * scales + offsets.y);
    }
    // loop through each power up type and position and place them in game
    for (const auto &[pos, type] : powerUpInfo)
    {
        // random open location for placing powerup
        sf::Vector2f powerUpLocation = map.selectSpawnLocation(openSpaces);
        // create a powerup at selected location and add it to vector
        powerUps.push_back(PowerUp(type, powerUpLocation));
    }

    // Make a Player position, size
    player.setHealth(3);
    player.loadSprite("slime1.png");
    player.setSize(30.0f, 30.0f);

    // position size of lives
    heartWidth = lives.getHeartWidth();
    livesX = 1300;
    livesY = 90;
    lives.setPosition(livesX, livesY);
    lives.setLives(player.getHealth());

    // score
    playerScore.setFont(font);
    playerScore.setCharacterSize(20);
    playerScore.setFillColor(sf::Color::White);
    playerScore.setPosition(1500, 90);

    // heart pickups
    const float scale = 20.0f;
    const sf::Vector2f offset = {250.0f, 0.0f};
    std::vector<sf::Vector2f> heartSpaces;
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
    // clock to measure time elapsed between frames for consistent updates
    sf::Clock clock;
    sf::Event event;
    // running game, menu screen first comes up
    while (runProgram)
    {
        // restart clock
        sf::Time deltaTime = clock.restart();

        // handle events that occurs within window
        while (window.pollEvent(event))
        {
            // check for window close events or ESC key
            if (event.type == sf::Event::Closed || (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape))
            {
                window.close();
                runProgram = false;
                continue;
            }
            // handle game state transitions
            if (GameState == MENU)
            {
                // starts the game with ENTER
                if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Enter)
                {
                    GameState = PLAY;
                }
            }
            else if ((GameState == PLAY || GameState == PAUSED) && event.type == sf::Event::KeyPressed)
            {
                // pause the game with 'P'
                if (event.key.code == sf::Keyboard::P)
                {
                    GameState = (GameState == PLAY) ? PAUSED : PLAY;
                }
            }

            if (event.type == sf::Event::KeyPressed)
            {
                if (GameState == MENU)
                {
                    // GameState is PLAY starts the game when 'Enter' pressed
                    if (event.key.code == sf::Keyboard::Enter)
                    {
                        GameState = PLAY;
                    }
                    // runProgram is false when game ends
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
        // Gamestate is MENU menu function works
        if (GameState == MENU)
        {
            handleMenu();
        }

        else if (GameState == PLAY)
        {
            Timers.update();
            /**
             * LOOPED GAME LOGIC GOES HERE
             */

            // get player position
            sf::Vector2f playerPosition = player.getPosition();

            // Enemy follows Player position
            for (Enemy &enemy : enemies)
            {
                enemy.update(deltaTime, playerPosition, map);
            }
            // player score increases 100 when enemy dies
            for (auto &enemy : enemies)
            {
                if (!enemy.isAlive())
                {
                    player.increaseScore(100);
                }
            }
            // remove dead enemies from the game
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
                        player.loseLife();
                        lives.setLives(player.getHealth());
                        break;
                    }
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

            // Player can move
            player.handleMovement(deltaTime, map);
            player.handleRotation();

            // player looses all lives, end game
            if (player.getHealth() <= 0)
            {
                runProgram = false;
                break;
            }

            // Do camera logic
            camera.setAll(player.getPosition().x, player.getPosition().y, 45);
            camera.scan(map);

            // swicth levels
            if (currentLevel == 2)
            {
                map.setEndGame(true);
                powerUps.clear();
            }

            // game ends
            else
            {
                map.setEndGame(false);
            }
            // checking if player reached the exit
            if (player.reachedExit(map))
            {
                currentLevel++;
                // if last level, finishes game
                if (currentLevel == 3)
                {
                    sf::Font font;
                    if (font.loadFromFile("Roboto-Bold.ttf"))
                    {
                        sf::Text endText("Congratulations, Game Finished", font, 24);
                        endText.setFillColor(sf::Color::White);
                        endText.setPosition(100, window.getSize().y / 2);
                        window.draw(endText);
                        window.display();
                        sf::sleep(sf::seconds(3));
                    }
                    window.close();
                    runProgram = false;
                    return;
                }
                else
                {
                    map.setEndGame(false);
                    maze.buildMaze();
                    map.buildMap(maze);
                    player.setPosition(sf::Vector2f(2.0f, 2.0f));
                    //  map.setEndGame(false);
                    if (currentLevel == 2)
                    {
                        map.setEndGame(true);
                        enemies.push_back(Enemy(sf::Vector2f(1000.0f, 150.0f), sf::Vector2f(60, 60)));
                        enemies.push_back(Enemy(sf::Vector2f(300.0f, 800.0f), sf::Vector2f(20, 20)));
                        enemies.push_back(Enemy(sf::Vector2f(500.0f, 150.0f), sf::Vector2f(60, 60)));
                        enemies.push_back(Enemy(sf::Vector2f(1200.0f, 800.0f), sf::Vector2f(20, 20)));
                    }
                }
                // runProgram=false;
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

        // adding Level, Score text
        else if (GameState == PLAY)
        {
            sf::Text LevelText;
            sf::Font font;
            if (!font.loadFromFile("Roboto-Bold.ttf"))
            {
                std::cerr << "Failed to load font" << std::endl;
            }
            LevelText.setFont(font);
            LevelText.setString("Level " + std::to_string(currentLevel));
            LevelText.setCharacterSize(24);
            LevelText.setFillColor(sf::Color::White);
            LevelText.setPosition(1500, 50);
            window.draw(LevelText);

            playerScore.setString("Score: " + std::to_string(player.getScore()));
            window.draw(playerScore);

            // updates Laser positions
            player.updateLasers(window, enemies);

            // set Player lives
            lives.setLives(player.getHealth());
            lives.draw(window);

            // draw enemy
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

            // draw player,timer,lives
            player.drawPlayer(window);
            Timers.draw(window);
            lives.draw(window);

            // Camera draw
            camera.draw(window);

            //...END DRAW OBJECTS
        }

        else if (GameState == PAUSED)
        {
            std::cout << "drawining pause screen" << std::endl;
            window.draw(pauseText);
        }

        else if (GameState == PAUSED)
        {
            window.draw(pauseText);
            // backgroundMusic.pause();
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
