#include "car.h"
#include "pedestrian.h"
#include "street.h"
#include <iostream>
#include <algorithm>  

// Parameterized constructor
Street::Street(int id, Direction direction) : id(id), direction(direction), cars(cars), pedestrians(pedestrians) {}

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

// Method to display traffic information
void Street::displayTraffic() const
{
    std::cout << "Street ID: " << id << std::endl;
    std::cout << "Direction: ";

    switch (direction)
    {
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
    for (const auto &car : cars)
    {
        car.displayInfo();
    }

    std::cout << "Pedestrians on the street:" << std::endl;
    for (const auto &pedestrian : pedestrians)
    {
        pedestrian.displayInfo();
    }
}

// Method to calculate traffic conditions
bool Street::calculateTraffic()
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
    priority = priority;
}
Priority Street::getPriority()
{
    return priority;
}
bool Street::checkEmergency()
{
    for (auto &car : cars)
    {
        if (car.getIsEmergency())
        {
            return true;
        }
        break;
    }
};
std::vector<Car> Street::sortAllStreetCarsByDistance(const Street street)
{
    std::vector<Car> cars;

    std::vector<Car> streetCars = street.getCars();
    cars.insert(cars.end(), streetCars.begin(), streetCars.end());

    // Now, sort the combined vector of cars
    std::sort(cars.begin(), cars.end(), [](const Car &car1, const Car &car2)
              { return car1.getDistance() < car2.getDistance(); });
    return cars;
};