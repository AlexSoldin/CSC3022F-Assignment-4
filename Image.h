#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <cstdlib>
#include <ios>
#include <memory>

#ifndef IMAGE_H
#define IMAGE_H

namespace SLDALE003{
    class Image{
        private:
            int width;
            int height;
            int size;
            unsigned char * data;
            int histogramLength;
            int * histogram;

        public:
            Image();
            ~Image();

            void loadImage(std::string fileName);
            void generateHistogram(const int binSize);
            int histogramMean(const int * histogram, const int histogramLength);
            void displayImageGrid(unsigned char * toDisplay);
    };
}

#endif