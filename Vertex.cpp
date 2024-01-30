Vertex::Vertex() {
    for (int i = 0; i < 3; i++) {
        pos_[i] = 0;
    }
}

Vertex::Vertex(int xPos, int yPos, int zPos) {
    pos_[0] = xPos;
    pos_[1] = yPos;
    pos_[2] = zPos;
}

Vertex::Vertex(int xPos, int yPos) {
    pos_[0] = xPos;
    pos_[1] = yPos;
    pos_[2] = 0;
}

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
