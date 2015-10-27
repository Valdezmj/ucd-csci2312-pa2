## CSCI 2312: Programming Assignment 3
_working with KMeans and clustering points_
***

Going from PA2 to PA3 there has been some major changes in how to use the _Cluster_ class as well as the newly created class, _KMeans_.

As always, starting with the Point class, lets take a look at how one can instantiate a Point object. 

###Creating a Point Object
```c++
int main() {
   //Creating a point with dimensions
   Point pt1(3);
   // pt1 will now be equal to (0, 0, 0)
   
   // Creating a point with dimensions and values
   double ptArray[3] = {1, 2, 3};
   Point pt2(3, ptArray);
   // pt2 will now be equal to (1, 2, 3);
   
   return 0;
}
```
As you can see starting with the first example, you can instantiate the Point class by simply passing a positive int value in as a parameter creating a point with X dimensions.  In this case, 3 was passed in and the point was initiated at the origin with three dimensions.

In the second example, the Point object was created by passing in the dimensions of the point as well as including an array of type, _double_, to set the values of each dimensions.  We can see that the second Point, _pt2_, was created to hold three dimensions with the values (1, 2, 3).

It makes no sense to create a dynamic Point with no starting dimensions or initial values such as:
```c++
int main() {
   // BAD
   Point badPoint;

   // GOOD
   // Point goodPoint(some dimensions, optional values in an array with type double)
   return 0;
}
```

### Operations with the Point object(s)

This Point class can also perform operations with other points as well as do simple arithmetic on its self.

#### Adding points together
```c++
int main() {
   double ptArray1[3] = {1, 2, 3};
   Point pt1(3, ptArray1);

   double ptArray2[3] = {3, 4, 5};
   Point pt2(3, ptArray2);

   Point pt3(3);

   pt3 = pt1 + pt2;

   // pt3 now equals (4, 6, 8)
   return 0;
}
```
#### Subtracting points
```c++
int main() {
   double ptArray1[3] = {1, 2, 3};
   Point pt1(3, ptArray1);

   double ptArray2[3] = {3, 4, 5};
   Point pt2(3, ptArray2);
   
   Point pt3(3);

   pt3 = pt2 - pt1;

   // pt3 now equals (2, 2, 2)
   return 0;
}
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
A key thing to notice in the code above and in the return value of the overloaded example given is that once the arithmetic is preformed between the two points, a point is returned back to the equation which then we see p1 is using the assignment operator ```=``` to assign the newly returned _Point_.

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
        ~Cluster();
        
	Cluster &operator+(const Cluster & rightSide);
        Cluster &operator-(const Cluster & rightSide);
        bool operator==(const Cluster & rightSide);
        Cluster &operator+=(const Cluster & rightSide);
        Cluster &operator-=(const Cluster & rightSide);
        Cluster &operator+(Point & point);
        Cluster &operator-(Point & point);





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
where ```head``` acts as the first node in the list.  In each node we see that we have a _Point_ pointer ```PointPtr pt``` which will store a memory address of a _Point_ object.

####Cluster Set Arithmetic
_arithmetic between two clusters_
***
If we were to have two clusters defined as followed:
Cluster1 = (p1, p2, p3)  && Cluster2 = (p3, p4, p5)

This class was written to preform as follows:

Cluster1 + Cluster2 = (p1, p2, p3, p4, p5)

Otherwise known as the union between two sets.  Likewise, vice versa Cluster1 - Cluster2 would yield _(p1, p2)_.  Or in other words all the points in Cluster1 that are not in Cluster2.

####Cluster and Point arithmetic
_arithmetic between a cluster and a point_
***
The cluster class overloaded multiple functions to allow such arithmetic
```c++
clusterTwo = clusterOne + randomPoint;
```
From the code above we can see that we are returning a Cluster object back to the equation which will contain the result of adding <tt>randomPoint</tt> to <tt>clusterOne</tt> but not actually adding the point to clusterOne.  Then assigning this newly formed cluster to <tt>clusterTwo</tt>.

###Compiler
Apple LLVM version 6.1.0 (clang-602.0.53)


