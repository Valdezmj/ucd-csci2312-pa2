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
        head = new Node;
        NodePtr assigneeNode;
        NodePtr assignNode;
        NodePtr lastNode;
        head->pt = new Point(*clust.head->pt);
        size++;

        assigneeNode = clust.head->next;
        if (assigneeNode != nullptr) {
            for (int i = 1; i < size; i++) {
                if (i == size - 1) {
                    lastNode = assignNode;
                    assignNode = new Node;
                    lastNode->next = assignNode;
                    assignNode->pt = new Point(*assigneeNode->pt);
                    size++;
                    assignNode->next = nullptr;
                } else {
                    if (i > 1) {
                        lastNode = assignNode;
                    }
                    assignNode = new Node;
                    lastNode->next = assignNode;
                    assignNode->pt = new Point(*assigneeNode->pt);
                    size++;
                    assigneeNode = assigneeNode->next;
                }
            }
        } else {
            head->next = nullptr;
        }
    }

    void Clustering::Cluster::add(const Clustering::PointPtr &pt) {
        if (size != 0) {
            NodePtr placementFinder;
            NodePtr newNode = new Node;
            newNode->pt = pt;

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
            head->pt = pt;
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
                    delete head->pt;
                    delete head;
                    if (i == size - 1) {

                    } else {
                        head = nextNode;
                        nextNode = nextNode->next;
                    }
                }
            } else {
                if (head->pt != nullptr) {
                    delete head->pt;
                }
                delete head;
            }
        }
    }

    const PointPtr Clustering::Cluster::remove(const Clustering::PointPtr pt) {
        NodePtr searchNode = head;
        NodePtr tempNodePtr;
        PointPtr tempPointPtr = head->pt;
        if (head->pt == pt) {
            tempNodePtr = head;
            head = head->next;
            tempNodePtr->pt = nullptr;
            delete tempNodePtr;
            size--;
            return tempPointPtr;
        }
        while (*searchNode->pt != *pt && searchNode->next != nullptr) {
            if (*searchNode->next->pt == *pt) {
                tempPointPtr = searchNode->next->pt;
                searchNode->next->pt = nullptr;
                tempNodePtr = searchNode->next;
                searchNode->next = searchNode->next->next;
                delete tempNodePtr;
                size--;
                return tempPointPtr;
            } else {
                searchNode = searchNode->next;
            }
        }
        return tempPointPtr;
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
                delete lastNode->pt;
                delete lastNode;
                secondToLastNode->next = nullptr;
            }
            delete head->pt;
            delete head;
        }
        NodePtr assignNode;
        NodePtr assigneeNode;
        size = clust.size;
        head = new Node;
        if (clust.head != nullptr) {
            head->pt = new Point(*clust.head->pt);
        } else {
            head = clust.head;
            return *this;
        }
        lastNode = head;

        assigneeNode = clust.head->next;
        for (int i = 1; i < size; i++) {
            if (i == size - 1) {
                lastNode = assignNode;
                assignNode = new Node;
                lastNode->next = assignNode;
                assignNode->pt = new Point(*assigneeNode->pt);
                assignNode->next = nullptr;
            } else {
                if (i > 1) {
                    lastNode = assignNode;
                }
                assignNode = new Node;
                lastNode->next = assignNode;
                assignNode->pt = new Point(*assigneeNode->pt);
                assigneeNode = assigneeNode->next;
            }
        }
        return *this;
    }

    Cluster &Cluster::operator+(const Cluster &rightSide) {
        if (*this == rightSide) {
            return *this;
        }

        Cluster * newCluster = new Cluster();
        NodePtr nodeCheckSetOne = head;
        NodePtr nodeCheckSetTwo = rightSide.head;
        NodePtr checkNewListNode;

        for (int i = 0; i < size; i++) {
            newCluster->add(nodeCheckSetOne->pt);

            if (nodeCheckSetOne->next != nullptr) {
                nodeCheckSetOne = nodeCheckSetOne->next;
            }
        }

        checkNewListNode = newCluster->head;

        for (int i = 0; i < rightSide.size; i++) {

            for (int j = 0; j < newCluster->size; j++) {

                if (*nodeCheckSetTwo->pt != *checkNewListNode->pt) {
                    newCluster->add(nodeCheckSetTwo->pt);
                    break;
                } else {
                }
                checkNewListNode = checkNewListNode->next;
            }

            if (nodeCheckSetTwo->next != nullptr) {
                nodeCheckSetTwo = nodeCheckSetTwo->next;
                checkNewListNode = newCluster->head;
            }
        }

        return *newCluster;
    }
    Cluster &Cluster::operator-(const Cluster &rightSide) {

        Cluster * newCluster = new Cluster();
        if (*this == rightSide) {
            return *newCluster;
        }
        NodePtr nodeCheckSetOne = head;
        NodePtr nodeCheckSetTwo = rightSide.head;
        NodePtr checkNewListNode;

        for (int i = 0; i < size; i++) {
            newCluster->add(nodeCheckSetOne->pt);

            if (nodeCheckSetOne->next != nullptr) {
                nodeCheckSetOne = nodeCheckSetOne->next;
            }
        }

        checkNewListNode = newCluster->head;

        for (int i = 0; i < rightSide.size; i++) {

            for (int j = 0; j < newCluster->size; j++) {

                if (*nodeCheckSetTwo->pt == *checkNewListNode->pt) {
                    newCluster->remove(nodeCheckSetTwo->pt);
                    break;
                } else {
                }
                checkNewListNode = checkNewListNode->next;
            }

            if (nodeCheckSetTwo->next != nullptr) {
                nodeCheckSetTwo = nodeCheckSetTwo->next;
                checkNewListNode = newCluster->head;
            }
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
        return *this;
    }
    Cluster &Cluster::operator-=(const Cluster &rightSide) {
        if (this == &rightSide) {
            return *this;
        }
        *this = (*this - rightSide);
        return *this;
    }

    Cluster &Cluster::operator+(Point &point) {
        if (size != 0) {
            NodePtr placementFinder;
            NodePtr newNode = new Node;
            newNode->pt = &point;

            if (*newNode->pt >= *head->pt) {
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
                if (*newNode->pt < *placementFinder->pt) {
                    if (*newNode->pt >= *(placementFinder->next)->pt) {
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
                } else if (*newNode->pt >= *placementFinder->pt) {
                    newNode->next = placementFinder;
                    head->next = newNode;
                    break;
                }
            }
            size++;
        } else {
            head = new Node;
            head->next = nullptr;
            head->pt = &point;
            size++;
        }
        return *this;

    }

    Cluster &Cluster::operator-(Point &point) {
        NodePtr searchNode = head;
        NodePtr tempNode;
        if (point == *searchNode->pt) {
            delete searchNode->pt;
            searchNode->pt = nullptr;
            head = head->next;
            delete searchNode;
            return *this;
        }
        while (*searchNode->pt != point && searchNode->next != nullptr) {
            if (*searchNode->next->pt == point) {
                delete searchNode->next->pt;
                searchNode->next->pt = nullptr;
                tempNode = searchNode->next;
                searchNode->next = searchNode->next->next;
                delete tempNode;
                size--;
                return *this;
            } else {
                searchNode = searchNode->next;
            }
        }
        return *this;
    }
}
