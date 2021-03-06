#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <cstdlib>
#include <ios>
#include <memory>

#ifndef CLUSTER_H
#define CLUSTER_H

namespace SLDALE003{
    class Cluster{
        public:
            std::vector<int> centroid;
            std::vector<int> classification;
            std::vector<std::string> stringClassification;

            Cluster(const std::vector<int> &centroid, const std::vector<int> &classification, const std::vector<std::string> &stringClassification);
            Cluster(const std::vector<int> &centroid);
            Cluster();

            std::string getClassification();
            friend std::ostream &operator<<(std::ostream &os, const Cluster &c);
            
    };
}

#endif