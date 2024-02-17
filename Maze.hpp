#ifndef MAZE_HPP
#define MAZE_HPP

#include <SFML/Graphics.hpp>

#include "Cell.hpp"
#include "Vertex.hpp"

#include <iostream>
#include <vector>
#include <random>

class Maze {
private:
    //The 2D vector that contains all the cells that make up the maze
    std::vector<std::vector<Cell>> maze_;

    //An array of two ints that represents the x, y position of the maze generator
    int active_[2];

    //Specifies the resolution of the maze
    int resolution_[2];

public:
    /**
     * BIG 5
     */
    /**
     * DEFAULT CONSTRUCTOR
     */
    Maze();

    /**
     * PARAMETERIZED CONSTRUCTOR
     */
    Maze(int resx, int resy);

    /**
     * COPY CONSTRUCTOR
     */
    Maze(const Maze& other);

    /**
     * COPY ASSIGNMENT OPERATOR
     */
    Maze& operator=(const Maze& other);

    /**
     * DESTRUCTOR
     */
    ~Maze();

    /**
     * ACCESSOR METHODS
    */
    /**
     * Returns the address to the 2D vector maze_ 
     */
    std::vector<std::vector<Cell>> & getMaze();

    /**
     * Returns the active_ vertex
     */
    int * getActive();

    /**
     * Returns the resolution_ vertex
     */
    int * getResolution();

    /**
     * MUTATOR METHODS
     */

    //PLEASE BUILD THE MUTATOR METHODS

    /**
     * MAZE FUNCTIONS
     */
    /**
     * Checks if the active cell is surrounded on all sides by visited cells, and cannot progress in any direction
     */
    bool isActiveStuck() const;

    /**
     * Checks if a particular direction from the active cell is free from a visited cell
     */
    bool IsDirectionBlocked(int direction) const;

    /**
     * Populates the maze with empty cells and a walled perimeter in preparation for maze generation
     */
    void setupMaze();

    /**
     * Uses the depth-first search algorithm to generate the maze
     */
    void depthFirstSearch();

    /**
     * Builds the 2D vector maze_ which represents the maze
     */
    void buildMaze();

    /**
     * GRAPHICS METHODS
     */
    /**
     * Draws the maze onto the screen
     */
    void draw(sf::RenderTarget& window) const;
};

#include "Maze.cpp"
#endif