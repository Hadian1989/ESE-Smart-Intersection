#include "car.h"
#include "pedestrian.h"
#include "street.h"
#include <iostream>
#include <algorithm>

// Parameterized constructor
Street::Street(int id, Direction direction, Priority priority) : id(id), direction(direction) , priority(priority){}

// Method to add a car to the street
void Street::addCar(const Car &car)
{
    cars.push_back(car);
}

// Method to add a pedestrian to the street
void Street::addPedestrian(const Pedestrian &pedestrian)
{
    pedestrians.push_back(pedestrian);
}

// Method to calculate traffic conditions
bool Street::calculateTraffic(std::vector<Car> cars)
{
    return cars.size() >= 15;
}
const std::vector<Car> &Street::getCars() const
{
    return cars;
}

const std::vector<Pedestrian> &Street::getPedestrians() const
{
    return pedestrians;
}
const Direction Street::getDirection() const
{
    return direction;
};
const std::string Street::getDirectionName() const
{
    switch (direction)
    {
    case SOUTH:
        return "SOUTH";
    case WEST:
        return "WEST";
    case NORTH:
        return "NORTH";
    case EAST:
        return "EAST";
    default:
        return "UNKNOWN";
    }
};
const bool Street::hasPedestrians() const
{
    return (pedestrians.size() > 0);
}
const int Street::getId() const
{
    return id;
}
void Street::setPriority(Priority newPriority)
{
    priority = newPriority;
}
Priority Street::getPriority()
{
    return priority;
}
bool Street::checkEmergency(std::vector<Car> cars)
{
    for (auto &car : cars)
    {
        if (car.getIsEmergency())
        {
            return true;
        }
    }
    return false;
}
void Street::sortAllStreetCarsByDistance(const Street street)
{
    std::vector<Car> cars;

    std::vector<Car> streetCars = street.getCars();
    cars.insert(cars.end(), streetCars.begin(), streetCars.end());

    // Now, sort the combined vector of cars
    std::sort(cars.begin(), cars.end(), [](const Car &car1, const Car &car2)
              { return car1.getDistance() < car2.getDistance(); });
};