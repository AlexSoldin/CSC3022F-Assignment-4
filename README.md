# README for CSC3022F Assignment 4

## clusterer.cpp
This is the driver class of this assignment. This class reads in all images from the specified dataset and stores them in vector of Image objects. From this vector, the histograms for each image can be calculated. Once all the images have been processed, k-means clustering is performed. Each cluster is represented by a Cluster object. After each initial cluster has been assigned, the clustering process occurs. The varaibles and methods in this class include:

* Public Variables
```cpp
    vector<SLDALE003::Image> images;
    vector<vector <int>> histograms;
    vector<SLDALE003::Cluster> clusters;
```
* Methods
```cpp
    string exec(string command);
    void createClusters(const int numClusters);
    void populateClusters();
    vector<int> calculateCentroid(SLDALE003::Cluster &c);
    void generateOutput(const string outputFileName);
    int main(int argc, char * argv[]);
```

## Cluster.cpp
This class is used to group different images that form a cluster. This class contains multiple variables and constructors for a cluster as well as the overloading of the operator<< as specified in the assignment brief. These variables and methods include:

* Public Variables
```cpp
    vector<int> centroid;
    vector<int> classification;
    vector<string> stringClassification;
```
* Methods
```cpp
    Cluster(const vector<int> &centroid, const vector<int> &classification, const vector<string> &stringClassification);
    Cluster(const vector<int> &centroid);
    Cluster();
    string getClassification();
    friend ostream &operator<<(ostream &os, const Cluster &c);
```


## Cluster.h
This class contains all the method calls held in Cluster.cpp.

## Image.cpp
This class holds all the data pertaining to an individual image. This includes reading in the image data and generating a histogram according to a specified bin size. These variables and methods include:

* Private Variables
```cpp
    string imageName;
    int width;
    int height;
    int size;
    int colourSize;
    vector<unsigned char> data;
    vector<int> histogram;
```
* Methods
```cpp
    Image();
    ~Image();
    vector<int> getHistogram();
    string getImageName();

    void loadImage(string fileName, bool colour);
    void generateHistogram(const int binSize);
    double histogramMean(const int binSize);
    void displayImageGrid(vector<unsigned char> toDisplay);
```

## Image.h
This class contains all the method calls held in Image.cpp.

## Additional Feature
I did explore using additional feautures to classify the images such as applying filters to the images or using techniques such as thresholding and masking. However, I did not beleive that any of the explored techniques yielded greater performance when clustering the images.


## Makefile
The Makefile compiles and links all necessary files into the clusterer executable. 

The input is of the form: ./clusterer [ dataset] [ -o output file base name] [ -k number of clusters] [ -bin bin width] [ -colour] [- INSERT]
* -colour argument instructs the program to utilise the RGB values images instead of converting them to greyscale
* INSERT argument instructs the program to generate a different feature as described in the Additional Feature Section above

Some examples have been commented out in the Makfile. The main commands include:
* make - compiles files
* make run - runs executable according to specific instruction
* make clean - removes executables