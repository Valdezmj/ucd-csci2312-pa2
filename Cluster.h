//
// Created by Michael Valdez on 9/19/15.
//

// Notes.
// Pass in the point dimensions to cluster in constructors.

#ifndef PA2_CLUSTER_H
#define PA2_CLUSTER_H
#include "Point.h"
#include <memory>

namespace Clustering {
    typedef std::shared_ptr<Point> PointPtr;

    class Cluster {
        struct Node;
        typedef Node *NodePtr;
    public:
        static const char POINT_CLUSTER_ID_DELIM;

        Cluster();
        Cluster(PointPtr &);
        Cluster(unsigned int);


        // The big three: cpy constructor, overloaded operator=, dtor
        Cluster(const Cluster &);

        Cluster &operator=(const Cluster &);

        ~Cluster();

        // Set functions: They allow calling c1.add(c2.remove(p));
        void add(const PointPtr &);

        const PointPtr &remove(const PointPtr &);

        // Overloaded operators

        // IO
        // - Friends
        friend std::ostream &operator<<(std::ostream &, const Cluster &);

        friend std::istream &operator>>(std::istream &, Cluster &);

        // Set-preserving operators (do not duplicate points in the space)
        // - Friends
        bool operator==(const Cluster &rhs);

        // - Members
        Cluster &operator+=(const Point &rhs); // allocate point
        Cluster &operator-=(const Point &rhs); // delete point(s) (greedy)

        // Set-destructive operators (duplicate points in the space)
        // - Members
        Cluster &operator+=(const Cluster &rhs); // union
        Cluster &operator-=(const Cluster &rhs); // (asymmetric) difference

        const Cluster operator+(const Cluster &rhs);

        const Cluster operator-(const Cluster &rhs);

        const Cluster operator+(const PointPtr &rhs);

        const Cluster operator-(const PointPtr &rhs);

        PointPtr &operator[] (int);

        // - Getters
        const Point getCentroid();
        void setCentroid(const Point & __p)  {__centroid = PointPtr(new Point(__p));__centroidValid = true;}
        void computeCentroid();
        const bool checkCentroid() {return __centroidValid;}
        unsigned int getSize() {return size;}
        void setPointDimension(unsigned int x) {pointDimensions = x;}
        unsigned int getPointDimension() {return pointDimensions;}

        void pickPoints(int k, PointPtr *&);

        double intraClusterDistance() const;
        friend double interClusterDistance(const Cluster &, const Cluster &);
        int getClusterEdges() {return (size * (size- 1) / 2);}


        class Move {
            PointPtr __pt;
            Cluster * __to;
            Cluster * __from;
        public:
            Move(const PointPtr a,Cluster *b, Cluster *c) : __pt(a), __to(c), __from(b) {}
            void perform() {__to->add(__from->remove(__pt));}
        };

        unsigned int __id;

    private:
        unsigned int size;
        bool __centroidValid;
        PointPtr __centroid;
        unsigned int pointDimensions;

        static unsigned int __idGenerator;

        struct Node {
            PointPtr pt;
            NodePtr next;

            Node() : pt(nullptr), next(nullptr) { }

            Node(PointPtr newPt) : pt(newPt), next(nullptr) { }
            Node(PointPtr __np, NodePtr __n) : pt(__np), next(__n) { }
        };

        NodePtr head;

        void clearList();
    };
}
#endif //PA2_CLUSTER_H
