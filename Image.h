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
        Image(){
            width = 0;
            height = 0;
        }
        void loadImage(std::string fileName);
};

#endif