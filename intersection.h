#ifndef INTERSECTION_H
#define INTERSECTION_H

#include <iostream>
#include <string>
#include "street.h"

class Intersection {
public:
    Intersection(int id);
    void addStreet(const Street& street, int direction);
    void displayIntersection() const;

private:
    int id;
    Street streets[4];  // Assuming four streets (north, south, east, west)
};

#endif // INTERSECTION_H
