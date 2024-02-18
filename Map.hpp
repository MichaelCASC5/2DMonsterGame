#ifndef MAP_HPP
#define MAP_HPP

#include <iostream>
#include <vector>

#include <SFML/Graphics.hpp>

class Map {
public:
    /**
     * BIG 5
     */
    /**
     * Default constructor
     */
    Map();

    /**
     * ACCESSOR FUNCTIONS
     */
    /**
     * Gets the value at a certain 2D index
     */
    bool getCoordinate(int x, int y);
    
    /**
     * Returns a pointer to the 2D vector
     */
    std::vector<std::vector<bool>> & getMap();

    /**
     * GRAPHICS FUNCTIONS
     */
    /**
     * Draws the map onto the screen
     */
    void draw(sf::RenderTarget& window) const;

private:
    //2D map
    std::vector<std::vector<bool>> map_;
};

#include "Map.cpp"
#endif
