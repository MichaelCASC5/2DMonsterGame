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
    std::cout << "raycast " << angle_ << std::endl;
    //The first point of intersection
    double dx = posX_ - (int)posX_;
    double dy = posY_ - (int)posY_;

    double interX_horz = 0;
    double interY_horz = 0;

    double interX_vert = 0;
    double interY_vert = 0;

    intersections.clear();

    //Calculate the tan of the angle in radians
    double tanAngle = tan(angle_ * PI / 180);

    /**
     * Get first intersection points
     */
    //Calculate first intersection with horizontal grid line
    interX_horz = posX_ - ((-1.0 * dy) / tanAngle);
    interY_horz = posY_ - dy;

    //Calculate first intersection with vertical grid line
    interX_vert = posX_ + (1 - dx);
    interY_vert = posY_ + ((-1.0 * (1 - dx)) * tanAngle);

    for (int i = 0; i < 10; i++) {
        Vertex pointofinterhorz(interX_horz, interY_horz);
        intersections.push_back(pointofinterhorz);

        Vertex pointofintervert(interX_vert, interY_vert);
        intersections.push_back(pointofintervert);

        // std::cout << interX_horz << " < " << interX_vert << std::endl;
        // while (interX_horz < interX_vert) {
        // if (interX_horz < interX_vert - 1 / tanAngle) {
            interY_horz -= 1;
            interX_horz += 1 / tanAngle;
        // }

        // std::cout << interY_vert << " < " << interY_horz << std::endl;
        // if (interY_vert > interY_horz + tanAngle) {
            interX_vert += 1;
            interY_vert -= tanAngle;
        // }
    }
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

void Camera::draw(sf::RenderTarget& window) const {
    for (int i = 0; i < intersections.size(); i++) {
        //Set the dimensions of the rectangle
        sf::RectangleShape shape(sf::Vector2f(5.f, 5.f));

        //Set the position of the rectangle
        sf::Vector2f position = {(float) intersections[i].getX() * 20 + 250, (float) intersections[i].getY() * 20};
        shape.setPosition(position);

        //Set the color of the rectangle
        shape.setFillColor(sf::Color::Blue);

        //Draw the rectangle to the target window
        window.draw(shape);
    }
}
