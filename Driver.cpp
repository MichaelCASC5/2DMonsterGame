/**
 * Constructor
 * 
 * This sets up the SFML window and all relevant information.
 * At the bottom the initial game logic that isn't meant to be looped
 * continuously is placed.
 */
Driver::Driver() : window(sf::VideoMode::getDesktopMode(), "2D Graphics", sf::Style::Fullscreen), runProgram(true), maze(10, 10), player(sf::Vector2f(100.0f,100.0f)), lives(3,"heart.png"), Timers(30) {
    /**
     * INITIAL GAME LOGIC
     */
    std::vector<Vertex> path = {Vertex(10, 10), Vertex(40, 2), Vertex(50, 5), Vertex(70, 50), Vertex(20, 20), Vertex(20, 50)};
    bot.setPath(path);

    //Setup maze
    maze.buildMaze();
    map.buildMap(maze);

    //ANTON CODE ASSIGNMENT
    //Make a Player position, size
    player.setHealth(3);
    player.loadSprite("slime1.png");
    player.setSize(30.0f, 30.0f);

    //position size of lives top right
    heartWidth=lives.getHeartWidth();
    livesX=790;
    livesY=30;
    lives.setPosition(livesX,livesY);
}

/**
 * Destructor lets loop() logicThread to catch up and close with everything else
 */
Driver::~Driver() {
    logicThread.join();
}

/**
 * Start the program
 * 
 * This is the jumping-off point where the threaded game logic and screen
 * drawing will begin.
 */
void Driver::start() {
    /**
     * Launch paintComponent after threading loop()
     * https://www.reddit.com/r/cpp_questions/comments/p4z5nv/invalid_use_of_nonstatic_member_function/
     * https://stackoverflow.com/questions/266168/simple-example-of-threading-in-c
     */
    logicThread = std::thread(&Driver::loop, this);
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
void Driver::loop() {
    while (runProgram) {
        /**
         * LOOPED GAME LOGIC GOES HERE
         */

        //Move bot
        bot.move();
        
        //ANTON CODE LOGIC
        Timers.update();
        //Player can move
        player.handleMovement();
        player.handleRotation();

        //...END LOOPED GAME LOGIC

        /**
         * Handle keypresses
         */
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed){
                window.close();
            //If ESCAPE is pressed set runProgram to false
            } else if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape) {
                runProgram = false;
            //If SPACE is pressed rebuild the maze, then rebuild the map around that maze
            } else if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Space) {
                maze.buildMaze();
                map.buildMap(maze);
            }
            else if(sf::Keyboard::isKeyPressed(sf::Keyboard::F)){
                player.shoot();
            }
        }

        //Sleep the thread to allow for 60 updates per second logic
        std::this_thread::sleep_for(std::chrono::milliseconds(1000 / 60));//60 ups
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
void Driver::paintComponent() {
    while (window.isOpen() && runProgram) {
        //Prevent other threads from simultaneously accessing the window
        mutex.lock();

        //Clear the screen to black
        window.clear(sf::Color::Black);

        player.updateLasers(window);

        /**
         * DRAW OBJECTS HERE
         */

        //Draw bot
        bot.draw(window);

        //Draw maze
        maze.draw(window);

        //Draw map
        map.draw(window);

        //ANTON CODE DRAW
        player.drawPlayer(window);
        Timers.draw(window);
        lives.draw(window);

        //...END DRAW OBJECTS

        //Display the window
        window.display();

        //Unlock the mutex
        mutex.unlock();

        //Sleep the loop to allow for X frames per second rendering
        std::this_thread::sleep_for(std::chrono::milliseconds(1000 / 60));//60 fps
    }
}
