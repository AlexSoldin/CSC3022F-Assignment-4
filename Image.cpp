#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <cstdlib>
#include <ios>

#include "Image.h"

using namespace std;

void Image::loadImage(string fileName){

    int rows = 0;
    int columns = 0;

    ifstream inputFile(fileName, ios::binary);
    std::stringstream ss;
    string line = "";

    if(inputFile){
        getline(inputFile, line);

        ss << inputFile.rdbuf();
        ss >> columns >> rows;

        int maxValue;
        ss >> maxValue;
        // cout << maxValue << "\n\n";

        int width = columns;
        int height = rows;
        // cout << width << " " << height << "\n\n";



        inputFile.close();
    }
    else{
        cout << "File Not Found" << "\n\n";
    }

}

Image::Image(){
    height = 0;
    width = 0;
}

Image::~Image(){
    
}