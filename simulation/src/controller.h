#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <iostream>
#include "intersection.h"
#include "street.h"

class Controller
{
public:
    int id;
    Intersection intersection;
    double speed_limit;
    double extreme_weather_speed_limit;
    bool is_failure_occured;
    double passing_time;
    double extreme_weather_passing_time;
    bool is_there_emergency_street;
    bool is_there_pedestrian_street;

    Controller(int id, Intersection intersection);

    void addCarToEachStreet(int intersectionId, int streetId, const Car &car);

    void addPedestrianToStreet(int intersectionId, int streetId, const Pedestrian &pedestrian);

    bool calculateTrafficCongestion(Intersection intersection);

    void setStreetPriority(Intersection intersection);

    void setPassPermission(Intersection intersection);
    
};

#endif // CONTROLLER_H
