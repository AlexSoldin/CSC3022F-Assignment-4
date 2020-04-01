#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <cstdlib>
#include <ios>
#include <stdexcept>
#include <stdio.h>
#include <cmath>

#include "Image.cpp"
#include "Cluster.cpp"

using namespace std;

vector<SLDALE003::Image> images;
vector<vector <int>> histograms;
vector<double> histogramMeans;

vector<SLDALE003::Cluster> clusters;

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

void createClusters(const int numClusters){
    for(int i=0; i < numClusters; i++){
        SLDALE003::Cluster clusterInstance;
        vector<int> randomHist;
        int r = (rand() % 100);
        randomHist = histograms[r];
        clusterInstance.centroid = {randomHist};
        clusters.push_back(clusterInstance);
    }
}

void populateClusters(){
    double minDistance = 1000000;
    double distance = 0;
    int clusterNumber = 0; //cluster number index for iteration
    int clusterToAssign = 0; //index of the cluster that the image is being assigned to
    int imageIndex = 0; //index of histogram image to be clustered

    for (int i = 0; i < clusters.size(); i++) {
        clusters[i].classification.clear();
    }

    for(auto histogram : histograms){
        minDistance = 1000000;
        clusterNumber = 0;
        
        for(auto cluster : clusters){
            distance = 0;

            for(int i=0; i < histogram.size(); i++){
                double value = cluster.centroid[i] - histogram[i];
                distance += pow(value, 2);
            }
            
            if(distance < minDistance){
                minDistance = distance;
                clusterToAssign = clusterNumber;
            }
            clusterNumber++;
        }
        clusters[clusterToAssign].classification.push_back(imageIndex);
        imageIndex++;
    }
}

vector<int> calculateCentroid(SLDALE003::Cluster &c){
    vector<int> newCentroid(c.centroid.size(), 0);
    for(int imageNumber : c.classification){
        for(int j=0; j < histograms[imageNumber].size(); j++){
            newCentroid[j] += histograms[imageNumber][j];
        }
    }

    for(int i=0; i < c.centroid.size(); i++){
        newCentroid[i] = newCentroid[i]/c.classification.size();
    }

    return newCentroid;
}

/* Main Method */
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

        /* Populate datasetFiles with all file names contained in the dataset directory */
        string ls = exec("cd "+dataset+" && ls"); //&& is used because it will only move to 'ls' command if 'cd' command works
        stringstream ss(ls);
        istream_iterator<string> begin(ss);
        istream_iterator<string> end;
        vector<string> datasetFiles(begin, end);
        // copy(datasetFiles.begin(), datasetFiles.end(), ostream_iterator<string>(cout, "\n")); //not returned in order
    
        for(int i = 0; i < datasetFiles.size(); i++){
            SLDALE003::Image imageInstance;
            imageInstance.loadImage(dataset+"/"+datasetFiles[i]);
            imageInstance.generateHistogram(binSize);
            images.push_back(imageInstance);
            double meanInstance = imageInstance.histogramMean(binSize);
            histograms.push_back(imageInstance.getHistogram());
            histogramMeans.push_back(meanInstance);
        }

        createClusters(numberOfClusters);
        populateClusters();

        bool converge;
        int iteration = 1;

        do {
            converge = true;
            populateClusters();
            cout << "Iteration " << iteration << endl;
            // outFile << "Iteration " << iteration << endl;

            for (int c = 0; c < numberOfClusters; c++) {
                
                vector<int> centroid = calculateCentroid(clusters[c]);
                if (centroid != clusters[c].centroid) {
                    converge = false;
                    clusters[c].centroid = centroid;
                }
                cout << "Cluster " << (c + 1) << ": " << clusters[c] << endl;
                // outFile << "Cluster " << (c + 1) << ": " << clusters[c].getPoints() << endl;
                // outFile << "Centroid " << clusters[c].centroid << endl;
            }
            ++iteration;
            cout << "\n\n";
        } while (!converge);

        for(int i=0; i<clusters.size(); i++){
            cout << "Cluster " << i << ": ";
            for(int j=0; j < clusters[i].classification.size(); j++){
                if(j <= clusters[i].classification.size() - 2)
                    cout << images[clusters[i].classification[j]].getImageName() << ", ";
                else
                    cout << images[clusters[i].classification[j]].getImageName() << "\n";
            }
        }

    }
    else{
        cout << "Incorrect Command Line Parameters\n\n";
    }

    return 0;
}