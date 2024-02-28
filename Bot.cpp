/**
 * VAR DEFINITIONS
 */
#define PI 3.1415926535897932384626433832795

/**
 * BIG 5
 */
/**
 * DEFAULT CONSTRUCTOR
 */
Bot::Bot() {
    xPos_ = 0;
    yPos_ = 0;

    velocity_ = 0.2;
    angle_ = 0;

    path_ = {};
}

/**
 * PARAMETERIZED CONSTRUCTOR
 */
Bot::Bot(int xPos, int yPos, int velocity, int angle, std::vector<Vertex> path) {
    xPos_ = xPos;
    yPos_ = yPos;

    velocity_ = velocity;
    angle_ = angle;

    path_ = path;
}

/**
 * COPY CONSTRUCTOR
 */
Bot::Bot(const Bot& other) {
    xPos_ = other.xPos_;
    yPos_ = other.yPos_;

    velocity_ = other.velocity_;
    angle_ = other.angle_;

    path_ = other.path_;
}

/**
 * COPY ASSIGNMENT OPERATOR
 */
Bot& Bot::operator=(const Bot& other) {
    xPos_ = other.xPos_;
    yPos_ = other.yPos_;

    velocity_ = other.velocity_;
    angle_ = other.angle_;

    path_ = other.path_;

    return *this;
}

/**
 * DESTRUCTOR
 */
Bot::~Bot() {}

/**
 * ACCESSOR FUNCTIONS
 */
/**
 * @return The x position
 */
double Bot::getXPos() {
    return xPos_;
}

/**
 * @return The y position
 */
double Bot::getYPos() {
    return yPos_;
}

/**
 * @return The velocity
 */
double Bot::getVelocity() {
    return velocity_;
}

/**
 * @return The angle
 */
double Bot::getAngle() {
    return angle_;
}

/**
 * @return The address to the path
 */
std::vector<Vertex> & Bot::getPath() {
    return path_;
}

/**
 * MUTATOR FUNCTIONS
 */
/**
 * @param n A double to set the x position to
 */
void Bot::setXPos(double n) {
    xPos_  = n;
}

/**
 * @param n A double to set the y position to
 */
void Bot::setYPos(double n) {
    yPos_ = n;
}

/**
 * @param n A double to set the velocity to
 */
void Bot::setVelocity(double n) {
    velocity_ = n;
}

/**
 * @param n A double to set the angle to
 */
void Bot::setAngle(double n) {
    angle_ = n;
}

/**
 * @param vec A vector to set the bot path to
 */
void Bot::setPath(std::vector<Vertex> vec) {
    path_ = vec;
}

/**
 * BOT FUNCTIONS
 */
/**
 * Calculate euclidean distance to target
 * 
 * Uses the distance formula to calculate how far from a point the
 * bot currently is.
 * 
 * @param vertex The target point to calculate the distance to
 * @return The distance to that point
 */
double Bot::dist(Vertex v) {
    return sqrt(pow(v.getX() - xPos_, 2) + pow(v.getY() - yPos_, 2));
}

/**
 * A mod function for the bot's path finding
 * 
 * The C++ fmod() function is really weird and doesn't behave like the one on my
 * calculator so I just made my own. This implementation correctly handles negative
 * numbers and can be used for modding angles.
 * 
 * @param x The divident to calculate the mod from
 * @param y the divisor to calculate the mod from
 * @return The modded value
 */
double mod(double x, double y) {
    double output = fmod(fabs(x), y);

    if (x < 0) {
        output = y - output;
    }

    return output;
}

/**
 * Keeps the angle between [-180, 180) degrees
 * 
 * @param angle The angle to refit into the specified range
 * @return The refitted angle
 */
double Bot::refit(double angle) {
    if (angle < -PI) {
        angle += 2 * PI;
    } else if (angle >= PI) {
        angle -= 2 * PI;
    }

    return angle;
}

/**
 * Moves the bot according to the path that was set.
 * 
 * Each game tick this function should be called. It moves the bot
 * through each successive coordinate in the path it should approach.
 * Each call of this function moves the bot by a certain amount toward
 * its next target.
 */
void Bot::move() {
    //Only go towards the next point if the vector isn't empty
    if (path_.size() > 0) {

        //Calculating the angle from this position to point
        double yDiff = path_[0].getY() - yPos_;
        double xDiff = path_[0].getX() - xPos_;
        double targetAngle = atan2(yDiff, xDiff);

        //Calculating where the target angle is relative to bot angle
        targetAngle = targetAngle - angle_;
        
        //Handling out of bounds
        angle_ = refit(angle_);
        targetAngle = refit(targetAngle);
        
        //Changing course slowly depending on where the target angle is
        if (targetAngle < 0) {
            angle_ -= 0.05;
        } else {
            angle_ += 0.05;
        }

        //If the bot reaches a point, remove it from the path
        if (dist(path_[0]) < 0.1) {
            path_.erase(path_.begin());
        }

        //Change position accounting for rotation
        xPos_ += velocity_ * cos(angle_);
        yPos_ += velocity_ * sin(angle_);
    }
}

/**
 * GRAPHICS FUNCTIONS
 */
/**
 * Draws the bot onto the screen
 */
void Bot::draw(sf::RenderTarget& window) const {
    //Set the dimensions of the rectangle
    sf::RectangleShape shape(sf::Vector2f(20.f, 30.f));

    //Set the position of the rectangle
    sf::Vector2f position = {(float) xPos_ * 20, (float) yPos_ * 20};
    shape.setPosition(position);

    //Set the color of the rectangle
    shape.setFillColor(sf::Color::White);

    //Rotate
    shape.rotate((float) angle_ * (180 / PI));

    //Draw the rectangle to the target window
    window.draw(shape);
}