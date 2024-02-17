#ifndef VERTEX_HPP
#define VERTEX_HPP

#include <iostream>

class Vertex {
private:
    double data_[3];

public:
    /**
     * BIG 5
     */
    /**
     * DEFAULT CONSTRUCTOR
     */
    Vertex();

    /**
     * PARAMETERIZED CONSTRUCTOR 3D
     */
    Vertex(double x, double y, double z);

    /**
     * PARAMETERIZED CONSTRUCTOR 2D
     */
    Vertex(double x, double y);

    /**
     * COPY CONSTRUCTOR
     */
    Vertex(const Vertex& other);

    /**
     * COPY ASSIGNMENT OPERATOR
     */
    Vertex& operator=(const Vertex& other);

    /**
     * DESTRUCTOR
     */
    ~Vertex();

    /**
     * Accessors methods
     */
    double getX() const;
    double getY() const;
    double getZ() const;

    /**
     * Mutator methods
     */
    void setX(double n);
    void setY(double n);
    void setZ(double n);
    void set(double x, double y, double z);

    /**
     * Print methods
     */
    void print() const;
};

#include "Vertex.cpp"
#endif