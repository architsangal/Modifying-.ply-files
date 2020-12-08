#ifndef TxtFileHandler_H
#define TxtFileHandler_H

#include <iostream>
#include <fstream>
#include "FileHandler.h"

using namespace std;

class TxtFileHandler: public FileHandler {

    public:
    TxtFileHandler(string name);
    ~TxtFileHandler();
    TxtFileHandler(const TxtFileHandler& tf);

    void read(); // Reads the data from the file and process the content
    void modify(); // Modifies the data of the file by adding document stats in header and file content in body
    void write(); // Writing the output data in the output file

    int getNumOfLines() { return numOfLines; } // Number of lines in data
    int getNumOfWords() { return numOfWords; } // Number of words in data
    int getNumOfCharWSpace() { return numOfChar + numOfSpace + numOfLines - 1; } // Number of characters with spaces in data
    int getNumOfCharWOSpace() { return numOfChar; } // Number of characters without spaces in data
    int getNumOfBytes() { return numOfChar + numOfSpace + numOfLines - 1; } // Number of bytes of data

    bool isValidFile() { return validFile; } // Validity of input file

    private:
    string fileName;
    string inputData, outputData;
    int numOfLines, numOfWords, numOfChar, numOfSpace;

    bool validFile;

    void process(string str); // Processes data of each line
    void countWords(string str); // Counts the number of words in text
    void countChar(string str); // Counts the number of characters and spaces in text

};

#endif