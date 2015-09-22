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

