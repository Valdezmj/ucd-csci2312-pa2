//
// Created by Michael Valdez on 9/19/15.
//

#ifndef PA2_CLUSTER_H
#define PA2_CLUSTER_H
#include "Point.h"
namespace Clustering {
    typedef Point * PointPtr;


    class Cluster {
        struct Node;
        typedef struct Node * NodePtr;
    public:
        Cluster();

        // The big three
        Cluster(const Cluster& clust);
        Cluster &operator=(const Cluster & clust);
        Cluster &operator+(const Cluster & rightSide);
        Cluster &operator-(const Cluster & rightSide);
        bool operator==(const Cluster & rightSide);
        Cluster &operator+=(const Cluster & rightSide);
        Cluster &operator-=(const Cluster & rightSide);
        Cluster &operator+(Point & point);
        Cluster &operator-(Point & point);



        ~Cluster();

        friend std::ostream &operator<<(std::ostream &, const Cluster &);
        void add(const PointPtr &pt);
        const PointPtr remove(const PointPtr pt);
        int size;
    private:
         struct Node {
            PointPtr pt;
            NodePtr next;
        };
        NodePtr head;

    };
}

#endif //PA2_CLUSTER_H
