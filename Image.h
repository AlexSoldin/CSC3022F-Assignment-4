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
            int * histogram;

        public:
            Image();
            ~Image();

            void loadImage(std::string fileName);
            void generateHistogram(const int binSize);
            void displayImageGrid(unsigned char * toDisplay);
    };
}

#endif