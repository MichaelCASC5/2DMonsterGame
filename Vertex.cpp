/**
    * BIG 5
*/
/**
    * DEFAULT CONSTRUCTOR
*/
Vertex::Vertex() {
    for (int i = 0; i < 3; i++) {
        pos_[i] = 0;
    }
}

/**
    * PARAMETERIZED CONSTRUCTORS
*/
/**
    * 3D PARAMETERIZED CONSTRUCTOR
*/
Vertex::Vertex(int xPos, int yPos, int zPos) {
    pos_[0] = xPos;
    pos_[1] = yPos;
    pos_[2] = zPos;
}

/**
    * 2D PARAMETERIZED CONSTRUCTOR
*/
Vertex::Vertex(int xPos, int yPos) {
    pos_[0] = xPos;
    pos_[1] = yPos;
    pos_[2] = 0;
}

/**
    * COPY CONSTRUCTOR
*/
Vertex::Vertex(const Vertex& other) {
    pos_[0] = other.pos_[0];
    pos_[1] = other.pos_[1];
    pos_[2] = other.pos_[2];
}

/**
    * COPY ASSIGNMENT OPERATOR
*/
Vertex& Vertex::operator=(const Vertex& other) {
    pos_[0] = other.pos_[0];
    pos_[1] = other.pos_[1];
    pos_[2] = other.pos_[2];

    return *this;
}

/**
    * DESTRUCTOR
*/
Vertex::~Vertex() {}

/**
    * Accessor methods
*/
int Vertex::getXPos() const {
    return pos_[0];
}

int Vertex::getYPos() const{
    return pos_[1];
}

int Vertex::getZPos() const{
    return pos_[2];
}

/**
    * Mutator methods
*/
void Vertex::setXPos(int n) {
    pos_[0] = n;
}

void Vertex::setYPos(int n) {
    pos_[1] = n;
}

void Vertex::setZPos(int n) {
    pos_[2] = n;
}

void Vertex::setPos(int xPos, int yPos, int zPos) {
    pos_[0] = xPos;
    pos_[1] = yPos;
    pos_[2] = zPos;
}

/**
    * Print methods
*/
void Vertex::print() const {
    std::cout << pos_[0] << ", " << pos_[1] << ", " << pos_[2] << std::endl;
}