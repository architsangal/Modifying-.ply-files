#pragma once
#include "../include/FileHandler.h"
#include "../include/Vertex.h"
#include <vector>
#include <set>
#include <iostream>
using namespace std;

class Ply : public FileHandler
{
    private:
    string fileName;
    string data;
    string filtered_data;
    bool isValid;
    int vertices;
    int faces;
    vector<Vertex> vertex_s;
    vector<vector<int>> face_s;

    void calcVertices(string line);
    void calcFaces(string line);
    int NewIndex(int old_index, set<int,greater<int>> &vertex_left);
    static bool compare(vector<Vertex> a,vector<Vertex> b);
    static double area(vector<Vertex> a);
    static double distance(Vertex a,Vertex b);

    public:
        Ply();
        Ply(const Ply &p);
        ~Ply();
        void read();
		void write();
		void modify();
        void setFileNameWithAddress(string name);
        void setFileName(string name);
        bool isValidFile();
}; 