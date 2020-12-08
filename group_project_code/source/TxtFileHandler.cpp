#include <bits/stdc++.h> 
#include <iostream>
#include <fstream>

#include "../include/TxtFileHandler.h"

using namespace std;

// Constructor
TxtFileHandler::TxtFileHandler(string name) {
    fileName = name;
    numOfLines = 0;
    numOfWords = 0;
    numOfChar = 0;
    numOfSpace = 0;
}

// Destructor
TxtFileHandler::~TxtFileHandler() {
    numOfLines = 0;
    numOfWords = 0;
    numOfChar = 0;
    numOfSpace = 0;
    validFile = false;
    inputData.erase();
    outputData.erase();
}

// Copy constructor
TxtFileHandler::TxtFileHandler(const TxtFileHandler& tf) {
    fileName = tf.fileName;
    inputData = tf.inputData;
    outputData = tf.outputData;
    numOfLines = tf.numOfLines;
    numOfWords = tf.numOfWords;
    numOfChar = tf.numOfChar;
    numOfSpace = tf.numOfSpace;
    validFile = tf.validFile;
}

// Reads the data from the file and process the content
void TxtFileHandler::read() {
    fstream inputFile("../files/" + fileName);
    string line;
    
    // Checks if the input file is valid or not
    if(inputFile.is_open())
    {
        validFile = true;
        while(getline(inputFile, line)) {
            inputData = inputData + line; // Input data
            process(line); // Process the content of the line
        }
        inputFile.close(); // Closing the file
    }
    else {
        validFile = false;
        cout << "\u001b[31m\n\t\t\t\t\t\tUNABLE TO OPEN FILE\u001b[0m\n" << endl;
    }
}

// Modifies the data of the file by adding document stats in header and file content in body
void TxtFileHandler::modify() {

    // Adding the document statistics to the header of the output data
    outputData = outputData + "Lines - " + to_string(getNumOfLines()) + "\n";
    outputData = outputData + "Words - " + to_string(getNumOfWords()) + "\n";
    outputData = outputData + "Characters (with spaces) - " + to_string(getNumOfCharWSpace()) + "\n";
    outputData = outputData + "Characters (no spaces) - " + to_string(getNumOfCharWOSpace()) + "\n";
    outputData = outputData + "Bytes - " + to_string(getNumOfBytes()) + "\n\n";

    // Adding the input data to the body of the output data
    outputData = outputData + inputData;
}

// Writing the output data in the output file
void TxtFileHandler::write() {
    ofstream outputFile;
    outputFile.open("../files/Stats_" + fileName);
    outputFile << outputData;
    outputFile.close();
}

// Processes data of each line
void TxtFileHandler::process(string str) {
    numOfLines += 1; // Increasing the number of lines
    countWords(str); // Counts number of words in the line
    countChar(str); // Count number of characters and spaces in the line
}

// Counts the number of words in text
void TxtFileHandler::countWords(string str) { 

    stringstream s(str);
    string word; 

    // While counting words we need to take care of special characters. 
    // Gedit consider any special character as a space 
    // So words like "abc>>xyz" are considered as 2 words instead of one.  
    while (s >> word) {
        bool special = true; // Keeps track if previous character was special char or not. 
        // Before the first char of current word we consider a space so it is true.

        for(int i = 0; i < word.size(); i++) {
            // Checks if current character is a (digit or alphabet) or not
            if(isdigit(word[i]) || isalpha(word[i])) {
                // If previous character was special char then we will increase number of words
                if(special) {
                    numOfWords++; // Increases count of total number of words in data
                }
                special = false; // Current char is not a special character
            }
            else {
                special = true; // Current char is a special character
            }
        }
    }
} 

// Counts the number of characters and spaces in text
void TxtFileHandler::countChar(string str) {
    for(int i = 0; i < str.length(); i++) {
        if(isspace(str[i])) {
            numOfSpace += 1; // Increases count of total number of spaces in data
        }
        else {
            numOfChar += 1; // Increases count of total number of char in data
        }
    }
}