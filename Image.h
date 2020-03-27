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
            std::vector<unsigned char> data;
            std::vector<int> histogram;

        public:
            Image();
            ~Image();

            std::vector<int> getHistogram();

            void loadImage(std::string fileName);
            void generateHistogram(const int binSize);
            double histogramMean(const int binSize);
            double getDistance(Image &other);
            void displayImageGrid(std::vector<unsigned char> toDisplay);
    };
}

#endif