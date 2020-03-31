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

void SLDALE003::Image::loadImage(string fileName){

    size_t pos = fileName.find("/") + 1;
    imageName = fileName.substr(pos);
    imageName = imageName.substr(0, imageName.length() - 4); //remove the file extension/type

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

        // cout << "\nWidth: " << width << "\nHeight: " << height << "\nMax Value: " << maxValue << "\n\n";
        
        size = width*height;
        int sizeInput = columns * rows * 3;
        // vector<unsigned char> inputData;

        unsigned char * inputData = new unsigned char [sizeInput];
        // vector<unsigned char> inputData;

        inputFile.read((char*)inputData, sizeInput);
        // unsigned char instance = 0;
        // while(!inputFile.eof()){
        //     inputFile >> instance >> ws; //ignores whitespace and adds each value to int vector
        //     inputData.push_back(instance);
        // }

        inputFile.close();

        /* Colour Conversion Equation Implementation */
        int sumCounter = 0;
        while(sumCounter < (sizeInput-2)){
            data.push_back(0.21*inputData[sumCounter] + 0.72*inputData[sumCounter+1] + 0.07*inputData[sumCounter+2]);
            sumCounter += 3;
        }

        // cout << imageName << "\n";
        // displayImageGrid(data);
        
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
    // cout << "Length of Histogram: " << histogramLength << "\nHistogram Data: [ ";
    // for(int i = 0; i < histogram.size(); i++){
    //     cout << histogram[i] << " ";
    // }
    // cout << "]\n\n";
}

vector<int> SLDALE003::Image::getHistogram(){
    return histogram;
}

double SLDALE003::Image::histogramMean(int binSize){
    double sum = 0;
    for(int i = 0; i < histogram.size(); i++){
        sum += histogram[i] * (i*binSize);
    }
    double mean = sum / histogram.size();
    // cout << "Histogram Mean: " << mean << "\n\n"; 
    return mean;
}

/* Squared Euclidean Distance for an Image */
double SLDALE003::Image::getDistance(Image &other){
    double squareDistance = 0;
    for(int i = 0; i < histogram.size(); i++){
        int value = other.histogram[i] - histogram[i];
        squareDistance += pow(value, 2);
    }
    return squareDistance;
}

/* Squared Euclidean Distance for a Vector */
double SLDALE003::Image::getDistance(vector<int> &other){
    double squareDistance = 0;
    for(int i = 0; i < histogram.size(); i++){
        int value = other[i] - histogram[i];
        squareDistance += pow(value, 2);
    }
    return squareDistance;
}

void SLDALE003::Image::displayImageGrid(vector<unsigned char> toDisplay){
    // When colour conversion is implemented, can see the PPM image
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