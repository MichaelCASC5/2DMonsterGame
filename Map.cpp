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
    if(exitX+3>=map_.size()){
        exitX=map_.size()-4;
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
    for (int i = 0; i < map_.size(); i++)
    {
        for (int j = 0; j < map_[i].size(); j++)
        {
            if (map_[i][j])
            {
                // Set the dimensions of the rectangle
                sf::RectangleShape shape(sf::Vector2f(18.f, 18.f));

                shape.setPosition((float)i * 20 + 250, (float)j * 20);
              
            
                if (i == static_cast<int>(exit.x) && i<static_cast<int>(exit.x)+3 && j == static_cast<int>(exit.y))
                {
                    shape.setFillColor(sf::Color::Yellow);
                }
                else{
  shape.setFillColor(map_[i][j] ? sf::Color::Green : sf::Color::Black);
                }
                // Set the position of the rectangle
                //  sf::Vector2f position = {(float) i * 20 + 250, (float) j * 20};
                // shape.setPosition(position);

                // Set the color of the rectangle
                //  shape.setFillColor(sf::Color::Green);

                // if (100000000.0 / rand() < 0.15)
                // Draw the rectangle to the target window
                window.draw(shape);
            
        }
    }
}
}

std::vector<sf::Vector2f> Map::findOpenSpaces(const Map &map)
{
    std::vector<sf::Vector2f> openSpaces;
    for (int x = 0; x < map.getMap().size(); ++x)
    {
        for (int y = 0; y < map.getMap()[x].size(); ++y)
        {
            if (!getCoordinate(x, y))
            {
                openSpaces.emplace_back(static_cast<float>(x), static_cast<float>(y));
            }
        }
    }
    return openSpaces;
}

sf::Vector2f Map::selectSpawnLocation(const std::vector<sf::Vector2f> &OpenSpaces)
{
    static std::random_device rd;
    static std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(0, OpenSpaces.size() - 1);
    return OpenSpaces[dis(gen)];
}

std::vector<Vertex> Map::getOpenSpaces() const
{
    std::vector<Vertex> openSpaces;
    for (int x = 0; x < map_.size(); ++x)
    {
        for (int y = 0; y < map_[x].size(); ++y)
        {
            if (!map_[x][y])
            {
                openSpaces.emplace_back(x, y);
            }
        }
    }
    return openSpaces;
}
sf::Vector2f Map::convertToScreen(const sf::Vector2f gridCoords) const
{
    const float TILE_SIZE = 20.0f;
    const sf::Vector2f OFFSET(250.0f, 0.0f);
    sf::Vector2f screenCoords(gridCoords.x * TILE_SIZE + OFFSET.x, gridCoords.y * TILE_SIZE);
    return screenCoords;
}

void Map::setExit(int x, int y)
{
    int exitWidth=3;
    for(int i=0;i<exitWidth;i++){
        int currentX=x+i;
        if(currentX<map_.size() && y<map_[currentX].size()){
            map_[currentX][y]=false;
        }
    }
    exit=sf::Vector2f(x,y);
}

sf::Vector2f Map::getExit() const
{
    return exit;
}

void Map::buildExit()
{
    if (!map_[static_cast<int>(exit.x)][static_cast<int>(exit.y)])
    {
        map_[static_cast<int>(exit.x)][static_cast<int>(exit.y)] = false;
    }
}
