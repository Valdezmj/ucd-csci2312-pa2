#include "Point.h"
#include <cmath>
#include <string>
#include <iostream>
#include <sstream>
#include <MacTypes.h>

// Default constructor
// Initializes dim to 0
namespace Clustering {
    const char Point::POINT_VALUE_DELIM = ',';
    Clustering::Point::Point() {
        dim = 0;
        dimensions = nullptr;
    }

// Construct a point with a number of dimensions
    Clustering::Point::Point(unsigned int dimension) {
        dim = dimension;
        dimensions = new double[dim];
        for (int i = 0; i < dim; i++) {
            dimensions[i] = 0;
        }
    }

    Clustering::Point::Point(unsigned int numDimensions, double array[]) {
        dim = numDimensions;
        dimensions = new double[numDimensions];

        for (int i = 0; i < numDimensions; i++) {
            dimensions[i] = array[i];
        }
    }

    Clustering::Point::Point(const Clustering::Point &pt) {
        dim = pt.getDims();
        dimensions = new double[dim];

        for (int i = 0; i < dim; i++) {
            dimensions[i] = pt.dimensions[i];
        }
    }

// Destructor
// No dynamic allocation, so nothing to do; if omitted, generated automatically
    Clustering::Point::~Point() {
            delete[] dimensions;
            dimensions = nullptr;
    }

// Mutator methods
// Change the values of private member variables

    void Clustering::Point::setDimensionValue(int dimension, double newValue) {
        if (dimension <= dim) {
            dimensions[dimension - 1] = newValue;
        }
    }
// Accessor
// Returns the value of of the given dimension

    double Clustering::Point::getDimensionValue(int dimension) const {
        if (dimension > dim) {
            return 0;
        }
        dimension--;

        return dimensions[dimension];
    }


// Gets a distance to another point
// Returns the distance as a double

    double Clustering::Point::distanceTo(const Clustering::Point &pt) {
        if (pt.getDims() > dim) {
            return 0;
        }
        double distance = 0.0;

        for (int i = 0; i < dim; i++) {
            distance += pow((pt.getDimensionValue(i + 1) - dimensions[i]), 2);
        }
        distance = sqrt(distance);

        return distance;
    }

    std::ostream &operator<<(std::ostream &os, const Clustering::Point &pt) {
        for (int i = 0; i < pt.getDims(); i++) {
            os << pt.dimensions[i];
            if (i != pt.getDims() - 1) {
                os << ", ";
            }
        }
        return os;
    }

    std::stringstream &operator>>(std::stringstream &is, Point &pt) {
        double d;
        std::string value;
        std::stringstream formatNum;
        formatNum.setf(std::ios::fixed);

        int i = 0;
        while (getline(is, value, pt.POINT_VALUE_DELIM)) {
            d = std::stod(value);
            formatNum.precision(1);
            formatNum << d;
            formatNum >> d;
            pt.dimensions[i++] = d;
        }
        return is;
    }

    bool operator==(const Clustering::Point &ptLeftSide, const Clustering::Point &ptRightSide) {
        if (ptLeftSide.getDims() != ptRightSide.getDims()) {
            return false;
        }
        bool check = true;
        for (int i = 1; i <= ptLeftSide.getDims(); i++) {
            if (ptLeftSide.getDimensionValue(i) != ptRightSide.getDimensionValue(i)) {
                check = false;
                break;
            }
        }
        return check;
    }

    bool operator!=(const Clustering::Point &ptLeftSide, const Clustering::Point &ptRightSide) {
        if (ptLeftSide.getDims() != ptRightSide.getDims()) {
            return true;
        }
        bool check = false;
        for (int i = 1; i <= ptLeftSide.getDims(); i++) {
            if (ptLeftSide.getDimensionValue(i + 1) != ptRightSide.getDimensionValue(i + 1)) {
                check = true;
                break;
            }
        }
        return check;
    }

    bool operator<(const Clustering::Point &ptLeftSide, const Clustering::Point &ptRightSide) {
        if (ptLeftSide.getDims() < ptRightSide.getDims()) {
            return true;
        } else if (ptLeftSide.getDims() > ptRightSide.getDims()) {
            return false;
        }
        bool check = false;

        for (int i = 0; i < ptLeftSide.getDims(); i++) {
            if (ptLeftSide.getDimensionValue(i + 1) < ptRightSide.getDimensionValue(i + 1)) {
                check = true;
            }
        }
        return check;
    }

    bool operator<=(const Clustering::Point &ptLeftSide, const Clustering::Point &ptRightSide) {
        if (ptLeftSide.getDims() < ptRightSide.getDims()) {
            return true;
        } else if (ptLeftSide.getDims() > ptRightSide.getDims()) {
            return false;
        }
        for (int i = 0; i < ptLeftSide.getDims(); i++) {
            if (ptLeftSide.getDimensionValue(i + 1) < ptRightSide.getDimensionValue(i + 1)) {
                return true;
            } else if (ptLeftSide.getDimensionValue(i + 1) == ptRightSide.getDimensionValue(i + 1)) {
            } else {
                return false;
            }
        }
        return true;
    }

    bool operator>(const Clustering::Point &ptLeftSide, const Clustering::Point &ptRightSide) {
        if (ptLeftSide.getDims() < ptRightSide.getDims()) {
            return false;
        } else if (ptLeftSide.getDims() > ptRightSide.getDims()) {
            return true;
        }
        for (int i = 0; i < ptLeftSide.getDims(); i++) {
            if (ptLeftSide.getDimensionValue(i + 1) > ptRightSide.getDimensionValue(i + 1)) {
                return true;
            } else if (ptLeftSide.getDimensionValue(i + 1) == ptRightSide.getDimensionValue(i + 1)) {
                return false;
            } else {
                return false;
            }
        }
        return true;
    }

    bool operator>=(const Clustering::Point &ptLeftSide, const Clustering::Point &ptRightSide) {
        if (ptLeftSide.getDims() < ptRightSide.getDims()) {
            return false;
        } else if (ptLeftSide.getDims() > ptRightSide.getDims()) {
            return true;
        }
        for (int i = 0; i < ptLeftSide.getDims(); i++) {
            if (ptLeftSide.getDimensionValue(i + 1) > ptRightSide.getDimensionValue(i + 1)) {
                return true;
            } else if (ptLeftSide.getDimensionValue(i + 1) == ptRightSide.getDimensionValue(i + 1)) {
            } else {
                return false;
            }
        }
        return true;
    }

    Clustering::Point &Clustering::Point::operator=(const Point &ptRightSide) {
        if (this == &ptRightSide) {
            return *this;
        } else {
            delete[] dimensions;
            dim = ptRightSide.getDims();
            dimensions = new double[dim];
            for (int i = 0; i < dim; i++) {
                dimensions[i] = ptRightSide.getDimensionValue(i + 1);
            }
        }
        return *this;
    }

    Clustering::Point &Clustering::Point::operator+(const Clustering::Point &ptRightSide) {
        if (dim != ptRightSide.getDims()) {
            std::cout << "You tried to add two points that weren't within " <<
            "the same dimensions... returning the first point " <<
            "as the answer\n";
            return *this;
        }

        Point *addedPoint = new Point(*this);

        for (int i = 0; i < dim; i++) {
            addedPoint->dimensions[i] = addedPoint->dimensions[i] + ptRightSide.getDimensionValue(i + 1);
        }
        return *addedPoint;
    }

    Clustering::Point &Clustering::Point::operator-(const Clustering::Point &ptRightSide) {
        if (dim != ptRightSide.getDims()) {
            std::cout << "You tried to subtract two points that weren't within " <<
            "the same dimensions... returning the first point " <<
            "as the answer\n";
            return *this;
        }

        Point *addedPoint = new Point(*this);

        for (int i = 0; i < dim; i++) {
            addedPoint->dimensions[i] = addedPoint->dimensions[i] - ptRightSide.getDimensionValue(i + 1);
        }
        return *addedPoint;
    }

    Clustering::Point &Clustering::Point::operator*(const double numberToMultiplyBy) {
        if (dim == 0) {
            std::cout << "You tried to multiply by a point that isn't " <<
            "established returning the point " <<
            "as the answer\n";
            return *this;
        }

        Point *addedPoint = new Point(*this);

        for (int i = 0; i < dim; i++) {
            addedPoint->dimensions[i] = addedPoint->dimensions[i] * numberToMultiplyBy;
        }
        return *addedPoint;
    }

    Clustering::Point &Clustering::Point::operator/(const double numberToDivideBy) {
        if (dim == 0 && numberToDivideBy == 0) {
            std::cout << "You either tried to divide by a point that isn't " <<
            "established or divide by 0... returning the point " <<
            "as the answer\n";
            return *this;
        }

        Point *addedPoint = new Point(*this);

        for (int i = 0; i < dim; i++) {
            addedPoint->dimensions[i] = addedPoint->dimensions[i] / numberToDivideBy;
        }
        return *addedPoint;
    }

    Clustering::Point &Clustering::Point::operator+=(const Clustering::Point &ptRightSide) {
        if (dim != ptRightSide.getDims()) {
            std::cout << "You tried to add two points that weren't within " <<
            "the same dimensions... returning the first point " <<
            "as the answer\n";
            return *this;
        }

        for (int i = 0; i < dim; i++) {
            this->dimensions[i] = this->dimensions[i] + ptRightSide.dimensions[i];
        }
        return *this;
    }

    Clustering::Point &Clustering::Point::operator-=(const Clustering::Point &ptRightSide) {
        if (dim != ptRightSide.getDims()) {
            std::cout << "You tried to subtract two points that weren't within " <<
            "the same dimensions... returning the first point " <<
            "as the answer\n";
            return *this;
        }

        for (int i = 0; i < dim; i++) {
            this->dimensions[i] = this->dimensions[i] - ptRightSide.getDimensionValue(i + 1);
        }
        return *this;
    }

    Clustering::Point &Clustering::Point::operator*=(const double numberToMultiplyBy) {
        if (dim == 0) {
            std::cout << "You tried to multiply by a point that isn't " <<
            "established returning the point " <<
            "as the answer\n";
            return *this;
        }

        Point *addedPoint = new Point(*this);

        for (int i = 0; i < dim; i++) {
            addedPoint->dimensions[i] = addedPoint->dimensions[i] * numberToMultiplyBy;
        }
        return *addedPoint;
    }

    Clustering::Point &Clustering::Point::operator/=(const double numberToDivideBy) {
        if (dim == 0 && numberToDivideBy == 0) {
            std::cout << "You either tried to divide by a point that isn't " <<
            "established or divide by 0... returning the point " <<
            "as the answer\n";
            return *this;
        }

        for (int i = 0; i < dim; i++) {
            this->dimensions[i] = this->dimensions[i] / numberToDivideBy;
        }
        return *this;
    }

    unsigned int Clustering::Point::getDims() const {
        return dim;
    }
}