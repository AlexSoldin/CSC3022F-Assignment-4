#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <algorithm>
#include <cstdlib>
#include <ios>

#include "Image.h"

using namespace std;

void SLDALE003::Image::loadImage(string fileName){

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

        width = columns;
        height = rows;

        cout << "\nWidth: " << width << "\nHeight: " << height << "\nMax Value: " << maxValue << "\n\n";
        
        size = columns * rows * 3;
        data = new unsigned char [size];

        inputFile.read((char*)data, size);
        // displayImageGrid(data);
        generateHistogram(1);

        inputFile.close();
    }
    else{
        cout << "File Not Found\n\n";
    }

}

void SLDALE003::Image::generateHistogram(const int binSize){
    int histogramLength = 256/binSize;
    histogram = new int [histogramLength];
    cout << "Length of Histogram: " << histogramLength << "\nHistogram Data: [";

	for(int i = 0; i < size; i += binSize){
        int index = stoi(to_string(data[i]));
        histogram[index]++;
    }

    for(int i = 0; i < histogramLength; i++){
        cout << histogram[i] << " ";
    }
    cout << "]\n\n";
}

void SLDALE003::Image::displayImageGrid(unsigned char * toDisplay){
    for(int i=0; i<height; i++){
        for(int j=0; j<width; j++){
            string out = to_string(toDisplay[i*height + j]);
            if(out.length() == 3)
                cout << out << "  ";
            if(out.length() == 2)
                cout << out << "   ";
            if(out.length() == 1)
                cout << out << "    ";
        }
       cout << "\n";
    }
    cout << "\n\n";
}

SLDALE003::Image::Image(){
    height = 0;
    width = 0;
}

SLDALE003::Image::~Image(){

}