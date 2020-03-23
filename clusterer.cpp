#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <cstdlib>
#include <ios>
#include <stdexcept>
#include <stdio.h>

#include "Image.cpp"

using namespace std;

/* Method used to execute command line operations and return values. Used to read contents of dataset directory */
string exec(string command) {
   char buffer[128];
   string fileContents = "";

   // Open pipe
   FILE* pipe = popen(command.c_str(), "r");
   if (!pipe) {
      return "popen Failed!";
   }

   // Read all files
   while (!feof(pipe)) {
      // Add fileContents to buffer
      if (fgets(buffer, 128, pipe) != NULL)
         fileContents += buffer;
   }

   pclose(pipe);
   return fileContents;
}

int main(int argc, char * argv[]){
    string dataset = argv[1];
    vector<string> datasetFiles;

    string outputArg = "-o";
    string clusterArg = "-k";
    string widthArg = "-bin";

    string outputPath = "./Output/";
    /* Default Values */
    string outputFileName = "Default";
    int numberOfClusters = 10;
    int binSize = 1;

    vector<SLDALE003::Image> images;

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
                binSize = stoi(argv[i+1]);
            }
        }

        cout << "\nCheck Command Line Parameters"
        << "\n-----------------------------------------------\n"
        << "Dataset:\t\t" << dataset 
        << "\nOutput File Name:\t" << outputFileName 
        << "\nNumber Of Clusters:\t" << numberOfClusters 
        << "\nBin Width:\t\t" << binSize 
        << "\n-----------------------------------------------\n\n";

        //Populate datasetFiles with all file names contained in the dataset directory
        string ls = exec("cd "+dataset+" && ls"); //&& is used because it will only move to 'ls' command if 'cd' command works
        stringstream ss(ls);
        istream_iterator<string> begin(ss);
        istream_iterator<string> end;
        vector<string> datasetFiles(begin, end);
        copy(datasetFiles.begin(), datasetFiles.end(), ostream_iterator<string>(cout, "\n"));
    
        for(int i = 0; i < datasetFiles.size(); i++){
            SLDALE003::Image imageInstance;
            string fileInstance = datasetFiles[i];
            imageInstance.loadImage(dataset+"/"+fileInstance);
            images.push_back(imageInstance);
        }

    }
    else{
        cout << "Incorrect Command Line Parameters\n\n";
    }
    
    return 0;
}