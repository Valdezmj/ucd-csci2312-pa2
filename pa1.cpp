//
// Created by Ivo Georgiev on 8/25/15.
//

#include "Point.h"
#include <cmath>
#include <iostream>
#include <iomanip>
using namespace std;

double computeArea(Point p[], double &area);
int main(void) {

    Point p[3]; // Three new points intialized at (0.0, 0.0, 0.0)
    double coordinatePt = 0.0; // our coordinate pt to store a value used to set x,y, and z values
    double area = 0.0;
    cout << "Welcome please provide coordinates for 3 pts." << endl;
   
    // This loops through the array of points and asks the user to set the x,y, and z values for each point
    for (int i = 0; i < 3; i++) {
       cout << "Please input an x value for pt " << i + 1 << endl;
       cin >> coordinatePt;
       p[i].setX(coordinatePt);

       cout << "Please input a y value for pt " << i + 1 << endl;
       cin >> coordinatePt;
       p[i].setY(coordinatePt);

       cout << "Please input an z value for pt " << i + 1 << endl;
       cin >> coordinatePt;
       p[i].setZ(coordinatePt);
    }

    // Output the area between the 3 points to the user 
    computeArea(p, area);
    cout << setprecision(2) << "The area between you're three points that you have created is: " << area << endl;

    return 0;
}

/* computeArea function
 * brief
 *  \param: Three Point refrences
 *  \return: double area calculated between the three points
 */
double computeArea(Point p[], double &area) {
   // Length of all sides will be stored in los
   double los = 0.0;
   double sideA = p[0].distanceTo(p[1]);
   double sideB = p[1].distanceTo(p[2]);
   double sideC = p[2].distanceTo(p[0]);
   los = .5 * (sideA + sideB + sideC);

   if (p[0].getX() == p[1].getX()) {
      if (p[0].getY() == p[1].getY()) {
         if (p[0].getZ() == p[1].getZ()) {
           return area; 
         }  
      }
   } else if (p[0].getX() == p[2].getX()) {
      if (p[0].getY() == p[2].getY()) {
         if (p[0].getZ() == p[2].getZ()) {
           return area;
         }
      }
   } else if (p[1].getX() == p[2].getX()) {
      if (p[1].getY() == p[2].getY()) {
         if (p[1].getZ() == p[2].getZ()) {
           return area;
         }
      }
   } 
   area = sqrt(los * (los - sideA) * (los - sideB) * (los - sideC));
   return area;
}
