#include "car.h"
#include "pedestrian.h"
#include "street.h"


Street::Street(int id, Direction direction, 
               int numberOfCars, int numberOfEmgCars, 
               int numberOfPedestrians)
    : id(id), direction(direction), 
      numberOfCars(numberOfCars), numberOfEmgCars(numberOfEmgCars),
      numberOfPedestrians(numberOfPedestrians) {}

void Street::addCar(const Car& car) {
    cars.push_back(car);
}

void Street::addPedestrian(const Pedestrian& pedestrian) {
    pedestrians.push_back(pedestrian);
}

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

    std::cout << "Number of Cars: " << numberOfCars << std::endl;
    std::cout << "Number of Emergency Cars: " << numberOfEmgCars << std::endl;
    std::cout << "Number of Pedestrians: " << numberOfPedestrians << std::endl;

    std::cout << "Cars on the street:" << std::endl;
    for (const auto& car : cars) {
        car.displayInfo();
    }

    std::cout << "Pedestrians on the street:" << std::endl;
    for (const auto& pedestrian : pedestrians) {
        pedestrian.displayInfo();
    }
}
