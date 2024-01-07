#ifndef INTERSECTION_H
#define INTERSECTION_H

#include <iostream>
#include <string>
#include "street.h"

class Intersection
{
public:
    Intersection(): id(0){}; 
    Intersection(int id, std::vector<Street> streets);
    void addStreet(const Street &street);
    void addCarsToStreet(int streetID, const std::vector<Car> &cars);
    void addPedestriansToStreet(int streetID, const std::vector<Pedestrian> &pedestrians);
    void displayIntersection() const;

private:
    int id;
    std::vector<Street> streets; // Assuming four streets (north, south, east, west)
};

#endif // INTERSECTION_H
