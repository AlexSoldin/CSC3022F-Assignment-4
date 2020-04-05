# README for CSC3022F Assignment 4

## clusterer.cpp


## Cluster.cpp
This class is used to group different images that form a cluster. This class contains multiple variables and constructors for a cluster as well as the overloading of the operator<< as specified in the assignment brief. These variables and methods include:

* Public Variables
    * std::vector<int> centroid;
    * std::vector<int> classification;
    * std::vector<string> stringClassification;
* Methods
    * Cluster(const vector<int> &centroid, const vector<int> &classification, const vector<string> &stringClassification);
    * Cluster(const vector<int> &centroid);
    * Cluster();
    * string getClassification();
    * friend ostream &operator<<(ostream &os, const Cluster &c);


## Cluster.h
This class contains all the method calls held in Cluster.cpp.

## Image.cpp
This class holds all the data pertaining to an individual image. This includes reading in the image data and generating a histogram according to a specified bin size.

## Image.h
This class contains all the method calls held in Image.cpp.

## Additional Feature



## Makefile
The Makefile compiles and links all necessary files into the clusterer executable. 

The input is of the form: ./clusterer [ dataset] [ -o output file base name] [ -k number of clusters] [ -bin bin width] [ -colour] [- INSERT]
* -colour argument instructs the program to utilise the RGB values images instead of converting them to greyscale
* INSERT arguement instructs the program to generate a different feature as described in the Additional Feature Section above

Some examples have been commented out in the Makfile. The main commands include:
* make - compiles files
* make run - runs executable according to specific instruction
* make clean - removes executables