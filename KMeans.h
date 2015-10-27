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
        void assignPointsIntially();
//        Create a cluster point_space (the rest OPTIONAL) with __release_points set to true
//        Open data file and read in points into point_space
//        Pick k points to serve as initial centroids
//        Create k-1 empty clusters (the rest OPTIONAL) with __release_points set to false
//        Set the centroids of the the k clusters to the k points that were picked
//                Create double score, double scoreDiff
//        Set scoreDiff = SCORE_DIFF_THRESHOLD + 1
//                ---------------------------------------
//                        loop until scoreDiff < SCORE_DIFF_THRESHOLD
//                loop through all clusters
//                loop through all points
//                find the min distance(point, centroid)
//        if centroid not of current cluster
//                perform move(point, current, other)
//        loop through all clusters
//        if centroid invalid
//        compute and set valid to true
//        compute new clustering score
//        compute absolute difference and set scoreDiff
//        ---------------------------------------
//        write out the clustering results to a file
//                (OPTIONAL) move all points back to point_space by setting all other centroids to infinity
//        delete all clusters




    };
}

#endif //PA2_KMEANS_H
