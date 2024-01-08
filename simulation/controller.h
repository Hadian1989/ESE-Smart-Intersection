#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <iostream>
#include "intersection.h"
#include "car.h"
#include "street.h"
#include "pedestrian.h"

class Controller {
public:
    Controller(int id);
    Intersection intersection;
    void addCarToEachStreet(int intersectionId, int streetID, const std::vector<Car> &cars);
    void addPedestrianToStreet(int intersectionId, int streetID, const std::vector<Pedestrian> &pedestrians);
    void displayInfo();
    bool calculateTrafficMode();
    void calculatePriority();
    void setPermission();
    void simulation();
private:
    
    
};

#endif // CENTRALIZED_CONTROLLER_H
