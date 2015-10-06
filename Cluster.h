//
// Created by Michael Valdez on 9/19/15.
//

#ifndef PA2_CLUSTER_H
#define PA2_CLUSTER_H
#include "Point.h"
#include <memory>

namespace Clustering {
    typedef Point *PointPtr;


    class Cluster {
        struct Node;
        typedef struct Node *NodePtr;
    public:
        Cluster();

        // The big three: cpy ctor, overloaded operator=, dtor
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

        // - Friends
        const Cluster operator+(const Cluster &rhs);

        const Cluster operator-(const Cluster &rhs);

        const Cluster operator+(const PointPtr &rhs);

        const Cluster operator-(const PointPtr &rhs);

        void check(const PointPtr &rhs) {
            if (head->pt.get() == rhs) {
                std::cout << "Point: " << *head->pt;
                std::cout << "We have a match of points with the same memory address\n";
            }
        }

        int size;
    private:
        typedef std::shared_ptr<Point> smartPointPtr;

        struct Node {
            smartPointPtr pt;
            NodePtr next;

            Node() : pt(nullptr), next(nullptr) { }

            Node(smartPointPtr newPt) : pt(newPt), next(nullptr) { }
        };

        NodePtr head;

        // Custom deleter for the shared smart pointer
        struct Release {
            void operator()(PointPtr p) {
                // Meant to be empty
            }
        };
    };
}
#endif //PA2_CLUSTER_H
