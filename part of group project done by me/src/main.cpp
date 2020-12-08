#include "../include/FileHandler.h"
#include "../include/Ply.h"
#include <iostream>
#include <string>
using namespace std;

int main()
{
    string filename,choice;
    Ply p;

    cout<< "Enter 1 for entering the complete address.\nEnter 2 for entering name of file( it will be assumed that the file is in the folder \"files\")\nEnter you choice : ";
    getline(cin, choice);
    if(choice.size() == 1 && (choice[0]=='1' || choice[0]=='2'))
    {
        if(choice[0]=='1')
        {
            cout<< "Address : ";
            getline(cin, filename);
            p.setFileNameWithAddress(filename);
        }
        else if(choice[0]=='2')
        {
            cout<< "File Name : ";
            getline(cin, filename);
            p.setFileName(filename);
        }

        p.read();

        // if file opens only then these functions are executed
        if(p.isValidFile())
        {
            p.modify();
            p.write();
        }
    }
    else
    {
        cout<< "Invalid Input" << endl;
    }
    
    return 0;
}