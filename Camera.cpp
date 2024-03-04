/**
 * BIG 5
 */
/**
 * Default Constructor
 */
Camera::Camera() {
    posX_ = 0;
    posY_ = 0;
    tileX_ = 0.0;
    tileY_ = 0.0;
    angle_ = 0.0;
}

/**
 * Parameterized Constructor
 */
Camera::Camera(int posX, int posY, int tileX, int tileY, int angle) {
    posX_ = posX;
    posY_ = posY;
    tileX_ = tileX;
    tileY_ = tileY;
    angle_ = angle;
}

/**
 * CAMERA FUNCTIONS
 */
void Camera::Raycast() {
    
}
