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
    //Default Constructor
    Map();

    //Accessor methods
    bool getCoordinate(int x, int y);
    bool * getMap();

private:
    //2D map
    bool map_[400][400];
};

#include "Map.cpp"
#endif
