#ifndef CELL_HPP
#define CELL_HPP

#include <SFML/Graphics.hpp>

#include "Cell.hpp"
#include "Vertex.hpp"

#include <iostream>
#include <vector>
#include <array> 

class Cell {
private:
    bool walls_[4];
    bool visited_;

public:
    /**
        * DEFAULT CONSTRUCTOR
    */
    Cell();

    // /**
    //     * PARAMETERIZED CONSTRUCTOR
    // */
    // Cell(std::initializer_list<int> arr);

    // /**
    //     COPY CONSTRUCTOR
    // */
    // Cell(const Cell& other);

    // /**
    //     COPY ASSIGNMENT OPERATOR
    // */
    // Cell& operator=(const Cell& other);

    // /**
    //     DESTRUCTOR
    // */
    // ~Cell();

    /**
        * ACCESSOR METHODS
    */
    /**
        * Returns the address to the 2D vector Cell_ 
    */
    bool * getWalls();

    /**
        * Returns whether cell has been visited
    */
    bool getVisited() const;

    /**
        * MUTATOR METHODS
    */
    /**
        * Sets a cell's walls to true or false
    */
    void setWallValues(bool up, bool right, bool down, bool left, bool visited);

    /**
        * Sets visited
    */
    void setVisited(bool visited);

    /**
        * CELL FUNCTIONS
    */
    /**
        * Returns whether the cell has any walls. If the cell has no walls, it means it hasn't been visited yet
    */
    bool hasWalls() const;

    /**
        * PRINT FUNCTIONS
    */
    void print() const;

    /**
        * GRAPHICS METHODS
    */
    /**
        * Draws the cell onto the screen
    */
    void draw(sf::RenderTarget& window, int xPos, int yPos) const;
};

#include "Cell.cpp"
#endif