#include "../include/FileHandler.h"
#include "../include/Ply.h"
#include "../include/Vertex.h"
#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <set>
#include <cmath>
#include <algorithm>
#include <bits/stdc++.h>
using namespace std;

//constructor
Ply::Ply()
{
    bool isValid = false;
    int vertices = 0;
    int faces = 0;
}

//copy constructor
Ply::Ply(const Ply &p)
{
    fileName = p.fileName;
    data = p.data;
    filtered_data = p.filtered_data;
    isValid = p.isValid;
    vertices = p.vertices;
    faces = p.faces;

    vertex_s.assign(p.vertex_s.begin(),p.vertex_s.end());
    face_s.assign(p.face_s.begin(),p.face_s.end());

}

//destructor
Ply::~Ply()
{
    vertex_s.clear();
    face_s.clear();
}

// reads the from the file and stores it in variable "data"
void Ply::read()
{
    string myText;

    // Read from the text file
    ifstream file(fileName);
    
    // If something goes wrong
    if(file.fail())
    {
        cout << "\u001b[31m\n\t\t\t\t\t\tUNABLE TO OPEN FILE\u001b[0m\n" << endl;
        isValid = false;
        return;
    }

    isValid = true;

    while (getline (file, myText))
    {
        int index=0;
        for(int i=0;myText.size();i++)
        {
            if(myText[i]!=' ')
            {
                index = i;
                break;
            }
        }
        if(myText[index]!='c')
            data = data + myText + "\n";
    }

    file.close();
}

// modities the data read from the file and store it in a new.
void Ply::modify()
{
    vector<string> lines;// data is split with delimiters as "\n", and the chunks are stored in the lines.
    
    stringstream data_in_line(data); 
    string tok;

    while(getline(data_in_line,tok,'\n')) 
    {
        if(tok.size()>0)
        {
            lines.push_back(tok); 
        }
    }

    filtered_data = lines[0] + "\n" + lines[1] + "\n";
    
    calcVertices(lines[2]);

    calcFaces(lines[6]);

    // vertex(s) are separated from the input and stored in vertex_s
    for(int i=0;i<vertices;i++)
    {
        stringstream l(lines[i+9]);
        double x,y,z;
        int count = 0;
        while(getline(l,tok,' ')) 
        {
            if(tok.size()>0)
            {
                count++;
                if(count == 1)
                {
                    sscanf(tok.c_str(),"%lf",&x);
                }
                else if(count == 2)
                {
                    sscanf(tok.c_str(),"%lf",&y);
                }
                else if(count ==3)
                {
                    sscanf(tok.c_str(),"%lf",&z);
                }
            }
        }
        Vertex temp(x,y,z);
        vertex_s.push_back(temp);
    }

    // faces are separated from the input and stored in faces_s
    for(int i=0;i<faces;i++)
    {
        stringstream l(lines[i+vertices+9]);
        int vs;
        while(getline(l,tok,' ')) 
        {
            if(tok.size()>0)
            {
                sscanf(tok.c_str(),"%d",&vs);
                break;
            }
        }
        
        vector<int> newface;
        for(int j=0;j<vs;j++)
        {
            getline(l,tok,' ');
            int temp;
            sscanf(tok.c_str(),"%d",&temp);
            newface.push_back(temp);
        }
        face_s.push_back(newface);
    }

    // our data is now transfered to vertex_s and face_s
    
    /*
    Assumptions :

        minimum vertex in a polygon are 2

        there are only convex polygons

        when we find the 10% of the total faces we may not get an integer. In that case we will floor that value and delete those number of triangles.

        Discard faces which are in the lower 10% of the sorted list of triangles -- what is area of the traiangle are equal?
        In this case, I have still deleted the triangles.
    */

    // faces with more than 3 vertex are being splited into many
    // e.g. {0,1,2,3} ==> {0,1,2} and {0,2,3} 
    // {0,1,2,3} is then deleted
    vector<int> toBeDeleted;
    for(int i=0;i<faces;i++)
    {
        if(face_s[i].size()>3)
        {
            toBeDeleted.push_back(i);
            for(int j=2;j<face_s[i].size();j++)
            {
                vector<int> temp;
                temp.push_back(face_s[i][0]);
                temp.push_back(face_s[i][j-1]);
                temp.push_back(face_s[i][j]);
                face_s.push_back(temp);
            }
        }
    }
    for(int i=toBeDeleted.size()-1;i>=0;i--)
    {
        face_s.erase( face_s.begin() + toBeDeleted[i]);
    }

    // combining the vector_s and face_s so that we can sort it using the compare() and sort() function
    vector<vector<Vertex>> data_vector;

    for(int i=0;i<face_s.size();i++)
    {
        vector<Vertex> temp; 
        for(int j=0;j<face_s[i].size();j++)
        {
            temp.push_back(vertex_s[face_s[i][j]]);
        }
        data_vector.push_back(temp);
    }

    sort(data_vector.begin(),data_vector.end(),compare);

    // 10% of the faces need to be deleted (see the assumptions stated above)
    int no_of_face_to_delete = floor(data_vector.size()*0.1);

    data_vector.erase(data_vector.begin(),data_vector.begin()+no_of_face_to_delete);

    // set stores the list of index of vertex which needs to be retained
    set<int,greater<int>> vertex_left;
    for(int i=0;i<data_vector.size();i++)
    {
        for(int j=0;j<data_vector[i].size();j++)
        {
            vertex_left.insert(data_vector[i][j].getIndex());
        }
    }
    
    filtered_data = filtered_data + to_string(vertex_left.size()) + "\n"
    + lines[3] + "\n" + lines[4] + "\n" + lines[5] + "\n" 
    + "element face " + to_string(data_vector.size()) + "\n" 
    + lines[7] + "\n" + lines[8] + "\n";

    // updating the vertex_s.
    for(int i=vertex_s.size()-1;i>=0;i--)
    {
        int flag = 0;
        for (auto it = vertex_left.begin(); it != vertex_left.end(); ++it)
        {
            if(vertex_s[i].getIndex() == *it)
            {
                flag = 1;
                break;
            }
        }
        if(flag == 0)
        {
            vertex_s.erase(vertex_s.begin()+i);
        }
    }

    // filtered_data is updated with vertices
    for(int i=0;i<vertex_s.size();i++)
    {
        filtered_data = filtered_data + to_string(vertex_s[i].getX()) + " "
        + to_string(vertex_s[i].getY()) + " "+ to_string(vertex_s[i].getZ()) + "\n";
    }

    // index of the vertices are updated
    // new index = smaller or equal numbers in the set than index
    for(int i=0;i<data_vector.size();i++)
    {
        for(int j=0;j<data_vector[i].size();j++)
        {
            int new_index = NewIndex(data_vector[i][j].getIndex(),vertex_left);
            data_vector[i][j].setIndex(new_index);
        }
    }

    // updating the filtered_data with faces
    for(int i=0;i<data_vector.size();i++)
    {
        filtered_data = filtered_data + to_string(data_vector[i].size()) + " ";
        for(int j=0;j<data_vector[i].size();j++)
        {
            if(j != data_vector[i].size()-1)
                filtered_data = filtered_data + to_string(data_vector[i][j].getIndex()) + " ";
            else
                filtered_data = filtered_data + to_string(data_vector[i][j].getIndex());
        }
        if(i != data_vector.size()-1)
            filtered_data = filtered_data + "\n";
    }
}

int Ply::NewIndex(int old_index, set<int,greater<int>> &vertex_left)
{
    int answer = -1;
    for(auto it = vertex_left.begin(); it != vertex_left.end(); ++it)
    {
        if(*it<=old_index)
        {
            answer++;
        }
    }
    return answer;
}

// according to new compilers the function needs to be static always.
bool Ply::compare(vector<Vertex> a,vector<Vertex> b)
{
    return area(a)<area(b);
}

double Ply::area(vector<Vertex> a)
{
    double x = distance(a[0],a[1]);
    double y = distance(a[1],a[2]);
    double z = distance(a[2],a[0]);
    double p = (x+y+z)/2;

    return sqrt(p*(p-x)*(p-y)*(p-z));
}

double Ply::distance(Vertex a,Vertex b)
{
    return sqrt((a.getX()-b.getX())*(a.getX()-b.getX())
    + (a.getY()-b.getY())*(a.getY()-b.getY())
    + (a.getZ()-b.getZ())*(a.getZ()-b.getZ()));
}

// extracts out the number of faces
void Ply::calcFaces(string line)
{
    stringstream line6(line);
    int integer;
    
    string tok;
    int count = 0;
    while(getline(line6,tok,' ')) 
    {
        if(tok.size()>0)
        {
            count++;
            if(count == 3)
            {
                sscanf(tok.c_str(),"%d",&integer);
                faces = integer;
            }
        }
    }    
}

//makes some basic changes to filtered_data and extracts out the number of vertex
void Ply::calcVertices(string line)
{
    stringstream line2(line);
    int integer;
    
    string tok;
    int count = 0;
    while(getline(line2,tok,' ')) 
    {
        if(tok.size()>0)
        {
            count++;
            if(count == 3)
            {
                sscanf(tok.c_str(),"%d",&integer);
                vertices = integer;
            }
            else
            {
                filtered_data = filtered_data + tok + " ";
            }            
        }
    }
}

// stores the data modified("filtered_data") in a new file.
void Ply::write()
{
    ofstream filteredFile("../files/filtered_file.ply");
    filteredFile << filtered_data;
    filteredFile.close();
    cout << "\n\t\t\u001b[32mNEW FILE \e[3m'filtered_file.ply' \u001b[0m\u001b[32mCONTAINING THE OUTPUT IS SAVED IN \e[3m'files' \u001b[0m\u001b[32mFOLDER" << "\u001b[0m\n" << endl;
}

void Ply::setFileName(string name)
{
    string address = "../files/";
    fileName = address+name;
}

void Ply::setFileNameWithAddress(string name)
{
    fileName = name;
}

// if file opens isValid is set to "true"
bool Ply::isValidFile()
{
    return isValid;
}
