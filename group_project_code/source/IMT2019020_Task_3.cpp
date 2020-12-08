#include "../include/IMT2019020_Task_3.h"
#include <fstream>
#include <iostream>
#include <string>

//Task 3
//Read the file.
//Store the data from the file as a table/matrix, including the row and column field names,
//if any, and transpose it.
//Output the transposed table in .csv format.

using namespace std;

//defining constructors
Task3::Task3(){}
Task3::Task3(string infile,string outfile)
{
  row = 0;
  column = 0;
  matrix = new string*[10000] ;
  for(long int i = 0 ; i < 10000 ; i++)
  {
    matrix[i] = new string[10000] ;
  }
  transpose = new string*[10000] ;
  for(long int i = 0 ; i < 10000 ; i++)
  {
    transpose[i] = new string[10000] ;
  }
  filename = infile;
  csvfile = outfile;
}
//defining copy constructor
Task3::Task3(const Task3& task3)
{
  filename = task3.filename;
  csvfile = task3.csvfile;
  row = task3.row;
  column = task3.column;
  matrix = new string*[10000];
  for (long int i = 0 ; i < 10000 ; i++)
  {
    matrix[i] = new string[10000] ;
  }
  for (long int i = 0; i < 10000; i++)
  {
    for (long int j = 0; j < 10000; j++)
    {
	     matrix[i][j] = task3.matrix[i][j];
    }
  }
  transpose = new string*[10000];
  for (long int i = 0 ; i < 10000 ; i++)
  {
    transpose[i] = new string[10000] ;
  }
  for (long int i = 0; i < 10000; i++)
  {
    for (long int j = 0; j < 10000; j++)
    {
  	  transpose[i][j] = task3.transpose[i][j];
    }
  }
}
//defining destructor
Task3::~Task3()
{
  for (long int i = 0 ; i < 10000 ; i++)
    delete[] matrix[i] ;
  delete[] matrix ;
  for (long int i = 0 ; i < 10000 ; i++)
    delete[] transpose[i] ;
  delete[] transpose ;
  row = 0 ; column = 0 ;
}
//reading data from data file
void Task3::read()
{
  int i = 0;
  size_t pos;
  ifstream source;
  source.open("../files/" + filename);
  if(source.is_open())
  {
     int j;
     string line,mat;
     while (getline(source, line))
     {
        j = 0;
        while((pos = line.find(',')) != std::string::npos)  //seperating data with respect to comma
        {
           matrix[i][j].assign(line.substr(0, pos));   //storing data into matrix
           j++;
           line.erase(0, pos + 1);
        }
        matrix[i][j].assign(line.substr(0, line.length()));
        j++;
        i++;
     }
     row = i;
     column = j;
     source.close();
  }
  else
  {
    cout << "\u001b[31m\n\t\t\t\t\t\tUNABLE TO OPEN FILE\u001b[0m\n" << endl;
  }
}

//modifying data i.e.., transposing the data
void Task3::modify()
{
  for(long int i = 0; i < row; i++)
  {
    for (long int j = 0; j < column; j++)
    {
         transpose[j][i] = matrix[i][j];
    }
  }
}
//writing the transposed data to .csv file
void Task3::write()
{
    ofstream source;
    source.open("../files/Transposed_" + csvfile);
    if(source.is_open())
    {
      for(int i = 0; i < column ; i++)
      {
        for(int j = 0 ; j < row ; j++)
        {
          source << transpose[i][j];
          if(j != row - 1) source << ",";
        }
        source << "\n";
      }
      source.close();
    	cout << "\n\t\t\u001b[32mTRANSPOSED DATA IS IN A NEW FILE \e[3m'Transposed_" << filename << "'\u001b[0m\u001b[32m WHICH IS SAVED IN \e[3m'files'\u001b[0m \u001b[32mFOLDER\u001b[0m\n" << endl;

    }
    else
    {
      cout << "\u001b[31m\n\t\t\t\t\t\tUNABLE TO OPEN FILE\u001b[0m\n" << endl;
    }
}
