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

private:
    double posX_;
    double posY_;

    int tileX_;
    int tileY_;

    int angle_;
};

#include "Camera.cpp"
#endif
