#ifndef INTERSECTION_H
#define INTERSECTION_H

#include <iostream>
#include <string>
#include "street.h"

class Intersection {
public:
    public:
    Intersection() : id(0) {}  // Default constructor
    Intersection(int id, std::vector<Street>& street);
    void addStreet(const Street& street, int direction);
    void displayIntersection() const;

private:
    int id;
    Street streets[4];  // Assuming four streets (north, south, east, west)
};

#endif // INTERSECTION_H
