// A multi-dimensional point class!
// Coordinates are double-precision floating point.

#ifndef __point_h
#define __point_h
#include <iostream>

namespace Clustering {
    class Point {

    private:
        double *dimensions;
        unsigned int dim;

    public:
        static const char POINT_VALUE_DELIM;

        // Constructors
        Point();                                // default constructor
        Point(unsigned int dimensions);                  // dimensions constructor
        Point(unsigned int dimension, double array[]);  // dimensions and array constructor
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
        unsigned int getDims() const;

        // function to get a distance to another point
        double distanceTo(const Point &pt);

        // Over loaded operators
        friend std::ostream &operator<<(std::ostream &os, const Point& pt);
        friend std::stringstream &operator>>(std::stringstream &is, Point& pt);


        friend bool operator==(const Point &ptLeftSide, const Point &ptRightSide);

        friend bool operator!=(const Point &ptLeftSide, const Point &ptRightSide);

        friend bool operator<(const Point &ptLeftSide, const Point &ptRightSide);

        friend bool operator<=(const Point &ptLeftSide, const Point &ptRightSide);

        friend bool operator>(const Point &ptLeftSide, const Point &ptRightSide);

        friend bool operator>=(const Point &ptLeftSide, const Point &ptRightSide);

        //friend Point &operator[](Point &ptLeftSide,Point &ptRightSide);

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
}
#endif // __point_h
