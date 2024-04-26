#ifndef CAMERA_HPP
#define CAMERA_HPP

#include <iostream>
#include "Vertex.hpp"

class Camera {
public:
    /**
     * BIG 5
     */
    /**
     * Default Constructor
     */
    Camera();

    /**
     * Parameterized Constructor
     */
    Camera(double posX, double posY, int tileX, int tileY, double angle);

    /**
     * CAMERA FUNCTIONS
     */
    /**
     * Cast a ray from the camera perspective
     */
    void raycast();

    /**
     * Set all relevant data
     */
    void setAll(double posX, double posY, double angle);

    /**
     * Draws camera information
     */
    void draw(sf::RenderTarget& window) const;

private:
    double posX_;
    double posY_;

    int tileX_;
    int tileY_;

    double angle_;

    std::vector<Vertex> intersections;
};

#include "Camera.cpp"
#endif
