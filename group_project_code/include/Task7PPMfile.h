#ifndef TASK7PPMFILE_H
#define TASK7PPMFILE_H

class Task7PPMfile 
{  
    public:
        Task7PPMfile(){;};
        ~Task7PPMfile(){
            delete threeChan;
        }
        friend std::istream& operator >>(std::ifstream& inputStream, Task7PPMfile& img);
        friend std::ostream& operator <<(std::ofstream& outputStream, const Task7PPMfile& img);
        void grayscale();
            // feel free to add more if you want!

        std::string MagicNumber; // A "magic number" for identifying the file type
        int width; // Width of the image
        int height; // Height of the image
        int MaxColorVal; // Maximum color value
        char *threeChan; // A series of rows and columns (raster) that stores important binary image data
};

#endif
