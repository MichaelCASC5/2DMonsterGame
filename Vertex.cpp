/**
 * BIG 5
 */
/**
 * DEFAULT CONSTRUCTOR
 */
Vertex::Vertex() {
    for (int i = 0; i < 3; i++) {
        data_[i] = 0;
    }
}

/**
 * PARAMETERIZED CONSTRUCTORS
 */
/**
 * 3D PARAMETERIZED CONSTRUCTOR
 */
Vertex::Vertex(double x, double y, double z) {
    data_[0] = x;
    data_[1] = y;
    data_[2] = z;
}

/**
 * 2D PARAMETERIZED CONSTRUCTOR
 */
Vertex::Vertex(double x, double y) {
    data_[0] = x;
    data_[1] = y;
    data_[2] = 0;
}

/**
 * COPY CONSTRUCTOR
 */
Vertex::Vertex(const Vertex& other) {
    data_[0] = other.data_[0];
    data_[1] = other.data_[1];
    data_[2] = other.data_[2];
}

/**
 * COPY ASSIGNMENT OPERATOR
 */
Vertex& Vertex::operator=(const Vertex& other) {
    data_[0] = other.data_[0];
    data_[1] = other.data_[1];
    data_[2] = other.data_[2];

    return *this;
}

/**
 * DESTRUCTOR
 */
Vertex::~Vertex() {}

/**
 * Accessor methods
 */
double Vertex::getX() const {
    return data_[0];
}

double Vertex::getY() const{
    return data_[1];
}

double Vertex::getZ() const{
    return data_[2];
}

/**
 * Mutator methods
 */
void Vertex::setX(double n) {
    data_[0] = n;
}

void Vertex::setY(double n) {
    data_[1] = n;
}

void Vertex::setZ(double n) {
    data_[2] = n;
}

void Vertex::set(double x, double y, double z) {
    data_[0] = x;
    data_[1] = y;
    data_[2] = z;
}

/**
 * Print methods
 */
void Vertex::print() const {
    std::cout << data_[0] << ", " << data_[1] << ", " << data_[2] << std::endl;
}