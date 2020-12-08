#include "../include/Task8.h"
#include "../include/FileHandler.h"
#include <sstream>
#include <fstream>
#include <iostream>
#include <algorithm> 
#include <cmath>

using namespace std;

Task8 :: Task8(string _filename, string _col1, string _col2) : FileHandler(), filename(_filename), col1(getColNum(_col1)), col2(getColNum(_col2)) {}	//Constructor

Task8 :: Task8(const Task8 &obj) : filename(obj.filename), col1(obj.col1), col2(obj.col2)		//Copy Constructor
{
	data = obj.data;
}

Task8 :: ~Task8() {}				//Destructor

bool Task8 :: fileExists()			//Checks if the file exists in 'file' folder or not
{
	ifstream infile("../files/" + filename);
	return infile.good();
}

size_t Task8 :: getColNum(string str)		//Function to get column number from name
{
	transform(str.begin(), str.end(), str.begin(), ::toupper); 
	reverse(str.begin(), str.end());
	int colNum = -1;
	for(int i = 0; i < str.size(); i++)
	{
		colNum += (int(str[i]) - 64) * pow(26, i);
	}
	return colNum;
}

bool Task8 :: isNumber(const string str)			//Checks if a string is number or not
{
    if(str.length() == 0)
    {
        return false;
    }
    bool dot = false;
    for(int i = 0; i < str.length(); i++)
    {   
        if(int(str[i]) < 48 || int(str[i]) > 57)
        {
            if(i == 0 && int(str[i]) == 45)
            {
                continue;
            }
            else
            {
                if(dot == false && int(str[i]) == 46)
                {
                    dot = true;
                }
                else
                {
                   return false;
                }
            }
            
        }
    }
    return true;
}

bool Task8 :: isColNum(const int colNum)				//Checks whether the whole column consists of number
{
	for(int i = 0; i < data.size(); i++)
	{
		if(!isNumber(data[i][colNum]))
		{
			return false;
		}
	}
	return true;
}

void Task8 :: read()						//Function to read file
{
	ifstream fin;
	string line, word;
	fin.open("../files/" + filename);
	while(!fin.eof())
	{
		vector<string> temp;
		getline(fin, line, '\n');
		stringstream s(line);
		while(getline(s, word, ','))
		{
			temp.push_back(word);
		}
		data.push_back(temp);
	}
	data.pop_back();
	fin.close();
}

bool Task8 :: isColWithinLimits()		//Function to check the column numbers
{
	if(col1 >= data[0].size() || col2 >= data[0].size() || col1 < 0 || col2 < 0)
	{
		return false;
	}
	return true;
}

void Task8 :: modify()						//Function to sort the data according to 2 columns
{
	bool check1 = isColNum(col1);
	bool check2 = isColNum(col2);
	if(check1 && check2)					//If both the columns have only numbers
	{
		sort(data.begin(), data.end(), [this](vector<string> &l, vector<string> &r)
		{
			if(stof(l[col1]) == stof(r[col1]))
			{
				return stof(l[col2]) < stof(r[col2]);
			}
			return stof(l[col1]) < stof(r[col1]);
		});
	}
	else if(!check1 && !check2)				//If both the columns have atleast one string
	{
		sort(data.begin(), data.end(), [this](vector<string> &l, vector<string> &r)
		{
			if(l[col1] == r[col1])
			{
				return l[col2] < r[col2];
			}
			return l[col1] < r[col1];			
		});	
	}
	else if(!check1 && check2)				//If first column has atleast one string and second column has only numbers
	{
		sort(data.begin(), data.end(), [this](vector<string> &l, vector<string> &r)
		{
			if(l[col1] == r[col1])
			{
				return stof(l[col2]) < stof(r[col2]);
			}
			return l[col1] < r[col1];
		});
	}
	else									//If first column has only numbers and second column has atleast one string
	{
		sort(data.begin(), data.end(), [this](vector<string> &l, vector<string> &r)
		{
			if(stof(l[col1]) == stof(r[col1]))
			{
				return l[col2] < r[col2];
			}
			return stof(l[col1]) < stof(r[col1]);
		});
	}
}

void Task8 :: write()					//Function to create and write in updated file
{
	ofstream outputFile;
	outputFile.open("../files/Sorted_" + filename);

	for(size_t i = 0; i < data.size(); i+= 1)
	{
		for(size_t j = 0; j < data[i].size(); j+= 1)
		{
			if(j != data[i].size()-1)
			{
				outputFile << data[i][j] << ",";
			}
			else
			{
				outputFile << data[i][j] << endl;
			}
		}
	}
	cout << "\n\t\t\u001b[32mDATA IN THE FILE HAS BEEN SORTED AND NEW FILE \e[3m'Sorted_" << filename << "'\u001b[0m\u001b[32m IS SAVED IN \e[3m'files'\u001b[0m \u001b[32mFOLDER\u001b[0m\n" << endl;
	outputFile.close();
}

bool Task8 :: isColumnValid(const string Num)					//Function to check if the column name entered is valid or not
{
	for(int i = 0; i < Num.length(); i++)
	{
		if((int(Num[i]) > 122 || int(Num[i]) < 97) && (int(Num[i]) > 90 || int(Num[i]) < 65))
		{
			return false;
		}
	}
	return true;
}