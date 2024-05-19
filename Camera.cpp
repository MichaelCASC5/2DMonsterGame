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
void Camera::raycast(Map & map, double angle) {
    //The first point of intersection
    double dx = posX_ - (int)posX_;
    double dy = posY_ - (int)posY_;

    double interX_horz = 0;
    double interY_horz = 0;

    double interX_vert = 0;
    double interY_vert = 0;

    //Calculate the tan of the angle in radians
    double tanAngle = tan(angle * PI / 180);

    /**
     * Get first intersection points
     */
    //Calculate first intersection with horizontal grid line
    interX_horz = posX_ - ((-1.0 * dy) / tanAngle);
    interY_horz = posY_ - dy;

    //Calculate first intersection with vertical grid line
    interX_vert = posX_ + (1 - dx);
    interY_vert = posY_ + ((-1.0 * (1 - dx)) * tanAngle);

    //Continue the ray cast for a certain amount of iterations
    bool foundTile = false;
    for (int i = 0; i < 10; i++) {
        //Only if the intersection points fall in the bounds of the maze
        //If greater than 0
        if (interX_horz > 0 && interY_horz > 0 && interX_horz < map.getMap().size() && interY_horz < map.getMap()[0].size()) {
            //If within the length and width of map
            if (interX_horz < interX_vert) {
                //Check if the intersection selects a tile for horizontal grid lines
                if (map.getMap()[interX_horz][interY_horz - 0.25]) {
                    //Add that point to the intersections vector
                    Vertex pointofinterhorz(interX_horz, interY_horz);
                    intersections.push_back(pointofinterhorz);

                    //Leave the loop
                    break;
                }
            }
        }

        //Only if the intersection points fall in the bounds of the maze
        //If greater than 0
        if (interX_vert > 0 && interY_vert > 0 && interX_vert < map.getMap().size() && interY_vert < map.getMap()[0].size()) {
            //If within the length and width of map
            if (interY_horz < interY_vert) {
                //Check if the intersection selects a tile for vertical grid lines
                if (map.getMap()[interX_vert][interY_vert]) {
                    //Add that point to the intersections vector
                    Vertex pointofintervert(interX_vert, interY_vert);
                    intersections.push_back(pointofintervert);

                    //Leave the loop
                    break;
                }
            }
        }

        interY_horz -= 1;
        interX_horz += 1 / tanAngle;

        interX_vert += 1;
        interY_vert -= tanAngle;
    }
}

/**
 * Cast many rays from the camera POV
 */
void Camera::scan(Map & map) {
    intersections.clear();
    for (int i = 0; i < angle_; i+=1) {
        raycast(map, i);
    }
    std::cout << angle_ << std::endl;
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
