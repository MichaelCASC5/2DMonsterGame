#ifndef VERTEX_HPP
#define VERTEX_HPP

class Vertex {
private:
    int pos_[3];

public:
    /**
        * DEFAULT CONSTRUCTOR
    */
    Vertex();

    /**
        * PARAMETERIZED CONSTRUCTOR 3D
    */
    Vertex(int xPos, int yPos, int zPos);

    /**
        * PARAMETERIZED CONSTRUCTOR 2D
    */
    Vertex(int xPos, int yPos);

    /**
        * Accessors methods
    */
    int getXPos() const;
    int getYPos() const;
    int getZPos() const;

    /**
        * Mutator methods
    */
    void setXPos(int n);
    void setYPos(int n);
    void setZPos(int n);
    void setPos(int xPos, int yPos, int zPos);
};

#include "Vertex.cpp"
#endif