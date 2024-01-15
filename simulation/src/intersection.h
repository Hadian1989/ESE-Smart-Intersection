#ifndef INTERSECTION_H
#define INTERSECTION_H

#include <vector>
#include <iostream>
#include "street.h"

class Intersection
{
public:
    int id;
    std::vector<Street> streets;
    State state = NORMAL;
    bool isExtremeWeather;
    bool isDay;

    Intersection(int id, bool isExtremeWeather);

    void addStreet(const Street &street);

    void addCarsToStreet(int streetId, const Car &car);

    void addPedestrianToStreet(int streetId, const Pedestrian &pedestrian);

    bool isThereEmergencyStreet();

    bool isThereHighCongestionStreet(std::vector<Street> streets) const;

    bool isTherePedestrianStreet(std::vector<Street> streets) const;

    const std::vector<Street> getStreets() const;

    void sortAllIntersectionCarsByDistance(std::vector<Street> streets);
};

#endif // INTERSECTION_H
