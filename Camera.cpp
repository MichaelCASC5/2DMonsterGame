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
Camera::Camera(int posX, int posY, int tileX, int tileY, double angle) {
    posX_ = posX;
    posY_ = posY;
    tileX_ = tileX;
    tileY_ = tileY;
    angle_ = angle;
}

/**
 * CAMERA FUNCTIONS
 */
/**
 * Cast a ray from the camera pov
 */
void Camera::raycast() {
    std::cout << posX_ << ", " << posY_ << " | " << tileX_ << ", " << tileY_ << " | " << angle_ << std::endl;
}

/**
 * Set relevant data
 */
void Camera::setAll(double posX, double posY, double angle) {
    posX_ = posX;
    posY_ = posY;
    tileX_ = (int)posX;
    tileY_ = (int)posY;
    angle_ = angle;
}
