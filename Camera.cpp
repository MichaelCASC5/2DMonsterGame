#define PI 3.1415926535897932384626433832795

/**
 * BIG 5
 */
/**
 * Default Constructor
 */
Camera::Camera() {
    posX_ = 0.0;
    posY_ = 0.0;
    tileX_ = 0;
    tileY_ = 0;
    angle_ = 0.0;
}

/**
 * Parameterized Constructor
 */
Camera::Camera(double posX, double posY, int tileX, int tileY, double angle) {
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

    //The first point of intersection
    double dy = posX_ - (int)posX_;
    double dx = posY_ - (int)posY_;

    double interX = posX_ + ((-1 * dy) / tan(angle_ * PI / 180));
    double interY = posY_ - dy;

    std::cout << "first intersection:\n" << interX << ", " << interY << std::endl;
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
