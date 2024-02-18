#ifndef BOT_CPP
#define BOT_CPP

#include <iostream>
#include <vector>

#include "Vertex.hpp"

#include <SFML/Graphics.hpp>

class Bot {
public:
    /**
     * BIG 5
     */
    /**
     * Default Constructor
     */
    Bot();

    /**
     * Parameterized Constructor
     */
    Bot(int xPos, int yPos, int velocity, int angle, std::vector<Vertex> path);

    /**
     * Copy Constructor
     */
    Bot(const Bot& other);

    /**
     * Copy Assignment Operator
     */
    Bot& operator=(const Bot& other);

    /**
     * Destructor
     */
    ~Bot();

    /**
     * ACCESSOR FUNCTIONS
     */
    /**
     * Get x position
     */
    double getXPos();

    /**
     * Get y position
     */
    double getYPos();

    /**
     * Get velocity
     */
    double getVelocity();

    /**
     * Get angle
     */
    double getAngle();

    /**
     * Get bot path
     */
    std::vector<Vertex> & getPath();

    /**
     * MUTATOR FUNCTIONS
     */
    /**
     * Set x position
     */
    void setXPos(double n);

    /**
     * Set y position
     */
    void setYPos(double n);

    /**
     * Set velocity
     */
    void setVelocity(double n);

    /**
     * Set angle
     */
    void setAngle(double n);

    /**
     * Set bot path
     */
    void setPath(std::vector<Vertex> vec);

    /**
     * BOT FUNCTIONS
     */
    /**
     * Calculate euclidean distance to target
     */
    double dist(Vertex v);

    /**
     * Move bot
     */
    void move();

    /**
     * GRAPHICS FUNCTIONS
     */
    /**
     * Draw the bot
     */
    void draw(sf::RenderTarget& window) const;
private:
    //Coordinate position of the bot
    double xPos_, yPos_;

    //Velocity and angle of the bot
    double velocity_;
    double angle_;

    //Path containing list of vertex positions to be visited
    std::vector<Vertex> path_;
};

#include "Bot.cpp"
#endif
