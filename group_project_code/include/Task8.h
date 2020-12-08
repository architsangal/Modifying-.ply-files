#ifndef TASK8_H
#define TASK8_H
#include <string>
#include <vector>
#include "FileHandler.h"

using namespace std;

class Task8 : public FileHandler
{
	private:
		vector<vector<string>> data;
		string filename;
		size_t col1;
		size_t col2;
		size_t getColNum(string s);
		bool isNumber(const string str);
		bool isColNum(const int col);

	public:
		Task8(string _filename, string _col1, string _col2);
		Task8(const Task8 &obj);
		~Task8();
		void read();
		void write();
		void modify();
		bool isColumnValid(const string str);
		bool fileExists();
		bool isColWithinLimits();
};

#endif