/**
 * BIG 5
 */
/**
 * DEFAULT CONSTRUCTOR
 * NOTE: The map_ resolution must always be a multiple of 5
 */
Map::Map() : map_(50, std::vector<bool>(50)) {}

/**
 * ACCESSOR FUNCTIONS
 */
/**
 * @return The value at a certain index
 */
bool Map::getCoordinate(int x, int y)
{
    return map_[x][y];
}
/**
 * @return A pointer to the entire 2D vector of bools.
 */
const std::vector<std::vector<bool>> &Map::getMap() const
{
    // Return a pointer to the first element
    return map_;
}

/**
 * MAP FUNCTIONS
 */
/**
 * Sets the borders of the map to true
 *
 * This function iterates through the map_ and sets whatever index is at an edge of the 2D
 * vector to true.
 */
void Map::buildPerimeter()
{
    // For every index, check if that index is at an edge. If so, set it to true
    for (int i = 0; i < map_.size(); i++)
    {
        for (int j = 0; j < map_[i].size(); j++)
        {
            if (i == 0 || i == map_.size() - 1 || j == 0 || j == map_[i].size() - 1)
            {
                map_[i][j] = true;
            }
        }
    }
}
/**
 * Builds an individual cell in the map
 *
 * This function accepts a position in the map (int x, int y) and a cell (Cell cell)
 * to build a blocky box in the map out of true/false values.
 * Depending on what walls the cell has, a corresponding box is built on the map.
 *
 * @param x The x position on the map to build the box to
 * @param y The y position on the map to build the box to
 * @param horz The horizontal width the box should have
 * @param vert The vertical height the box should have
 * @param cell The maze cell that the box will be built from
 */
void Map::buildCell(int x, int y, int horz, int vert, Cell cell)
{
    // Increase the width and height accordingly to allow a box to be built at a certain position
    horz += x;
    vert += y;

    // For a certain range in the map_, check if an index should be true given the cell data
    for (int i = x; i < horz && i < map_.size(); i++)
    {
        for (int j = y; j < vert && i < map_[i].size(); j++)
        {
            if ((i == x && cell.getWalls()[3]) || (i == horz - 1 && cell.getWalls()[1]) || (j == y && cell.getWalls()[0]) || (j == vert - 1 && cell.getWalls()[2]))
            {
                map_[i][j] = true;
            }
        }
    }

    // Fill in the corners of a cell to clean up the map
    if (x >= 0 && y >= 0 && x < map_.size() && y < map_[0].size())
    {
        map_[x][y] = true;
        map_[x + 4][y + 4] = true;
        map_[x][y + 4] = true;
        map_[x + 4][y] = true;
    }
}

/**
 * Builds the map according to a maze
 *
 * This function accepts a reference to a maze. It will use the maze data to
 * build a blocky map. First, the map_ is cleared (all bools are set to false).
 * Then, for every cell in the maze some corresponding bools in the map_ are set
 * to true to imitate the maze.
 *
 * @param maze A maze object that contains the information to build the map
 */
void Map::buildMap(Maze &maze)
{
    // If the map isn't clear, clear the map before building again
    for (int i = 0; i < map_.size(); i++)
    {
        for (int j = 0; j < map_[i].size(); j++)
        {
            // Set every cell to false
            map_[i][j] = 0;
        }
    }

    // Build perimeter
    buildPerimeter();

    // Set scale of maze translation onto the map
    int sc = 5;

    // For every cell in the maze, build a real blocky cell in the gridded map
    for (int i = 0; i < maze.getMaze().size(); i++)
    {
        for (int j = 0; j < maze.getMaze()[i].size(); j++)
        {
            buildCell(i * sc - sc, j * sc - sc, sc, sc, maze.getMaze()[i][j]);
        }
    }

    int exitX = (maze.getMaze().size() * sc) - sc;
    int exitY = (maze.getMaze().back().size() * sc) - sc;
    if (exitX + 3 >= map_.size())
    {
        exitX = map_.size() - 4;
    }
    if (exitX >= 0 && exitX < map_.size() && exitY >= 0 && exitY < map_[exitX].size())
    {
        setExit(exitX, exitY);
    }
    else
    {
        setExit(map_.size() - 4, map_[0].size() - 1);
    }
}

/**
 * GRAPHICS FUNCTIONS
 */
/**
 * Draws the map onto the screen
 */
void Map::draw(sf::RenderTarget &window) const
{

    std::cout << "Exit coordinates: " << exit.x << ", " << exit.y << std::endl;
    for (int i = 0; i < map_.size(); i++)
    {
        for (int j = 0; j < map_[i].size(); j++)
        {
            // Set the dimensions of the rectangle
            sf::RectangleShape shape(sf::Vector2f(18.f, 18.f));

            shape.setPosition((float)i * 20 + 250, (float)j * 20);

            // Gets the last 3 coordinates of Exit map
            if (i >= static_cast<int>(exit.x) && i < static_cast<int>(exit.x) + 3 && j == static_cast<int>(exit.y))
            {
                shape.setFillColor(sf::Color::Yellow);
                std::cout << "Drawing Exit at:  " << i << ", " << j << std::endl;
                window.draw(shape);
            }
            else if (map_[i][j])
            {
                // second level
                if (endGameColor)
                {
                    shape.setFillColor(sf::Color::Blue);
                }
                // original level
                else
                {
                    shape.setFillColor(sf::Color::Green);
                }
            }
            else
            {
                continue;
            }
            window.draw(shape);
        }
    }
}

/**
 * finds open spaces of coordinate in the map
 * finds cell that are not occupied. marked as open
 * returns a list of open spaces as 2D vector coordinates
 * @param map A constatn reference to map object
 * @return std::vector<sf::Vector2f> A vector of 2D Vectors representing open spaces
 */
std::vector<sf::Vector2f> Map::findOpenSpaces(const Map &map)
{
    // vector hold coordinates of all open spaces in map
    std::vector<sf::Vector2f> openSpaces;
    // iterate trhough each column of map
    for (int x = 0; x < map.getMap().size(); ++x)
    {
        // iterate through each row within current column
        for (int y = 0; y < map.getMap()[x].size(); ++y)
        {
            // check if current cell(x,y) not occupied
            if (!getCoordinate(x, y))
            {
                // if open, add current coordinates to openSpace Vector, convert to float
                openSpaces.emplace_back(static_cast<float>(x), static_cast<float>(y));
            }
        }
    }
    // return vector of open spaces coordinates
    return openSpaces;
}

/**
 * Selects random spawn location
 * random number generator from vector of open spaces.
 * @param OpenSpaces a constant of vector of potential spawn locations
 * @return sf::Vector2f the coordinate of randmly spawned locations
 */
sf::Vector2f Map::selectSpawnLocation(const std::vector<sf::Vector2f> &OpenSpaces)
{
    // random device, generator
    static std::random_device rd;
    static std::mt19937 gen(rd());
    // pick index in range of vector
    std::uniform_int_distribution<> dis(0, OpenSpaces.size() - 1);
    // return randomly selected location of OpenSpace vector
    return OpenSpaces[dis(gen)];
}

/**
 * retrieve open spaces on the map that are not occupied
 * @return std::vector<Vertex> A vector of 2D Vectors representing open spaces coordinates
 */
std::vector<Vertex> Map::getOpenSpaces() const
{
    // vector to store coordianates of open spaces
    std::vector<Vertex> openSpaces;
    // iterate each column of map
    for (int x = 0; x < map_.size(); ++x)
    {
        // iterate each row of current column
        for (int y = 0; y < map_[x].size(); ++y)
        {
            // check if cell at position (x,y) not occupied
            if (!map_[x][y])
            {
                // add coordinates to openSpace vector
                openSpaces.emplace_back(x, y);
            }
        }
    }
    return openSpaces;
}

/**
 * converts grid coordinates to screen coordinates
 * @param gridCoords grid coordinate to be converted
 * @return sf::Vector2f Screen coordinate
 */
sf::Vector2f Map::convertToScreen(const sf::Vector2f gridCoords) const
{
    // size of each tile in pixels
    const float TILE_SIZE = 20.0f;
    // scaling
    const sf::Vector2f OFFSET(250.0f, 0.0f);
    // return screen coordinates by scaling grid coordinates, adding offset.
    sf::Vector2f screenCoords(gridCoords.x * TILE_SIZE + OFFSET.x, gridCoords.y * TILE_SIZE);
    return screenCoords;
}

/**
 * Sets location of exit of map
 * defined exit point of map
 * @param x: the x-coordinate of starting point
 * @param y the y-coordinate of starting point
 */
void Map::setExit(int x, int y)
{
    // width of exit area
    int exitWidth = 3;
    // prevent out of map bounds
    int maxX = std::min(x + exitWidth, static_cast<int>(map_.size()));
    for (int i = x; i < maxX; i++)
    {

        if (y < map_[i].size())
        {
            // clear cell to make part of exit
            map_[i][y] = false;
        }
    }
    // store exit location
    exit = sf::Vector2f(x, y);
}

/**
 * retrieves exit cooridante of map
 * @return sf::Vector2f coordinate of exit
 */
sf::Vector2f Map::getExit() const
{
    return exit;
}

/**
 * exit marked in map
 */
void Map::buildExit()
{
    if (!map_[static_cast<int>(exit.x)][static_cast<int>(exit.y)])
    {
        // ensures exit open
        map_[static_cast<int>(exit.x)][static_cast<int>(exit.y)] = false;
    }
}

/**
 * sets end game condition
 * @param endGame boolean flag indicating game condition be activated
 */
void Map::setEndGame(bool endGame)
{
    endGameColor = endGame;
}