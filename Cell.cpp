/**
    * DEFAULT CONSTRUCTOR
*/
Cell::Cell() {
    for (int i = 0; i < 4; i++) {
        walls_[i] = 0;
    }
}

/**
    * ACCESSOR METHODS
*/
/**
    * Returns the address to the 2D vector Cell_ 
*/
bool * Cell::getWalls() {
    return walls_;
}

/**
    * MUTATOR METHODS
*/
/**
    * Sets a cell's walls to true or false
*/
void Cell::setWallValues(bool up, bool right, bool down, bool left) {
    walls_[0] = up;
    walls_[1] = right;
    walls_[2] = down;
    walls_[3] = left;
}

/**
    * CELL FUNCTIONS
*/
bool Cell::isVisited() const {
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
    //Set the dimensions of the rectangle
    sf::RectangleShape shape(sf::Vector2f(15.f, 15.f));

    //Set the position of the rectangle
    sf::Vector2f position = {(float) xPos * 20, (float) yPos * 20};
    shape.setPosition(position);

    //Set the color of the rectangle
    shape.setFillColor(sf::Color::Black);

    //Draw the rectangle to the target window
    window.draw(shape);

    for (int i = 0; i < 4; i++) {
        if (walls_[0]) {
            //Set the dimensions of the rectangle
            sf::RectangleShape shape(sf::Vector2f(20.f, 5.f));

            //Set the position of the rectangle
            sf::Vector2f position = {(float) xPos * 20, (float) yPos * 20 - 5};
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