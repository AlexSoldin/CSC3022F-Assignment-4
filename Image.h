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

class Image{
    private:
        int width;
        int height;
        std::unique_ptr<unsigned char[]> data;
        
    public:
        void loadImage(std::string fileName);
};

#endif