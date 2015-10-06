//
// Created by Michael Valdez on 9/19/15.
//

#include "Cluster.h"
namespace Clustering {
    Clustering::Cluster::Cluster() {
        size = 0;
        head = nullptr;
    }

    Clustering::Cluster::Cluster(const Clustering::Cluster &clust) {
        NodePtr newNode;
        NodePtr copyNode;
        NodePtr loopNode;
        if (clust.head != nullptr) {
            head = new Node;
            size = clust.size;
            copyNode = clust.head;
            head->pt = copyNode->pt;
            loopNode = head;
            copyNode = copyNode->next;
            for (int i = 1; i < clust.size; i++) {
                newNode = new Node(copyNode->pt);
                loopNode->next = newNode;
                loopNode = loopNode->next;
                copyNode = copyNode->next;
            }
            loopNode->next = nullptr;
        } else {
            head = nullptr;
        }


    }

    void Clustering::Cluster::add(const Clustering::PointPtr &pt) {
        smartPointPtr tempSmartPt(pt, Release());
        if (size != 0) {
            NodePtr placementFinder;
            NodePtr newNode = new Node;
            newNode->pt = tempSmartPt;

            if (*newNode->pt >= *head->pt) {
                if (newNode->pt == head->pt) {
                    return;
                }
                newNode->next = head;
                head = newNode;
                size++;
                return;
            }
            if (head->next == nullptr) {
                newNode->next = nullptr;
                head->next = newNode;
                size++;
                return;
            }
            placementFinder = head;
            while (placementFinder->next != nullptr) {
                if (newNode->pt == placementFinder->pt) {
                    return;
                }
                if (*newNode->pt < *placementFinder->pt) {
                    if (*newNode->pt >= *(placementFinder->next)->pt && newNode->pt != placementFinder->pt) {
                        newNode->next = (placementFinder->next);
                        placementFinder->next = newNode;
                        break;
                    } else if ((placementFinder->next)->next == nullptr) {
                        newNode->next = nullptr;
                        (placementFinder->next)->next = newNode;
                        break;
                    } else {
                        placementFinder = placementFinder->next;
                    }
                } else if (*newNode->pt >= *placementFinder->pt && newNode->pt != placementFinder->pt) {
                    newNode->next = placementFinder;
                    head->next = newNode;
                    break;
                }
            }
            size++;
        } else {
            head = new Node;
            head->next = nullptr;
            head->pt = tempSmartPt;
            size++;
        }
    }

    std::ostream &operator<<(std::ostream & os, const Cluster & clust) {
        if (clust.size == 1) {
            os << "(" << *clust.head->pt << ")";
            return os;
        } else if(clust.size == 0) {
            os << "(no points in clust)";
            return os;
        }
        Clustering::Cluster::NodePtr searchNode = clust.head;
        os << "(";
        while (searchNode->next != nullptr) {
            os << *searchNode->pt << ", ";
            searchNode = searchNode->next;
        }
        os << *searchNode->pt << ")";
        return os;
    }

    Clustering::Cluster::~Cluster() {
        if (size > 0) {
            NodePtr nextNode;
            nextNode = head->next;
            if (nextNode != nullptr) {
                for (int i = 0; i < size; i++) {
                    if (head->pt.unique()) {
                        delete head->pt.get();
                    }
                    delete head;
                    if (i == size - 1) {

                    } else {
                        head = nextNode;
                        nextNode = nextNode->next;
                    }
                }
            } else {
                if (head->pt.unique()) {
                    delete head->pt.get();
                }
                delete head;
            }
        }
    }

    const PointPtr &Clustering::Cluster::remove(const Clustering::PointPtr &pt) {
        NodePtr searchNode = head;
        NodePtr tempNodePtr = head;
        PointPtr tempPt;

        if (head->pt.get() == pt) {
            head = head->next;
            delete tempNodePtr;
            size--;
            return pt;
        }

        for (int i = 0; i < size; i++) {
            if (searchNode->pt.get() == pt) {
                tempNodePtr->next = searchNode->next;
                delete searchNode;
                size--;
                return pt;
            } else {
                tempNodePtr = searchNode;
                searchNode = searchNode->next;
            }
        }
        return pt;
    }

    Cluster &Cluster::operator=(const Cluster &clust) {
        if (this == &clust) {
            return *this;
        }
        if (*this == clust) {
            return *this;
        }
        NodePtr lastNode;
        NodePtr secondToLastNode;
        if (head != nullptr) {
            while (head->next != nullptr) {
                lastNode = head;
                while (lastNode->next != nullptr) {
                    secondToLastNode = lastNode;
                    lastNode = lastNode->next;
                }
                if (lastNode->pt.unique()) {
                    delete lastNode->pt.get();
                }
                delete lastNode;
                secondToLastNode->next = nullptr;
            }
            if (head->pt.use_count() == 0) {
                delete head->pt.get();
            }
            delete head;
        }
        NodePtr assignNode;
        NodePtr assigneeNode;
        size = clust.size;
        head = new Node;
        if (clust.head != nullptr) {
            head->pt = clust.head->pt;
        } else {
            head = clust.head;
            return *this;
        }
        lastNode = head;

        assigneeNode = clust.head->next;
        for (int i = 1; i < size; i++) {

                if (i > 1) {
                    lastNode = assignNode;
                }
                assignNode = new Node;
                lastNode->next = assignNode;
                assignNode->pt = assigneeNode->pt;
                assigneeNode = assigneeNode->next;
        }
        return *this;
    }

    const Cluster Cluster::operator+(const Cluster &rightSide) {
        if (*this == rightSide) {
            return *this;
        }

        Cluster * newCluster = new Cluster(*this);
        NodePtr nodeCheckSetTwo = rightSide.head;
        NodePtr checkNewListNode;
        NodePtr addingPoint;
        checkNewListNode = newCluster->head;
        bool check = true;

        for (int i = 0; i < rightSide.size; i++) {
            for (int j = 0; j < newCluster->size; j++) {
                if (nodeCheckSetTwo->pt == checkNewListNode->pt) {
                    check = false;
                    break;
                }
                checkNewListNode = checkNewListNode->next;
            }
            if (check) {
                checkNewListNode = newCluster->head;
                if (*checkNewListNode->pt <= *nodeCheckSetTwo->pt) {
                    addingPoint = new Node(nodeCheckSetTwo->pt);
                    addingPoint->next = newCluster->head;
                    newCluster->head = addingPoint;
                } else {
                    for (int j = 0; j < newCluster->size; j++) {
                        if (*checkNewListNode->pt > *nodeCheckSetTwo->pt) {
                            if (checkNewListNode->next == nullptr) {
                                addingPoint = new Node(nodeCheckSetTwo->pt);
                                checkNewListNode->next = addingPoint;
                                break;
                            }
                            if (*checkNewListNode->next->pt <= *nodeCheckSetTwo->pt) {
                                addingPoint = new Node(nodeCheckSetTwo->pt);
                                addingPoint->next = checkNewListNode->next;
                                checkNewListNode->next = addingPoint;
                                break;
                            }

                        }
                        checkNewListNode = checkNewListNode->next;
                        //addingPoint = addingPoint->next;
                    }
                }
                newCluster->size++;
            }
            nodeCheckSetTwo = nodeCheckSetTwo->next;
            checkNewListNode = newCluster->head;
            check = true;
        }
        return *newCluster;
    }

    const Cluster Cluster::operator-(const Cluster &rightSide) {
        if (*this == rightSide) {
            return *this;
        }

        Cluster * newCluster = new Cluster(*this);
        NodePtr nodeCheckSetTwo = rightSide.head;
        NodePtr checkNewListNode;
        NodePtr removeNode;
        checkNewListNode = newCluster->head;

        for (int i = 0; i < rightSide.size; i++) {

            for (int j = 0; j < newCluster->size; j++) {

                if (*nodeCheckSetTwo->pt == *checkNewListNode->pt) {
                    newCluster->remove(nodeCheckSetTwo->pt.get());
                    break;
                }
                checkNewListNode = checkNewListNode->next;
            }

                nodeCheckSetTwo = nodeCheckSetTwo->next;
                checkNewListNode = newCluster->head;
        }

        return *newCluster;
    }

    bool Cluster::operator==(const Cluster &rightSide) {
        if (size < rightSide.size || size > rightSide.size) {
            return false;
        }
        NodePtr nodeCheckSetOne = head;
        NodePtr nodeCheckSetTwo = rightSide.head;
        for (int i = 0; i < size; i++) {
            if (nodeCheckSetOne->pt.get() != nodeCheckSetTwo->pt.get()) {
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
        return *this;
    }

    Cluster &Cluster::operator-=(const Cluster &rightSide) {
        if (this == &rightSide) {
            return *this;
        }
        *this = (*this - rightSide);
        return *this;
    }

    const Cluster Cluster::operator+(const PointPtr &point) {
        Cluster * newCluster = new Cluster(*this);

        newCluster->add(point);
        return *newCluster;
    }

    const Cluster Cluster::operator-(const PointPtr &point) {
        Cluster *newCluster = new Cluster(*this);

        newCluster->remove(point);
        return *newCluster;
    }

    Cluster &Cluster::operator+=(const Point &rhs) {
        smartPointPtr tempNode(new Point(rhs));
        if (size != 0) {
            NodePtr placementFinder;
            NodePtr newNode = new Node(tempNode);

            if (*newNode->pt >= *head->pt) {
                if (newNode->pt == head->pt) {
                    return *this;
                }
                newNode->next = head;
                head = newNode;
                size++;
                return *this;
            }
            if (head->next == nullptr) {
                newNode->next = nullptr;
                head->next = newNode;
                size++;
                return *this;
            }
            placementFinder = head;
            while (placementFinder->next != nullptr) {
                if (newNode->pt == placementFinder->pt) {
                    return *this;
                }
                if (*newNode->pt < *placementFinder->pt) {
                    if (*newNode->pt >= *(placementFinder->next)->pt && newNode->pt != placementFinder->pt) {
                        newNode->next = (placementFinder->next);
                        placementFinder->next = newNode;
                        break;
                    } else if ((placementFinder->next)->next == nullptr) {
                        newNode->next = nullptr;
                        (placementFinder->next)->next = newNode;
                        break;
                    } else {
                        placementFinder = placementFinder->next;
                    }
                } else if (*newNode->pt >= *placementFinder->pt && newNode->pt != placementFinder->pt) {
                    newNode->next = placementFinder;
                    head->next = newNode;
                    break;
                }
            }
            size++;
            return *this;
        } else {
            head = new Node;
            head->next = nullptr;
            head->pt = tempNode;
            size++;
            return *this;
        }
    }

    Cluster &Cluster::operator-=(const Point &rhs) {
        NodePtr loopNodeFirst, loopNodeSecond;
        loopNodeSecond = head;
        for (int i = 0; i < size; i++) {
            if (*loopNodeSecond->pt == rhs) {
                if (loopNodeSecond == head) {
                    loopNodeFirst = loopNodeSecond;
                    loopNodeSecond = loopNodeSecond->next;
                    delete loopNodeFirst;
                    size--;
                } else {
                    loopNodeFirst->next = loopNodeSecond->next;
                    delete loopNodeSecond;
                    loopNodeSecond = loopNodeFirst->next;
                    size--;
                }
            } else {
                loopNodeFirst = loopNodeSecond;
                loopNodeSecond = loopNodeSecond->next;
            }
        }
        return *this;
    }
}