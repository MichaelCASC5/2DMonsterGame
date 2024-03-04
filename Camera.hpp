#ifndef CAMERA_HPP
#define CAMERA_HPP

#include <iostream>

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
    Camera(int posX, int posY, int tileX, int tileY, double angle);

    /**
     * CAMERA FUNCTIONS
     */
    void Raycast();

private:
    double posX_;
    double posY_;

    int tileX_;
    int tileY_;

    int angle_;
};

#include "Camera.cpp"
#endif
