#include<iostream>
#include <fstream>
#include <cmath>
#include "../include/Task7PPMfile.h"

using namespace std;

istream& operator >>(ifstream& inputStream, Task7PPMfile& img)
{  
    //string fileName;
    //char dump;

    inputStream >> img.MagicNumber >> img.width >> img.height >> img.MaxColorVal;
    inputStream.get();

    size_t memoryBlockSize = img.width * img.height * 3; //This means the size is 3 bytes

    img.threeChan = new char[memoryBlockSize];

    inputStream.read(img.threeChan, memoryBlockSize); //Read data into array
    return inputStream;
}

ostream& operator <<(ofstream& outputStream, const Task7PPMfile& img)
{  

    outputStream << img.MagicNumber << " " << img.width << " " << img.height << " " << img.MaxColorVal << " ";
    outputStream.write(img.threeChan, img.width * img.height * 3);
    return outputStream;
}


void Task7PPMfile::grayscale()
{  
    const float r = 0.3F;
    const float g = 0.59F;
    const float b = 0.11F;

    int s = this->width * this->height * 3;
    for(int i = 0;i<s;i+=3)
    {
        float greyscaleValue = (this->threeChan[i] * r) + (this->threeChan[i+1] * g) + (this->threeChan[i+2] * b);

        this->threeChan[i] = greyscaleValue;
        this->threeChan[i+1] = greyscaleValue;
        this->threeChan[i+2] = greyscaleValue;
    }

}
    

