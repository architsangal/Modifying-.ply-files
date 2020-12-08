#include "../include/Task8.h"
#include "../include/Ply.h"
#include "../include/FileHandler.h"
#include "../include/TxtFileHandler.h"
#include "../include/IMT2019020_Task_3.h"
#include "../include/Task7PPMfile.h"
#include <iostream>
#include <string>
#include <bits/stdc++.h>


using namespace std;

void showMenu()			//Display Menu
{
	cout << "\t\t\t1. Read a .csv file and transpose the data" << endl 
		 << "\t\t\t2. Read a .txt file and generate the document statistics (as provided in gedit text editor)" << endl
		 << "\t\t\t3. Read a .ply file and compute the area of each face and sort the faces by area" << endl
		 << "\t\t\t4. Read a .ppm file and convert the image to grayscale" << endl
		 << "\t\t\t5. Read a .csv file and sort the data on the basis of two columns" << endl
		 << "\t\t\t6. Exit " << endl <<  endl;
}

bool Run()
{
	string operation;
	cout << "\t\t\t\e[3m\u001b[33m     Please choose the operation that you wish to perform: \e[0m\u001b[0m";					//Input the operation number
	cin >> operation;
	if(operation != "1" && operation != "2" && operation != "3" && operation != "4" && operation != "5" && operation != "6")		//If the operation is invalid
	{
		cout << endl << "\t\t\t\t\t  \u001b[31mPLEASE CHOOSE A VALID OPERATION!\u001b[0m" << endl << endl;
		return true;
	}
	else if(operation == "6")				//Exit
	{
		return false;
	}
	else
	{
		string filename;
		cout << "\n\t\t\t\t\t   Enter file name: ";		//Input file name
		cin >> filename;
		if(filename.length() < 5)			//If file name is not valid
		{
			cout << "\n\u001b[31m\t\t\t\t\t     FILE TYPE NOT RECOGNIZED\u001b[0m\n" << endl;
			return true;
		}
		else
		{
			if(operation == "5")					//Read a .csv file and sort data on the basis of two columns
			{
				if(filename.substr(filename.length() - 4).compare(".csv") == 0)
				{
					string col1, col2;
					cout << "\t\t\t\t\t  Enter two Column names to sort: ";
					cin >> col1 >> col2;
					Task8 file(filename, col1, col2);
					if(file.fileExists())
					{
						if(file.isColumnValid(col1) && file.isColumnValid(col2))
						{
							file.read();
							if(file.isColWithinLimits())
							{
								file.modify();
								file.write();
							}
							else
							{
								cout << "\u001b[31m\n\t\t\t\t\t\t  INVALID COLUMNS\u001b[0m\n" << endl;
							}
						}
						else
						{
							cout << "\u001b[31m\n\t\t\t\t\t    THE COLUMN NAME IS INCORRECT\u001b[0m\n" << endl;
						}	
					}
					else
					{
						cout << "\u001b[31m\n\t\t\t\t\t\tUNABLE TO OPEN FILE\u001b[0m\n" << endl;
					}
				}
				else
				{
					cout << "\u001b[31m\n\t\t\t\t\t\tNOT A .csv FILE!\u001b[0m\n" << endl;
				}
				return true;
			}
			else if(operation == "2")				//Read a .txt file and generate statistics
			{
				if(filename.substr(filename.length() - 4).compare(".txt") == 0)
				{
					TxtFileHandler f(filename);
					f.read(); // Reads the txt file
					// Modify and write only if input file is valid
					if(f.isValidFile()) {
						f.modify();
						f.write();
						cout << "\n\t\t\u001b[32mNEW FILE \e[3m'Stats_" << filename << "' \u001b[0m\u001b[32mWITH DOCUMENT STATS HAS BEEN ADDED TO \e[3m'files' \u001b[0m\u001b[32mFOLDER\u001b[0m\n" << endl;
					}
				}
				else
				{
					cout << "\u001b[31m\n\t\t\t\t\t\tNOT A .txt FILE!\u001b[0m\n" << endl;
				}
				return true;
			}
			else if(operation == "3")			//Read a .ply file and compute and sort area
			{
				if(filename.substr(filename.length() - 4).compare(".ply") == 0)
				{
					Ply p;
					p.setFileName(filename);
					p.read();
					
					if(p.isValidFile())
					{
						p.modify();
						p.write();
					}
				}
				else
				{
					cout << "\u001b[31m\n\t\t\t\t\t\tNOT A .ply FILE!\u001b[0m\n" << endl;
				}
				return true;
			}
			else if(operation == "1")												//Read a .csv file and transpose it
			{
				if(filename.substr(filename.length() - 4).compare(".csv") == 0)
				{
					ifstream infile("../files/" + filename);
					if(infile.good())
					{
						FileHandler* data = new Task3(filename,filename);
						data->read();      //read
						data->modify();    //modify
						data->write();     //write
						delete data;
					}
					else
					{
						cout << "\u001b[31m\n\t\t\t\t\t\tUNABLE TO OPEN FILE\u001b[0m\n" << endl;
					}
				}
				else
				{
					cout << "\u001b[31m\n\t\t\t\t\t\tNOT A .csv FILE!\u001b[0m\n" << endl;
				}
				return true;
			}
			else if(operation == "4")
			{
				if(filename.substr(filename.length() - 4).compare(".ppm") == 0)
				{
					ifstream infile("../files/" + filename);
					if(infile.good())
					{
						Task7PPMfile t;
						ifstream inStream;
        				ofstream outStream;
        				inStream.open("../files/" + filename, ifstream::binary);
        				inStream >> t;
        				inStream.close();
						string OutputFileName = "Grey_" + filename.substr(0, filename.length() - 3)  + "pgm";
        				t.grayscale();
        				outStream.open("../files/" + OutputFileName, ifstream::binary);
        				outStream << t;
        				outStream.close();
						cout << "\n\t\t\u001b[32mTHE FILE HAS BEEN CONVERTED TO GREYSCALE AND SAVED AS \e[3m'" << OutputFileName << "'\u001b[0m\u001b[32m IN \e[3m'files'\u001b[0m \u001b[32mFOLDER\u001b[0m\n" << endl;

					}
					else
					{
						cout << "\u001b[31m\n\t\t\t\t\t\tUNABLE TO OPEN FILE\u001b[0m\n" << endl;
					}
				}
				else
				{
					cout << "\u001b[31m\n\t\t\t\t\t\tNOT A .ppm FILE!\u001b[0m\n" << endl;
				}
				return true;
			}
		}
	}	
	return true;
}

int main()
{
	cout << endl << "\t\t\t\t\t\u001b[36m\u001b[1m\u001b[4mWELCOME TO FILE MANAGEMENT SYSTEM\u001b[0m" << endl << endl;
	showMenu();
	while(Run())
	{
		showMenu();
	}
	cout << "\n\e[3m\e[1m\u001b[36m\t\t\t\t\t\t   THANK YOU!\e[0m\u001b[0m" << endl << endl;
	return 0;
}