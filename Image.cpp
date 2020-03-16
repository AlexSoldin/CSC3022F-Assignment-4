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

    getline(inputFile, line);

    string current = getline(inputFile, line);
    cout << current[0];

    ss >> columns >> rows;

    int maxVal;
    ss >> maxVal;

    width = columns;
    height = rows;

    data = std::make_unique<unsigned char[]>(width * height);

    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            ss >> noskipws >> data.get()[width * i + j];
        }
    }

}