#ifndef MAP_HPP
#define MAP_HPP

#include <iostream>
#include <vector>

#include <random>

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
    const std::vector<std::vector<bool>> & getMap() const;

    /**
     * MAP FUNCTIONS
     */
    /**
     * Sets the borders of the map to true
     */
    void buildPerimeter();

    /**
     * Builds a box in the map
     */
    void buildCell(int x, int y, int horz, int vert, Cell cell);

    /**
     * Builds the map according to a maze
     */
    void buildMap(Maze &maze);


    /**
     * GRAPHICS FUNCTIONS
     */
    /**
     * Draws the map onto the screen
     */
    void draw(sf::RenderTarget& window) const;
    
    std::vector<Vertex> getOpenSpaces() const;

    std::vector<sf::Vector2f>findOpenSpaces(const Map& map);

    sf::Vector2f selectSpawnLocation(const std::vector<sf::Vector2f>&OpenSpaces);

    sf::Vector2f convertToScreen(const sf::Vector2f gridCoords) const;

    void setExit(int x, int y);

    sf::Vector2f getExit() const;

    void buildExit();

    void setEndGame(bool endGame);

    bool isBlocked(int x, int y) const;


private:
    //2D map
    std::vector<std::vector<bool>> map_;
    sf::Vector2f exit;
    bool endGameColor=false;
};

#include "Map.cpp"
#endif
