#include "car.h"
#include "pedestrian.h"
#include "street.h"
#include <iostream>

// Parameterized constructor
Street::Street(int id, Direction direction, std::vector<Car> cars, std::vector<Pedestrian> pedestrians): 
      id(id),
      direction(direction),
      cars(cars),
      pedestrians(pedestrians) {}

// Method to add a car to the street
void Street::addCar(const Car &car) {
    cars.push_back(car);
}

// Method to add a pedestrian to the street
void Street::addPedestrian(const Pedestrian &pedestrian) {
    pedestrians.push_back(pedestrian);
}

// Method to display traffic information
void Street::displayTraffic() const {
    std::cout << "Street ID: " << id << std::endl;
    std::cout << "Direction: ";

    switch (direction) {
        case SOUTH:
            std::cout << "South";
            break;
        case WEST:
            std::cout << "West";
            break;
        case NORTH:
            std::cout << "North";
            break;
        case EAST:
            std::cout << "East";
            break;
    }

    std::cout << std::endl;


    std::cout << "Cars on the street:" << std::endl;
    for (const auto &car : cars) {
        car.displayInfo();
    }

    std::cout << "Pedestrians on the street:" << std::endl;
    for (const auto &pedestrian : pedestrians) {
        pedestrian.displayInfo();
    }
}

// Method to calculate traffic conditions
bool Street::calculateTraffic() {
    return cars.size() >= 15;
    }
