/**
 * BIG 5
 */
/**
 * DEFAULT CONSTRUCTOR
 */
Map::Map() : map_(32, std::vector<bool>(32)) {
    /**
     * Set the borders to true
     */
    for (int i = 0; i < map_.size(); i++) {
        for (int j = 0; j < map_[i].size(); j++) {
            if (i == 0 || i == map_.size() - 1 || j == 0 || j == map_[i].size() - 1) {
                map_[i][j] = true;
            }
        }
    }
    
    /**
     * For the sake of example, a few more cells are set to true.
     */
    map_[30][30] = true;
    map_[29][29] = true;
    map_[28][28] = true;

    map_[11][13] = true;
    map_[3][7] = true;
    map_[15][25] = true;
}

/**
 * ACCESSOR FUNCTIONS
 */
/**
 * @return The value at a certain index
 */
bool Map::getCoordinate(int x, int y) {
    return map_[x][y];
}
/**
 * @return A pointer to the entire 2D vector of bools.
 */
std::vector<std::vector<bool>> & Map::getMap() {
    //Return a pointer to the first element
    return map_;
}

/**
 * GRAPHICS FUNCTIONS
 */
/**
 * Draws the map onto the screen
 */
void Map::draw(sf::RenderTarget& window) const {
    for (int i = 0; i < map_.size(); i++) {
        for (int j = 0; j < map_[i].size(); j++) {
            // if (100000000.0 / rand() < 0.1) {
            if (map_[i][j]) {
                //Set the dimensions of the rectangle
                sf::RectangleShape shape(sf::Vector2f(27.f, 27.f));

                //Set the position of the rectangle
                sf::Vector2f position = {(float) i * 30, (float) j * 30};
                shape.setPosition(position);

                //Set the color of the rectangle
                shape.setFillColor(sf::Color::Green);

                //Draw the rectangle to the target window
                window.draw(shape);
            }
        }
    }
}