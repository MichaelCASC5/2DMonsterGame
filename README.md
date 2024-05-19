# 2DMonsterGame
CS Capstone Spring 2024 group project. Navigate a monster-infested maze.

This project is a 2D game built in C++ using the SFML 2D graphics library. Our group decided to select this language since we have experience with it from our coursework.

To launch the program, simply enter "make" into the WSL terminal. Ensure you have the SFML 2D graphics library installed for WSL.

What the make file does:
    All .cpp files are compiled with C++17 into an executable called "prog"

    The appropriate linker flags are included in the compile command

    Then, prog is executed and the program begins running

How to set up the program:
    To ensure SFML is installed for WSL, first perform a search for the SFML package with your package manager:
        apt-cache search sfml
    
    You will need the development library called:
        libsfml-dev
    
    Then, install the library:
        sudo apt-get install libsfml-dev
    
    If it prompts you, enter yes to install.

    Here is the official SFML tutorial for Linux with some sample code for testing:
        https://www.sfml-dev.org/tutorials/2.6/start-linux.php
    
    Then you can run "make"

If there are difficulties with the project, visit the official SFML documentation.

Maintainence and Contribution:
    Anton and Michael have contributed to this project, and it may be maintained and updated going forward.


**** THE GAME ****


Player Controls:
    Use the WASD keys to move around, and the C and V keys to rotate the player.

    Use the F keys to fire the weapon.

    The player has 3 lives. Once they are all exhausted, the game is lost.

The Powerups:
    Power ups spawn in scattered across the map. Collide with them to collect them.

    These power ups can alter statistics like the weapon's rate of fire and the player's rate of speed.

The Map:
    The map consits of a maze of blocks. The blocks cannot be passed through.

    There is an exit at the bottom right of the maze, that will proceed to the next level or end the game.

The Enemies:
    The moving red squares represent the enemies. They follow the player and will remove your lives when made contact with.

    Take aim and shoot them to destroy them.

Additional Controls:
    Press ESC to leave the program

    Press SPACEBAR to regenerate the maze

Thank you for reading! Have fun.
