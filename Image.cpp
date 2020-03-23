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
        
        size = width*height;
        int sizeInput = columns * rows * 3;
        unsigned char * inputData = new unsigned char [sizeInput];

        inputFile.read((char*)inputData, sizeInput);
        inputFile.close();

        /* Colour Conversion Equation Implementation */
        int sumCounter = 0;
        while(sumCounter < (sizeInput-2)){
            data.push_back(0.21*inputData[sumCounter] + 0.72*inputData[sumCounter+1] + 0.07*inputData[sumCounter+2]);
            sumCounter += 3;
        }

        // cout << fileName << "\n";
        displayImageGrid(data);
        generateHistogram(1);
        // generateHistogram(4);
        cout << "Histogram Mean: " << histogramMean() << "\n\n";
        
    }
    else{
        cout << "File Not Found\n\n";
    }
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
    cout << "Length of Histogram: " << histogramLength << "\nHistogram Data: [ ";
    for(int i = 0; i < histogram.size(); i++){
        cout << histogram[i] << " ";
    }
    cout << "]\n\n";
}

int SLDALE003::Image::histogramMean(){
    int sum = 0;
    for(int i=0; i< histogram.size(); i++){
        sum += histogram[i];
    }
    int mean = sum/histogram.size();
    return mean;
}

void SLDALE003::Image::displayImageGrid(vector<unsigned char>toDisplay){
    // When colour conversion is implemented, can see the PPM image clearly
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
    size = 0;
}

SLDALE003::Image::~Image(){}

vector<int> SLDALE003::Image::getHistogram(){
    return histogram;
}