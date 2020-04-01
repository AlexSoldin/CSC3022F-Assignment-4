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

SLDALE003::Cluster::Cluster(const vector<int> &centroid, const vector<int> &classification) : centroid(centroid), classification(classification) {}

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

ostream& operator<<(ostream& os, SLDALE003::Cluster& c){
    for(int i=0; i < c.classification.size(); i++){
        if(i <= c.classification.size() - 2)
            os << to_string(c.classification[i]) << ", ";
        else
            os << to_string(c.classification[i]);
    }
    return os;
}
