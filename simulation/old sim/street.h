#ifndef STREET_H
#define STREET_H

#include <iostream>
#include <string>
#include <vector>
#include "car.h"
#include "pedestrian.h"

enum Priority {
    EMERGENCY= 1,
    HIGHTRAFFIC,
    PASSENGER,
    NORMAL
};

class Street
{
public:
    // Parameterized constructor
    Street(int id, Direction direction,Priority priority);

    void addCar(const Car &car);
    void addPedestrian(const Pedestrian &pedestrian);
    bool calculateTraffic(std::vector<Car> cars);
    bool checkEmergency(std::vector<Car> cars);

    const int getId() const;
    const std::vector<Car> &getCars() const;
    const std::vector<Pedestrian> &getPedestrians() const;
    const bool hasPedestrians() const;
    // Setters for hasPriority
    void setPriority(Priority priority);
    Priority getPriority();
    const Direction getDirection() const;
    const std::string  getDirectionName() const;
    void sortAllStreetCarsByDistance(const Street street);



private:
    int id;
    bool isTrafficHigh;
    Priority priority;
    Direction direction;
    std::vector<Car> cars;
    std::vector<Pedestrian> pedestrians;
};

#endif // STREET_H
