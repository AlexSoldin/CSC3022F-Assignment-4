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
            std::string imageName;
            int width;
            int height;
            int size;
            int colourSize;
            std::vector<unsigned char> data;
            std::vector<int> histogram;

        public:
            Image();
            ~Image();

            std::vector<int> getHistogram();
            std::string getImageName();

            void loadImage(std::string fileName, bool colour);
            void generateHistogram(const int binSize);
            double histogramMean(const int binSize);
            double getDistance(Image &other);
            double getDistance(std::vector<int> &other);
            void displayImageGrid(std::vector<unsigned char> toDisplay);
    };
}

#endif