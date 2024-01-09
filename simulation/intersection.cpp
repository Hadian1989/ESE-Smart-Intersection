#include "intersection.h"
#include <algorithm>

Intersection::Intersection(int id, std::vector<Street> streets) : id(id), streets(streets) {}

void Intersection::addStreet(const Street &street)
{
    streets.push_back(street);
}
void Intersection::addCarsToStreet(int streetId, const std::vector<Car> &cars)
{
    for (const auto &car : cars)
    {
        streets[streetId].addCar(car);
    }
}
void Intersection::addPedestriansToStreet(int streetId, const std::vector<Pedestrian> &pedestrians)
{
    for (const auto &pedestrian : pedestrians)
    {
        streets[streetId].addPedestrian(pedestrian);
    }
}
bool Intersection::isThereEmergencyStreet(std::vector<Street> streets)
{
    for (auto &street : streets)
    {
        if (street.getPriority() == EMERGENCY)
        {
            return true;
        }
        
    }
    return false;
}
bool Intersection::isThereHighCongestionStreet(std::vector<Street> streets)
{
    for (auto &street : streets)
    {
        if (street.getPriority() == HIGHTRAFFIC)
        {
            return true;
        }
        
    }
    return false;
}
bool Intersection::isTherePedestrianStreet(std::vector<Street> streets)
{
    for (auto &street : streets)
    {
        if (street.getPriority() == PASSENGER)
        {
            return true;
        }
        
    }
    return false;
}

void Intersection::displayIntersection() const
{
    std::cout << "Intersection ID: " << id << std::endl;

    for (int i = 0; i < 4; ++i)
    {
        std::string direction;
        switch (i)
        {
        case 0:
            direction = "North";
            break;
        case 1:
            direction = "South";
            break;
        case 2:
            direction = "East";
            break;
        case 3:
            direction = "West";
            break;
        }

        std::cout << "Street in " << direction << " direction:" << std::endl;
        streets[i].displayTraffic();
        std::cout << std::endl;
    }
}
const std::vector<Street> Intersection::getStreets() const
{
    return streets;
}
void Intersection::sortAllIntersectionCarsByDistance(std::vector<Street> streets)
{
    std::vector<Car> cars;
    for (auto &street : streets)
    {
        std::vector<Car> streetCars = street.getCars();
        cars.insert(cars.end(), streetCars.begin(), streetCars.end());
    }

    // Now, sort the combined vector of cars
    std::sort(cars.begin(), cars.end(), [](const Car &car1, const Car &car2)
              { return car1.getDistance() < car2.getDistance(); });
}
