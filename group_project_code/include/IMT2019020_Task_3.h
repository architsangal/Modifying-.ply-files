#ifndef Task3_H
#define Task3_H
#include "FileHandler.h"
#include <string>
#include <fstream>

using namespace std;

class Task3:public FileHandler
{
   //data members
   string filename;      //data file
   string csvfile;       //.csv file we are transposing the data to
   long int row;
   long int column;
   string **matrix;     //matrix that stores the data which we are reading
   string **transpose;  //transposed matrix of the matrix


	public:
    Task3();   //constructor
    Task3(string infile,string outfile);  //constructor
    Task3(const Task3& task3);  //copy constructor
    ~Task3();  //destructor

   //virtual function,binded at run time
  public:
	  void read();
		void write();
		void modify();

    //get methods
    long int getRow()
    {
      return row;
    }
    long int getColumn()
    {
      return column;
    }
    string getMatrix()
    {
      return matrix[10000][10000];
    }
    string getTranspose()
    {
      return transpose[10000][10000];
    }
};

#endif
