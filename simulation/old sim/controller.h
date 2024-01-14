#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <iostream>
#include "intersection.h"
#include "car.h"
#include "street.h"
#include "pedestrian.h"

class Controller {
public:
    Controller(int id, Intersection intersection);
    Intersection intersection;
    void addCarToEachStreet(int intersectionId, int streetID, const std::vector<Car> &cars);
    void addPedestrianToStreet(int intersectionId, int streetID, const std::vector<Pedestrian> &pedestrians);
    void displayInfo();
    bool calculateTrafficCongestion(Intersection intersection);
    void checkVehiclesCollision();
    void setStreetPriority(Intersection intersection);
    void setCarPermission(Intersection intersection);
    void movingSimulation(Intersection intersection);
    void upadteTrafficFlow(Intersection intersection);
private:
    
    
};

#endif // CENTRALIZED_CONTROLLER_H
