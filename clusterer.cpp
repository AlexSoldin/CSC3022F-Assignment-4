#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <cstdlib>
#include <ios>

#include "Image.h"

using namespace std;

int main(int argc, char * argv[]){
    string dataset = argv[1];

    string outputArg = "-o";
    string clusterArg = "-k";
    string widthArg = "-bin";

    string outputPath = "./Output/";
    /* Default Values */
    string outputFileName = "Defualt";
    int numberOfClusters = 10;
    int binWidth = 1;

    Image image;

    if(argc > 2){
        for(int i = 2; i < argc; i++){
            // cout << "argv[" << i << "] = " << argv[i] << endl;
            string current = argv[i];

            if(current.compare(outputArg) == 0){
                outputFileName = argv[i+1];
            }
            if(current.compare(clusterArg) == 0){
                numberOfClusters = stoi(argv[i+1]);
            }
            if(current.compare(widthArg) == 0){
                binWidth = stoi(argv[i+1]);
            }
        }

        cout << "\nCheck Command Line Parameters"
        << "\n----------------------------------------\n"
        << "Dataset:\t\t" << dataset 
        << "\nOutput File Name:\t" << outputFileName 
        << "\nNumber Of Clusters:\t" << numberOfClusters 
        << "\nBin Width:\t\t" << binWidth 
        << "\n----------------------------------------\n\n";

        image.loadImage(dataset+"/eight_1.ppm");

    }
    else{
        cout << "Incorrect Command Line Parameters";
    }

    return 0;

}