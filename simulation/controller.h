#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <iostream>
#include <cstdlib> // for rand()
#include "intersection.h"
#include "car.h"
#include "pedestrian.h"

class Controller {
public:
    Controller();

private:
    Intersection intersection;
    void addRandomCars();
    void addRandomPedestrians();
    void addRandomEmergencyCar();
};

#endif // CENTRALIZED_CONTROLLER_H
