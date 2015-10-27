## CSCI 2312: Programming Assignment 3
_working with KMeans and clustering points_
***

Going from PA2 to PA3 there has been some major changes in how to use the _Cluster_ class as well as the newly created class, _KMeans_.

As always, starting with the Point class, lets take a look at how one can instantiate a Point object. 

### Point Class
***
#### Creating a Point Object
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
Points being added follow the operation: (w, x, y) + (q, r, s) = (w + q, x + r, y + s)
_Point objects can also perform +=_

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
Points being subtracted follow the operation: (w, x, y) + (q, r, s) = (w - q, x - r, y - s)
_Point objects can also perform -=_

#### Multiplying and dividing by a constant
```c++
int main() {
   double ptArray1[3] = {1, 2, 3};
   Point pt1(3, ptArray1);

   double ptArray2[3] = {3, 4, 5};
   Point pt2(3, ptArray2);
  
   Point pt3(3);

   pt3 = (3 * pt1) + (2 * pt2);

   // pt3 now equals (9, 14, 19)

   pt3 /= 2;    // This is equivalent to pt3 = pt3 / 2;

   // pt3 now equals (4.5, 7, 9.5)
   return 0;
}
```
Points can be,
multiplied: a * (x, y, z) = (a * x, a * y, a * z)

divided: (x, y, z) / a = (x / a, y / a, z / a) 

operations also allowed with constants are *=, /=

#### Comparison operators
```c++
int main() {
   double ptArray1[3] = {1, 2, 3};
   Point pt1(3, ptArray1);

   double ptArray2[3] = {3, 4, 5};
   Point pt2(3, ptArray2);
  
   Point pt3(3);

   pt3 = (3 * pt1) + (2 * pt2);

   // pt3 now equals (9, 14, 19)
   
   // True
   pt3 > pt1;
   
   // False
   pt1 >= pt2;
   
   // False
   pt3 <= pt2;
   
   // True
   pt3 >= (pt1 + pt2)
   return 0;
}
```
The standard comparisons between points can be applied.  Comparing each dimension of each point with another point.

_Note: if dimensions aren't the same, false will always be returned_

#### stream operators
```c++
int main() {
   double ptArray1[3] = {1, 2, 3};
   Point pt1(3, ptArray1);

   double ptArray2[3] = {3, 4, 5};
   Point pt2(3, ptArray2);

   Point pt3(3);

   pt3 = (3 * pt1) + (2 * pt2);

   // pt3 now equals (9, 14, 19)
   
   cout << pt3;
   // prints 9, 14, 19
   stringstream someStream;
   
   someStream >> pt1;
   
   return 0;
}
```
One thing to note here is that when using >> to a point, you are using a string stream. Make sure the point in the stream and the object its self
have the same dimensions or you will get an error.

### Cluster Class
***
This class acts as a container that can hold a list of Point objects in lexicographical order.  Each cluster created will have a unique
id.  See example below...

_Note: Exposes a typedef PointPtr when included, which is a shared pointer of a Point object._
#### Creating a Cluster Object
```c++
int main() {
   //Creating a Cluster with dimensions
   Cluster cl1(3); // id: 1
   // cl1 will now hold points with three dimensions
   
   Cluster cl2(4); // id: 2
   // cl2 will now hold points with four dimensions 
   return 0;
}
```
It is important to understand the relationship between the points and its cluster.  They should be related enough where it is safe to assume
all points inside each cluster should be of the same dimensions.  If for some reason a cluster will be changed to hold points with different
dimensions than originally created for see properties section to update the cluster.

#### Cluster Centroids
Each cluster will have a centroid associated with it and can be accessed by _getCentroid_.  See properties section to understand more.

Any operation on a cluster that changes the size will cause the centroid to become _invalid_.

Clusters with invalid centroids can become valid again by calling _computeCentroid_ or _setCentroid_.  See properties for more information
on _setCentroid_.

As for _computeCentroid_, this will calculate the centroid based upon the points contained in the cluster and set centroid valid to _true_.
#### Properties of Cluster
There are many properties that can be accessed to get the state of the Cluster.

##### size of cluster
_getSize_
returns the size of the cluster.

##### adding/removing points to a cluster
_add_ takes a PointPtr.
_remove_ takes a PointPtr and returns a PointPtr.

see section below that explains more on adding and removing points to a cluster.

##### Centroids
_checkCentroid_
returns the value of the validity of the centroid. Can be true or false.

_computeCentroid_: See centroids section to understand more.

_getCentroid_
returns a point.  Ex. 3, 2, 1
type: double

_setCentroid_
Sets a centroid to the following Point object passed in.
Setting the validity of the centroid to true.
```c++
int main() {
   double arr[3] = {6, 8, 9};
   Point pt1(3, arr);
   Cluster cl1(3);

   cl1.setCentroid(pt1);
   
   cout << cl1.getCentroid(); // prints 6, 8, 9
   return 0;
}
```

##### point dimensions of cluster
_getPointDimension_
returns an unsigned int.

_setPointDimension_
accepts an unsigned int.
***
#### Cluster Set Arithmetic
_arithmetic between two clusters_
If we were to have two clusters defined as followed:
Cluster1 = (p1, p2, p3)  && Cluster2 = (p3, p4, p5)

This class was written to preform as follows:

Cluster1 + Cluster2 = (p1, p2, p3, p4, p5)

Otherwise known as the union between two sets.  Likewise, vice versa 
```c++
Cluster1 - Cluster2 
```
would yield _(p1, p2)_.  Or in other words all the points in Cluster1 that are not in Cluster2.


#### Cluster and Point arithmetic
_arithmetic between a cluster and a point_
The cluster class overloaded multiple functions to allow such arithmetic
```c++
// randomPoint is a PointPtr
clusterTwo = clusterOne + randomPoint;
```
From the code above we can see that we are returning a Cluster object back to the equation which will contain the result of adding <tt>PointPtr randomPoint</tt> to <tt>clusterOne</tt> but not actually adding the point to clusterOne.  Then assigning this newly formed cluster to <tt>clusterTwo</tt>.

#### Adding and removing points
##### Adding
Using the _add_ function of the cluster will add a PointPtr object to a cluster
```c++
// randPt is a PointPtr object
clustOne.add(randPt);
```
You can also use the += operator to add a Point object to a cluster.
```c++
// randPt is a Point Object
clustOne += randPt;
```
##### Removing
_remove_ function will remove a point from the cluster by the <tt>PointPtr</tt> passed in.
```c++
// randPt is a PointPtr object
clustTwo.remove(randPt);

// Acceptable
clustOne.add(clustTwo.remove(randPt));
```
Although it is mentioned in the code above that you can add a <tt>PointPtr</tt> by removing it from another cluster, there is a better way to do this.  See Move class associated within Cluster.

you can also remove all points from a cluster that are equal to a _Point_ object.
```c++
// randPt is a Point Object
clustOne -= randPt;

// If clustOne contains many points that are equal in value to randPt, they will all be removed.
```

#### Move class (associated  with Cluster)
_only available when working with clusters_

The Move class allows the ease of moving one PointPtr object from one cluster to another.
```c++
...
// moving randPt from clustOne to clustTwo
Cluster::Move pointMove(randPt, &clustOne, &clustTwo);
pointMove.perform();
```
Using the example above, the first parameter will be the PointPtr you want to move, the second parameter is the address or <tt>* Cluster</tt> of a Cluster where the PointPtr
is currently located and the third parameter takes the address of a Cluster where the PointPtr will be moved to.

Notice you have to call the _perform()_ function in order for the move to take place!

#### 
###Compiler
Apple LLVM version 6.1.0 (clang-602.0.53)


