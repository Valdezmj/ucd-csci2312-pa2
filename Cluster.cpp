//
// Created by Michael Valdez on 9/19/15.
//

#include "Cluster.h"
#include <sstream>
#include <cassert>
#include <cmath>
#include <memory>

namespace Clustering {
    const char Cluster::POINT_CLUSTER_ID_DELIM = ':';
    unsigned int Cluster::__idGenerator = 1;

    Clustering::Cluster::Cluster() {
        __id = __idGenerator;
        Cluster::__idGenerator++;
        __centroid = nullptr;
        __centroidValid = false;
        size = 0;
        head = nullptr;
    }
    Clustering::Cluster::Cluster(unsigned int i) {
        __id = __idGenerator;
        Cluster::__idGenerator++;
        __centroid = nullptr;
        __centroidValid = false;
        size = 0;
        head = nullptr;
        pointDimensions = i;
    }

    Clustering::Cluster::Cluster(const Clustering::Cluster &__cl) {
        NodePtr __n;
        NodePtr __c;
        NodePtr __l;
        if (__cl.head != nullptr) {
            __centroid = __cl.__centroid;
            __centroidValid = __cl.__centroidValid;
            head = new Node;
            size = __cl.size;
            __c = __cl.head;
            head->pt = __c->pt;
            __l = head;
            __c = __c->next;
            for (int i = 1; i < __cl.size; i++) {
                __n = new Node(__c->pt);
                __l->next = __n;
                __l = __l->next;
                __c = __c->next;
            }
            __l->next = nullptr;
        } else {
            head = nullptr;
        }
    }

    Cluster::Cluster(PointPtr &__ptr) :  __centroid(__ptr) {
        Cluster(__ptr->getDims());

    }

    void Clustering::Cluster::add(const Clustering::PointPtr &__pt) {
        NodePtr __new = new Node(__pt);
        if (head != nullptr) {
            NodePtr __c = head;
            NodePtr __p = head;
            while (__c != nullptr) {
                if (*__new->pt <= *__c->pt) {
                    if (__c == head) {
                        head = __new;
                        __new->next = __c;
                        break;
                    } else {
                        __p->next = __new;
                        __new->next = __c;
                        break;
                    }
                } else {
                    if (__c->next != nullptr) {
                        __p = __c;
                        __c = __c->next;
                    } else {
                        __c->next = __new;
                        break;
                    }
                }
            }

        } else {
            head = __new;
        }
        size++;
    }

    std::ostream &operator<<(std::ostream & os, const Cluster & __cl) {
        if(__cl.size == 0) {
            return os;
        }
        Cluster::NodePtr __s = __cl.head;
        for (int i = 0; i < __cl.size - 1; i++) {
            os << *__s->pt << " " << __cl.POINT_CLUSTER_ID_DELIM << " " << __cl.__id << std::endl;
            __s = __s->next;
        }
        os << *__s->pt << " " << __cl.POINT_CLUSTER_ID_DELIM << " " << __cl.__id << std::endl;
        return os;
    }

    Clustering::Cluster::~Cluster() {
        clearList();
    }

    const PointPtr &Clustering::Cluster::remove(const Clustering::PointPtr &__pt) {
        if (head != nullptr) {
            NodePtr __p = head, __c = head, __n = __c->next;
            while (__c != nullptr) {
                if (__pt == __c->pt) {
                    if (__c == head) {
                        head = __n;
                    }
                    delete __c;
                    __centroidValid = false;
                    size--;
                    if (__p == nullptr) {
                        head = __n;
                        __c = __n;
                    } else {
                        __c = __n;
                        __p->next = __c;
                        if (__n != nullptr) {
                            __n = __n->next;
                        }
                    }

                } else {
                    __p = __c;
                    __c = __n;
                    if (__n != nullptr) {
                        __n = __n->next;
                    }
                }
            }
        }
        return __pt;
    }

    Cluster &Cluster::operator=(const Cluster &__cl) {
        if (this == &__cl || *this == __cl) {
            // assignment to itself
        } else if(__cl.head == nullptr) {
            //assignment to an empty cluster
            this->clearList();

        } else {
            this->clearList();
            __centroid = __cl.__centroid;
            __centroidValid = __cl.__centroidValid;
            NodePtr __new, __c, __f = __cl.head;
            __new = new Node(__f->pt);
            head = __new;
            __c = head;
            __f = __f->next;

            for (int i = 1; i < __cl.size; i++) {
                __new = new Node(__f->pt);
                __c->next = __new;
                __c = __c->next;
                __f = __f->next;
            }
            size = __cl.size;
        }
        return *this;
    }

    const Cluster Cluster::operator+(const Cluster &__rs) {
        if (*this == __rs) {
            return *this;
        }
        Cluster __nc;
        if (size == 0) {
            __nc = __rs;
        } else {
            __nc = *this;
        }
        NodePtr __x = __rs.head;
        NodePtr __ncp = __nc.head;
        bool __a = true;
        for (int i = 0; i < __rs.size; i++) {
            for (int j = 0; j < __nc.size; j++) {
                if (__x->pt == __ncp->pt) {
                    __a = false;
                    break;
                } else {
                    __ncp = __ncp->next;
                }
            }
            if (__a) {
                __nc.add(__x->pt);
            }
            __x = __x->next;
            __ncp  = __nc.head;
            __a = true;
        }
        return __nc;
    }

    const Cluster Cluster::operator-(const Cluster &__rs) {
        Cluster __nc(*this);
        if (*this == __rs) {
            __nc.clearList();
            return __nc;
        }

        NodePtr __nst = __rs.head;
        NodePtr __nl;
        __nl = __nc.head;

        for (int i = 0; i < __rs.size; i++) {

            for (int j = 0; j < __nc.size; j++) {

                if (*__nst->pt == *__nl->pt) {
                    __nc.remove(__nst->pt);
                    break;
                }
                __nl = __nl->next;
            }

                __nst = __nst->next;
                __nl = __nc.head;
        }

        return __nc;
    }

    bool Cluster::operator==(const Cluster &rightSide) {
        if (size < rightSide.size || size > rightSide.size) {
            return false;
        }
        NodePtr nodeCheckSetOne = head;
        NodePtr nodeCheckSetTwo = rightSide.head;
        for (int i = 0; i < size; i++) {
            if (nodeCheckSetOne->pt != nodeCheckSetTwo->pt) {
                return false;
            }
            nodeCheckSetOne = nodeCheckSetOne->next;
            nodeCheckSetTwo = nodeCheckSetTwo->next;
        }
        return true;
    }

    Cluster &Cluster::operator+=(const Cluster &rightSide) {
        if (this == &rightSide) {
            return *this;
        }
        *this = (*this + rightSide);
        __centroidValid = false;
        return *this;
    }

    Cluster &Cluster::operator-=(const Cluster &rightSide) {
        if (this == &rightSide) {
            return *this;
        }
        *this = (*this - rightSide);
        __centroidValid = false;
        return *this;
    }

    const Cluster Cluster::operator+(const PointPtr &point) {
        Cluster newCluster(*this);

        newCluster.add(point);
        return newCluster;
    }

    const Cluster Cluster::operator-(const PointPtr &point) {
        Cluster newCluster(*this);

        newCluster.remove(point);
        return newCluster;
    }

    Cluster &Cluster::operator+=(const Point &__P) {
        PointPtr test = PointPtr(new Point(__P));
        add(test);
        __centroidValid = true;
        return *this;
    }

    Cluster &Cluster::operator-=(const Point &rhs) {
        NodePtr loopNodeFirst, loopNodeSecond;
        loopNodeSecond = head;
        for (int i = 0; i < size; i++) {
            if (*loopNodeSecond->pt == rhs) {
                if (loopNodeSecond == head) {
                    loopNodeFirst = loopNodeSecond;
                    loopNodeSecond = loopNodeSecond->next;
                    head = loopNodeSecond;
                    delete loopNodeFirst;
                } else {
                    loopNodeFirst->next = loopNodeSecond->next;
                    delete loopNodeSecond;
                    loopNodeSecond = loopNodeFirst->next;
                }
                i--;
                size--;
            } else {
                loopNodeFirst = loopNodeSecond;
                loopNodeSecond = loopNodeSecond->next;
            }
        }
        __centroidValid = false;
        return *this;
    }

    void Clustering::Cluster::clearList() {
        // Check to see if the list is empty.
        if (head != nullptr) {
            if (size > 1) {
                // If it isn't create a loopNode that you will use to to obtain 1 node ahead of
                // the head node (or first node).
                NodePtr __l = head->next;

                // notice in this for loop I do size - 1.  Which means I only want to loop through 1 less than the total size.
                // You'll see why in the for loop.
                for (int i = 0; i < size - 1; i++) {
                    // delete the node.
                    delete head;

                    // This next block is where the size - 1 comes into play with our for loop.
                    // If the next node after our second node (remember, head -> loopNode -> (this is the node we care about).
                    // If there is no Node after loopNode (loopNode->next == nullptr) we don't increment loopNode like we
                    // would usually do but instead assign head to loopNode and do the standard procedure of deleting a
                    // node and its contents.
                    if (__l != nullptr) {
                        if (__l->next != nullptr) {  // Only gets in here if loopNode points to another node (not nullptr).
                            head = __l;
                            __l = __l->next;
                        }
                        else { // This block only gets executed when we are at the end of the list.
                            // Where loopNode is pointing to the last node in the list and head is pointing to the
                            // second to last node.
                            head = __l;
                            delete head;
                        }
                    }

                }
            } else {
                delete head;
            }
            __centroidValid = false;
            head = nullptr;
            size = 0;
        }
    }

    std::istream &operator>>(std::istream &istream, Cluster &cluster) {
        // check if the stream is failing
        assert(!istream.fail());

        std::string value;              // Used to store the getline below- no use except for counting
        std::string line;
        std::getline(istream, line);

        // Set the string we are going to parse
        std::stringstream streamToPoint;
        streamToPoint.str(line);

        // Create our new point
        Point newPoint((int)cluster.pointDimensions);

        // clear the buffer and re assign the same string we want to pass to our new point
        // for it to parse
        streamToPoint.clear();
        streamToPoint.str(line);

        // Stream input to the new point
        streamToPoint >> newPoint;

        // Add the new point
        cluster += newPoint;
        return istream;
    }

    void Cluster::computeCentroid() {
        if (head != nullptr) {
            NodePtr __n = head;
            __centroid = nullptr;
            __centroid = PointPtr(new Point(pointDimensions));
            for (int i = 0; i < pointDimensions; i++) {
                __centroid->setDimensionValue(i + 1, 0);
            }
            while (__n != nullptr) {
                *__centroid += *__n->pt;
                __n = __n->next;
            }
            *__centroid /= (int)size;
        } /*else {
            __centroid = nullptr;
            __centroidValid = false;
        }*/
        __centroidValid = true;
    }

    void Cluster::pickPoints(int k, PointPtr *&pointArray) {
        // add exception to handle when cluster has no points to pick from
        if (size == 0) {
            std::cerr << "You tried to pick points from an empty cluster returning an empty list\n";
            return;
        }
        pointArray = new PointPtr[k];
        if (head != nullptr) {
            int __s, __inc, __pp;
            // Decide a good starting point to pick points
            if (size < 2) {
                __s = 0;
                __inc = 1;
            } else {
                __s = 1;
                __inc = 2;
            }

            __pp = 0;
            for (int i = __s; i < size; i += __inc) {
                if (__pp < k) {
                    pointArray[__pp] = (*this)[i];
                    __pp++;
                }
            }
            if (__pp < k) {
                double __inf [pointDimensions];
                for (int i = 0; i < pointDimensions; i++) {
                    __inf[i] = std::numeric_limits<double>::max();
                }
                PointPtr __infinity(new Point(pointDimensions, __inf));
                for (int i = __pp; i < k; i++) {
                    pointArray[i] = __infinity;
                }
            }
        }

    }

    double Cluster::intraClusterDistance() const {
        double __d = 0;
        if (head != nullptr) {
            NodePtr __z = head, __x = head;
            for (int i = 0; i < size; i++) {
                for (int j = 0; j < size; j++) {
                    __d += __z->pt->distanceTo(*__x->pt);
                    __x = __x->next;
                }
                __z = __z->next;
                __x = head;
            }
            __d /= 2;
        }
        return __d;
    }

    double interClusterDistance(const Cluster &__c1, const Cluster &__c2) {
        double __d = 0;
        if (__c1.head != nullptr && __c2.head != nullptr && __c1.pointDimensions == __c2.pointDimensions) {
            Cluster::NodePtr __z = __c1.head, __x = __c2.head;
            for (int i = 0; i < __c1.size; i++) {
                for (int j = 0; j < __c2.size; j++) {
                    __d += __z->pt->distanceTo(*__x->pt);
                    __x = __x->next;
                }
                __z = __z->next;
                __x = __c2.head;
            }
            __d /= 2;
        }
        return __d;
    }

    // 1 based index
    PointPtr &Cluster::operator[](int x) {
        NodePtr __c = head;
        for (int i = 1; i <= x; i++) {
            __c = __c->next;
        }
        return __c->pt;
    }

    const Point Cluster::getCentroid() {
        if (__centroid != nullptr) {
            return *__centroid;
        } else {
            Point empty(0);
            return empty;
        }
    }
}