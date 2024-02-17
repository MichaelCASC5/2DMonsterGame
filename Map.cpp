/**
 * BIG 5
 */
/**
 * DEFAULT CONSTRUCTOR
 */
Map::Map() {}

/**
 * ACCESSOR METHODS
 */
/**
 * @return The value at a certain index
 */
bool Map::getCoordinate(int x, int y) {
    return map_[x, y];
}
/**
 * @return A pointer to the entire 2D array of bools.
 */
bool * Map::getMap() {
    //Return a pointer to the first element
    return &map_[0][0];
}