## CSCI 2312: Programming Assignment 2

_working with dynamic memory, linked lists, and overloaded operators_

***

The main goal of this programming assignment was too expand our knowledge on how to maintain dynamic memory, operate with a linked list and overload operators.

Starting with the updated _Point_ class, here is the <tt>Point.h</tt> that describes an object in any dimensional Euclidean space:

```c++
class Point {

    private:
        double *dimensions;
        int dim;

    public:
        // Constructors
        Point();                                // default constructor
        Point(int dimensions);                  // dimensions constructor
        Point(int dimension, double array[]);  // dimensions and array constructor
        Point(const Point &pt);

        // Mutator method
        // used for setting values at a specific dimension
        // for example if you wanted to set the 3rd dimension of (6, 4, 9) of
        // point p to 6.8 you would write  p.setDimensionValue(3, 6.8);
        void setDimensionValue(int dimension, double value);

        // Destructor
        ~Point();

        // Accessor method
        double getDimensionValue(int dimension) const;
        int getDims() const;
        double * getDimensionsAddress() {return dimensions;};

        // function to get a distance to another point
        double distanceTo(Point &pt);

        // Over loaded operators
        friend std::ostream & operator<<(std::ostream &os, const Point& pt);

        friend bool operator==(const Point &ptLeftSide, const Point &ptRightSide);

        friend bool operator!=(const Point &ptLeftSide, const Point &ptRightSide);

        friend bool operator<(const Point &ptLeftSide, const Point &ptRightSide);

        friend bool operator<=(const Point &ptLeftSide, const Point &ptRightSide);

        friend bool operator>(const Point &ptLeftSide, const Point &ptRightSide);

        friend bool operator>=(const Point &ptLeftSide, const Point &ptRightSide);

        Point &operator=(const Point &ptRightSide);

        Point &operator+(const Point &ptRightSide);

        Point &operator-(const Point &ptRightSide);

        Point &operator*(const double numberToMultiplyBy);

        Point &operator/(const double numberToDivideBy);

        Point &operator+=(const Point &ptRightSide);

        Point &operator-=(const Point &ptRightSide);

        Point &operator*=(const double numberToMultiplyBy);

        Point &operator/=(const double numberToDivideBy);

    };
```
One of the main changes between the first assignment and this assignment was changing the _Point_ class to allow an object to be a point in space of any dimension.  Such (1, 2, 3, 4). 
This required changing the constructors a bit:
```c++
	Point();                                // default constructor
        Point(int dimensions);                  // Constructor with given dimensions size
        Point(int dimension, double array[]);  // Constructor with given dimension size and array of values
        Point(const Point &pt);		       // Copy constructor
```
Along with that, instead of storing a constant value for each dimension- we dynamically allocate the dimensions in c++ by writing:
```c++
double *dimensions;
```
This allows us to change these values to support any different dimension we want.

Almost all the common operators were overloaded to support arithmetic between two points.  Such as:
_(1, 2, 3) + (3, 2, 1) = (4, 4, 4)_

This exact example would take the declaration of an overloaded function wrriten:
```c++
Point &operator+(const Point &ptRightSide);
```
More importantly, the example of:
```c++
p1 = p2 + p3;
```
A key thing to notice in the code above and in the return value of the overloaded example given is that once the arithmetic is preformed between the two points, a point is returned back to the equation which then we see p1 is using the assignment operator ```c++ =``` to assign the newly returned _Point_.

###Cluster Class
***
This class acts as a container of _Points_ resembled in a link list.  The header file of this class is:
```c++
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
```
The main goal of this class was to implement a linked list which was:
```c++
struct Node {
            PointPtr pt;
            NodePtr next;
        };
        NodePtr head;
```
where ```c++ head ``` acts as the first node in the list.  In each node we see that we have a _Point_ pointer ```c++ PointPtr pt```
