#include "../include/Vertex.h"
using namespace std;

// static variable count assigns the index for the vertex
int Vertex::count = 0;

// constructor
Vertex::Vertex(double tx,double ty,double tz)
{
    index = count;
    count++;
    x = tx;
    y = ty;
    z = tz;
}

// copy constructor
Vertex::Vertex(const Vertex &v)
{
    index = v.index;
    x = v.x;
    y = v.y;
    z = v.z;
}

// destructor
Vertex::~Vertex()
{}


// following are the getters and setters
int Vertex::getIndex()
{
    return index;
}

void Vertex::setIndex(int value)
{
    index=value;
}

double Vertex::getX()
{
    return x;
}

double Vertex::getY()
{
    return y;
}

double Vertex::getZ()
{
    return z;
}