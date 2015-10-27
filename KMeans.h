//
// Created by Michael Valdez on 10/16/15.
//

#ifndef PA2_KMEANS_H
#define PA2_KMEANS_H

#include "Cluster.h"
#include "Point.h"
#include <string>
namespace Clustering {
    class KMeans {
    public:
        void start();
        KMeans(int, double, unsigned int, std::string, std::string);
        double computeClusteringScore();
        static double SCORE_DIFF_THRESHOLD;
        ~KMeans();


    private:
        Cluster * __ps;
        Cluster * __cl;
        PointPtr * __centroids;
        int __size;
        double __s, __sd;
        std::string __rf, __of;
        void readFile();
        void writeFile();
        void createClusters();
    };
}

#endif //PA2_KMEANS_H
