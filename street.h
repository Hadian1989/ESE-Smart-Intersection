#ifndef STREET_H
#define STREET_H

#include <iostream>
#include <string>
#include <vector>
#include "car.h"
#include "pedestrian.h"

enum Direction {
    SOUTH,
    WEST,
    NORTH,
    EAST
};

class Street {
public:
    // Default constructor
    Street() : id(0), direction(SOUTH), numberOfCars(0), numberOfEmgCars(0), numberOfPedestrians(0) {}

    // Parameterized constructor
    Street(int id, Direction direction, int numberOfCars, int numberOfEmgCars, int numberOfPedestrians);

    void addCar(const Car& car);
    void addPedestrian(const Pedestrian& pedestrian);
    void displayTraffic() const;

private:
    int id;
    Direction direction;
    int numberOfCars;
    int numberOfEmgCars;
    int numberOfPedestrians;
    std::vector<Car> cars;
    std::vector<Pedestrian> pedestrians;
};

#endif // STREET_H
