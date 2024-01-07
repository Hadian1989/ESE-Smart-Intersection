#ifndef STREET_H
#define STREET_H

#include <iostream>
#include <string>
#include <vector>
#include "car.h"
#include "pedestrian.h"

class Street
{
public:
    // Parameterized constructor
    Street(int id, Direction direction, std::vector<Car> cars, std::vector<Pedestrian> pedestrians);

    void addCar(const Car &car);
    void addPedestrian(const Pedestrian &pedestrian);
    void displayTraffic() const;
    bool calculateTraffic();

private:
    int id;
    Direction direction;
    std::vector<Car> cars;
    std::vector<Pedestrian> pedestrians;
};

#endif // STREET_H
