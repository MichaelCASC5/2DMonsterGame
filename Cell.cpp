/**
    * BIG 5
*/
/**
    * DEFAULT CONSTRUCTOR
*/
Cell::Cell() {
    for (int i = 0; i < 4; i++) {
        walls_[i] = 0;
    }

    visited_ = false;
}

/**
    * PARAMETERIZED CONSTRUCTOR
*/
Cell::Cell(bool up, bool right, bool down, bool left, bool visited) {
    walls_[0] = up;
    walls_[1] = right;
    walls_[2] = down;
    walls_[3] = left;

    visited_ = visited;
}

/**
    * COPY CONSTRUCTOR
*/
Cell::Cell(const Cell& other) {
    walls_[0] = other.walls_[0];
    walls_[1] = other.walls_[1];
    walls_[2] = other.walls_[2];
    walls_[3] = other.walls_[3];

    visited_ = other.visited_;
}

/**
    * COPY ASSIGNMENT OPERATOR
*/
Cell& Cell::operator=(const Cell& other) {
    walls_[0] = other.walls_[0];
    walls_[1] = other.walls_[1];
    walls_[2] = other.walls_[2];
    walls_[3] = other.walls_[3];

    visited_ = other.visited_;

    return *this;
}

/**
    * DESTRUCTOR
*/
Cell::~Cell() {}

/**
    * ACCESSOR METHODS
*/
/**
    * @return the address to the 2D vector Cell_ 
*/
bool * Cell::getWalls() {
    return walls_;
}

/**
    * @return Whether the cell has been visited or not
*/
bool Cell::getVisited() const {
    return visited_;
}

/**
    * MUTATOR METHODS
*/
/**
    * Sets a cell's walls to true or false
*/
void Cell::setWallValues(bool up, bool right, bool down, bool left, bool visited) {
    walls_[0] = up;
    walls_[1] = right;
    walls_[2] = down;
    walls_[3] = left;

    visited_ = visited;
}

/**
    * Sets visited
    * @param visited The bool to set visited_ to
*/
void Cell::setVisited(bool visited) {
    visited_ = visited;
}

/**
    * CELL FUNCTIONS
*/
bool Cell::hasWalls() const {
    bool output = false;

    for (int i = 0; i < 4; i++) {
        if (walls_[i]) {
            output = true;
            break;
        }
    }

    return output;
}

/**
    * PRINT FUNCTIONS
*/
/**
    * Prints the cell data to console
*/
void Cell::print() const {
    for (int i = 0; i < 4; i++) {
        std::cout << walls_[i] << " ";
    }
    std::cout << "\n";
}

/**
    * GRAPHICS METHODS
*/
/**
    * Draws the cell onto the screen
*/
void Cell::draw(sf::RenderTarget& window, int xPos, int yPos) const {
    if (!hasWalls()) {
        //Set the dimensions of the rectangle
        sf::RectangleShape shape(sf::Vector2f(15.f, 15.f));

        //Set the position of the rectangle
        sf::Vector2f position = {(float) xPos * 20, (float) yPos * 20};
        shape.setPosition(position);

        //Set the color of the rectangle
        shape.setFillColor(sf::Color::Black);

        //Draw the rectangle to the target window
        window.draw(shape);
    }

    for (int i = 0; i < 4; i++) {
        if (walls_[0]) {
            //Set the dimensions of the rectangle
            sf::RectangleShape shape(sf::Vector2f(25.f, 5.f));

            //Set the position of the rectangle
            sf::Vector2f position = {(float) xPos * 20 - 5, (float) yPos * 20 - 5};
            shape.setPosition(position);

            //Set the color of the rectangle
            shape.setFillColor(sf::Color::Blue);

            //Draw the rectangle to the target window
            window.draw(shape);
        }
        if (walls_[1]) {
            //Set the dimensions of the rectangle
            sf::RectangleShape shape(sf::Vector2f(5.f, 20.f));

            //Set the position of the rectangle
            sf::Vector2f position = {(float) xPos * 20 + 15, (float) yPos * 20};
            shape.setPosition(position);

            //Set the color of the rectangle
            shape.setFillColor(sf::Color::Blue);

            //Draw the rectangle to the target window
            window.draw(shape);
        }
        if (walls_[2]) {
            //Set the dimensions of the rectangle
            sf::RectangleShape shape(sf::Vector2f(20.f, 5.f));

            //Set the position of the rectangle
            sf::Vector2f position = {(float) xPos * 20, (float) yPos * 20 + 15};
            shape.setPosition(position);

            //Set the color of the rectangle
            shape.setFillColor(sf::Color::Blue);

            //Draw the rectangle to the target window
            window.draw(shape);
        }
        if (walls_[3]) {
            //Set the dimensions of the rectangle
            sf::RectangleShape shape(sf::Vector2f(5.f, 20.f));

            //Set the position of the rectangle
            sf::Vector2f position = {(float) xPos * 20 - 5, (float) yPos * 20};
            shape.setPosition(position);

            //Set the color of the rectangle
            shape.setFillColor(sf::Color::Blue);

            //Draw the rectangle to the target window
            window.draw(shape);
        }
    }
}