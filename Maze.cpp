/**
 * BIG 5
 */
/**
 * DEFAULT CONSTRUCTOR
 */
Maze::Maze() {
    maze_ = {};

    active_[0] = 1;
    active_[1] = 1;

    resolution_[0] = 10;
    resolution_[1] = 10;
}

/**
 * PARAMETERIZED CONSTRUCTOR
 * Specifies resolution
 */
Maze::Maze(int resx, int resy) {
    maze_ = {};

    active_[0] = 1;
    active_[1] = 1;

    resolution_[0] = resx + 2;
    resolution_[1] = resy + 2;
}

/**
 * COPY CONSTRUCTOR
 */
Maze::Maze(const Maze& other) {
    //Clears the maze_ of this object
    maze_.clear();

    //For every cell in the other maze, push a copy to this one
    for (int i = 0; i < other.maze_.size(); i++) {
        std::vector<Cell> layer;
        Cell cell;
        for (int j = 0; j < other.maze_.size(); j++) {
            cell = other.maze_[i][j];
        }

        //Push each row of the other maze to this one's
        maze_.push_back(layer);

        //Clear the row after
        layer.clear();
    }

    //Set active and resolution to the other maze
    active_[0] = other.active_[0];
    active_[1] = other.active_[1];

    resolution_[0] = other.resolution_[0];
    resolution_[1] = other.resolution_[1];
}

/**
 * COPY ASSIGNMENT OPERATOR
 */
Maze& Maze::operator=(const Maze& other) {
    //Clears the maze_ of this object
    maze_.clear();

    //For every cell in the other maze, push a copy to this one
    for (int i = 0; i < other.maze_.size(); i++) {
        std::vector<Cell> layer;
        Cell cell;
        for (int j = 0; j < other.maze_.size(); j++) {
            cell = other.maze_[i][j];
        }

        //Push each row of the other maze to this one's
        maze_.push_back(layer);

        //Clear the row after
        layer.clear();
    }

    //Set active and resolution to the other maze
    active_[0] = other.active_[0];
    active_[1] = other.active_[1];

    resolution_[0] = other.resolution_[0];
    resolution_[1] = other.resolution_[1];

    return *this;
}

/**
 * DESTRUCTOR
 */
Maze::~Maze() {}

/**
 * ACCESSOR METHODS
 */
/**
 * Returns the address to the 2D vector maze_ 
 */
std::vector<std::vector<Cell>>& Maze::getMaze() {
    return maze_;
}

/**
 * @returns a pointer to the active_ vertex
 */
int * Maze::getActive() {
    return active_;
}

/**
 * @returns a pointer to the resoution_ vertex
 */
int * Maze::getResolution() {
    return resolution_;
}

/**
 * MAZE FUNCTIONS
 */
/**
 * Checks if the active_ is surrounded on all sides by visited cells or borders
 *
 * An array of 4 booleans attest to whether there are open spaces in either direction.
 */
bool Maze::isActiveStuck() const {
    //If the 4 adjacent spaces are obstructed. True if there is an obstruction.
    bool surrounded[4];

    //The 4 directions either way are checked for a visited cell
    surrounded[0] = maze_[active_[0] + 0][active_[1] - 1].getVisited();
    surrounded[1] = maze_[active_[0] + 1][active_[1] + 0].getVisited();
    surrounded[2] = maze_[active_[0] + 0][active_[1] + 1].getVisited();
    surrounded[3] = maze_[active_[0] - 1][active_[1] + 0].getVisited();
    
    //If the active_ is surrounded on all sides (each side is true), return true
    bool output = true;
    for (int i = 0; i < 4; i++) {
        //If a single side is caught being false (there is a free space there) return false
        if (!surrounded[i]) {
            output = false;
            break;
        }
    }

    return output;
}

/**
 * Checks if the direction the active_ wishes to travel to is blocked off by a visited cell 
 *
 * Depending on which direction the active_ wishes to go, one is either added or subtracted to find
 * the adjacent position. Then that cell is checked to see if it was ever visited.
 *
 * @param direction The direction that the active_ wishes to travel in.
 * @return A boolean representing whether or not a visited cell lies one ahead in that direction.
 */
bool Maze::IsDirectionBlocked(int direction) const {
    if (direction == 0) {
        return maze_[active_[0] + 0][active_[1] - 1].getVisited();
    } else if (direction == 1) {
        return maze_[active_[0] + 1][active_[1] + 0].getVisited();
    } else if (direction == 2) {
        return maze_[active_[0] + 0][active_[1] + 1].getVisited();
    } else if (direction == 3) {
        return maze_[active_[0] - 1][active_[1] + 0].getVisited();
    } else {
        return 0;
    }
}

/**
 * Populates the maze with cells
 *
 * The maze is filled with empty cells but considers the cells around the perimeter as having been
 * visited. These cells are built to serve as a walled perimeter around the maze.
 *
 * @post A blank maze is built with a walled perimeter
 */
void Maze::setupMaze() {
    //Populate the maze with empty cells
    for (int i = 0; i < resolution_[0]; i++) {
        //This represents each row of cells to be added to the maze
        std::vector<Cell> mazeLayer;
        
        //Push a cell to form each row; do something special for the borders
        for (int j = 0; j < resolution_[1]; j++) {
            Cell cell;

            //The border cells should be pre-visited
            if (i == 0 || i == resolution_[0] - 1 || j == 0 || j == resolution_[1] - 1) {
                cell.setVisited(true);
            }

            //Push each cell into the row
            mazeLayer.push_back(cell);
        }

        //Push each row into the maze
        maze_.push_back(mazeLayer);
        mazeLayer.clear();
    }
}

/**
 * Uses the Depth-First Search Algorithm to generate the maze
 *
 * The cell generation doesn't begin at (0, 0), where the border is. Instead the generation begins
 * at (1, 1). The first cell counts as having been visited and it is given walls.
 * A random direction is chosen for the active_, and the maze extends into that direction.
 * As the maze navigates around the map, the coordinates of the nodes visited are recorded and remembered
 * in the vector "path." The active_ only stops once it gets stuck somewhere.
 * When the active_ gets stuck, the algorithm traverses that recorded "path" to find the first cell that
 * can be expanded on.
 *
 * @post The maze has been generated
 */
void Maze::depthFirstSearch() {
    //Clear maze_
    maze_.clear();

    //Sets up the maze by populating it with cells
    setupMaze();

    //Generating random device to seed the RNG
    std::random_device rd;
    std::mt19937 gen(rd());//Mersenne Twister
    std::uniform_real_distribution<double> dis(0, 1.0);//range [0,1)

    //Reset the active_ to randomized spawn coordinates to begin generation
    Vertex spawn((int)(1 + (resolution_[0] - 2) * dis(gen)), (int)(1 + (resolution_[1] - 2) * dis(gen)));
    active_[0] = spawn.getX();
    active_[1] = spawn.getY();

    //Prepare the first cell by giving it total walls
    maze_[spawn.getX()][spawn.getY()].setWallValues(1, 1, 1, 1, 1);

    //Preparing the path
    std::vector<Vertex> path;

    //Add the first cell to the path
    // Vertex firstCell(1, 1);
    path.push_back(spawn);

    //So long as the amount of cells hasn't filled in the maze, keep generating
    while (path.size() < (resolution_[0] - 2) * (resolution_[1] - 2)) {
        //Generate a random direction to move the active_ to [0,3]
        int direction = (int)(dis(gen) * 4);

        //Checks if the active can't move in any direction. If it can't, then go back and find an open cell along the path.
        if (!isActiveStuck()) {
            //If the active isn't surrounded, then check which direction is actually suitable to advance towards.
            if (!IsDirectionBlocked(direction)) {
                //Open up this cell to the appropriate direction
                maze_[active_[0]][active_[1]].getWalls()[(direction)] = false;
                
                //move active_ based on direction
                if (direction == 0) {
                    active_[1] = active_[1] - 1;
                } else if (direction == 1) {
                    active_[0] = active_[0] + 1;
                } else if (direction == 2) {
                    active_[1] = active_[1] + 1;
                } else if (direction == 3) {
                    active_[0] = active_[0] - 1;
                }

                //Set the next wall to recieve the active_
                //If the cell hasn't been visited yet, set it to all walls
                if (!maze_[active_[0]][active_[1]].getVisited()) {
                    maze_[active_[0]][active_[1]].setWallValues(1, 1, 1, 1, 1);
                }
                //If it has been visited, open up the wall to recieve the active_
                maze_[active_[0]][active_[1]].getWalls()[(direction + 2) % 4] = false;

                //Add the cell to the path
                Vertex traceCell(active_[0], active_[1]);
                path.push_back(traceCell);
            }
        } else {
            //Traverse the path in search of an open cell
            // for (int i = 0; i < path.size(); i++) {//Hard mode
            for (int i = path.size() - 1; i >= 0; i--) {//Easy mode
                //Set the active_ to the path as it's being traversed
                active_[0] = path[i].getX();
                active_[1] = path[i].getY();

                //If that new active isn't surrounded, then this section is finished
                if (!isActiveStuck()) {
                    break;
                }
            }
        }
    }
    
    //Clear path
    path.clear();
}

/**
 * Builds the maze
 *
 * First, the setup is called to populate the maze with empty cells and a perimeter. Then, the depth-first search
 * algorithm is called to generate the maze structure.
 *
 * @post A completely generated maze.
 */
void Maze::buildMaze() {
    //Sets the maze up
    setupMaze();

    //Algorithmically generates the maze
    depthFirstSearch();

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(1,resolution_[1]-2);

    int exitRow=dis(gen);
    maze_[resolution_[0]-2][exitRow].setWallValues(
        maze_[resolution_[0]-2][exitRow].getWalls()[0],
        false,
        maze_[resolution_[0]-2][exitRow].getWalls()[2],
        maze_[resolution_[0]-2][exitRow].getWalls()[3],
        true
    );
}

/**
 * GRAPHICS METHODS
 */
/**
 * Draws the maze onto the screena
 */
void Maze::draw(sf::RenderTarget& window) const {
    for (int i = 0; i < resolution_[0]; i++) {
        for (int j = 0; j < resolution_[1]; j++) {
            maze_[i][j].draw(window, i, j);
        }
    }
}

