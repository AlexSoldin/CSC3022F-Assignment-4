#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <algorithm>
#include <cstdlib>
#include <ios>
#include <cmath>

#include "Cluster.h"

using namespace std;

SLDALE003::Cluster::Cluster(const vector<int> &centroid, const vector<int> &classification, const vector<string> &stringClassification) : centroid(centroid), classification(classification), stringClassification(stringClassification) {}

SLDALE003::Cluster::Cluster(const vector<int> &centroid) : centroid(centroid) {}

SLDALE003::Cluster::Cluster(){
}

string SLDALE003::Cluster::getClassification(){
    string output = "";
    for(int value: classification){
        output += to_string(value) + " ";
    }
    return output;
}

/* Overload operator<< to Display Images Contained in Cluster */
ostream& operator<<(ostream& os, SLDALE003::Cluster& c){
    os << "cluster " << c.stringClassification[0] << ": "; //first instance is the cluster ID
    for(int i=1; i < c.stringClassification.size(); i++){
        if(i < c.stringClassification.size() - 1)
            os << c.stringClassification[i] << ", ";
        else
            os << c.stringClassification[i];
    }
    return os;
}
