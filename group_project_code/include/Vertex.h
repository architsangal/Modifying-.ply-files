#pragma once
#include <iostream>
using namespace std;

class Vertex
{
    private:
    double x;
    double y;
    double z;
    int index;
    static int count;

    public:
    Vertex(double tx,double ty,double tz);
    Vertex(const Vertex &v);
    ~Vertex();
    
    public:
    double getX();
    double getY();
    double getZ();
    int getIndex();
    void setIndex(int value);
}; 