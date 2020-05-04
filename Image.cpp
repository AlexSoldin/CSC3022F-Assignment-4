#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <algorithm>
#include <cstdlib>
#include <ios>
#include <cmath>

#include "Image.h"

using namespace std;

void SLDALE003::Image::loadImage(string fileName, const bool colour, const bool threshold){

    size_t pos = fileName.find("/") + 1;
    imageName = fileName.substr(pos);
    imageName = imageName.substr(0, imageName.length() - 4); //remove the file extension/type

    int rows = 0;
    int columns = 0;

    ifstream inputFile(fileName, ios::binary);
    string line;
    string comment;
    string dimensions;
    string maxValue;

    if(inputFile){
        getline(inputFile, line);

        getline(inputFile, comment);
        while(comment.at(0)=='#'){
            getline(inputFile, comment);
        }
        dimensions = comment;
        
        getline(inputFile, maxValue);
        
        std::stringstream(dimensions) >> columns >> std::ws;
        std::stringstream(dimensions) >> rows >> std::ws;

        width = columns;
        height = rows;

        // cout << "\nWidth: " << width << "\nHeight: " << height << "\nMax Value: " << maxValue << "\n\n";
        
        size = width*height;
        colourSize = columns * rows * 3;

        unsigned char * inputData = new unsigned char [colourSize];
        inputFile.read((char*)inputData, colourSize);
        inputFile.close();

        if(colour & !threshold){
            /* Populate Colour Data Vector */
            for(int i=0; i < colourSize; i++){
                data.push_back(inputData[i]);
            }
        }
        else{
        /* Colour Conversion Equation Implementation */
            int sumCounter = 0;
            while(sumCounter < (colourSize-2)){
                data.push_back(0.21*inputData[sumCounter] + 0.72*inputData[sumCounter+1] + 0.07*inputData[sumCounter+2]);
                sumCounter += 3;
            }
        }

        // View greyscale images
        // cout << imageName << "\n";
        // displayImageGrid(data); 
        
    }
    else{
        cout << "File Not Found\n\n";
    }
}

vector<int> SLDALE003::Image::thresholdImage(){
    vector<int> temp;
    double mean = dataMean();
    for (int i = 0; i < data.size(); i++){
        int value = stoi(to_string(data[i]));
        if(value > mean)
            temp.push_back(255);
        else
            temp.push_back(0);
    }
    return temp;
}

void SLDALE003::Image::generateHistogram(const int binSize){
    int histogramLength = 256/binSize;

    for(int i=0; i<histogramLength;i++){
        histogram.push_back(0);
    }

    if(binSize == 1){
        for(int i = 0; i < data.size(); i++){
            int value = stoi(to_string(data[i]));
            histogram[value]++;
        }
    }
    else{
        vector<int> tempHistogram(data.size(), 0);

        for(int i = 0; i < data.size(); i++){
            int value = stoi(to_string(data[i]));
            tempHistogram[value]++;
        }

        int index = 0;
        for(int i = 0; i < data.size(); i += binSize){
            for(int j = i; j < i+binSize; j++){
                histogram[index] += tempHistogram[j];
            }   
            index++;
        }
    }

    /* Display Histogram */ 
    // cout << "Length of Histogram: " << histogramLength << "\nHistogram Data: [ ";
    // for(int i = 0; i < histogram.size(); i++){
    //     cout << histogram[i] << " ";
    // }
    // cout << "]\n\n";
}

vector<int> SLDALE003::Image::getHistogram(){
    return histogram;
}

double SLDALE003::Image::dataMean(){
    double sum = 0;
    for(int i = 0; i < data.size(); i++){
        sum += stoi(to_string(data[i]));
    }
    double mean = sum / data.size();
    // cout << "Data Mean: " << mean << "\n\n"; 
    return mean;
}

void SLDALE003::Image::displayImageGrid(const vector<unsigned char> toDisplay){
    // When colour conversion is implemented, you can see the PPM image
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
    imageName = "";
    height = 0;
    width = 0;
    size = 0;
}

SLDALE003::Image::~Image(){}

string SLDALE003::Image::getImageName(){
    return imageName;
}