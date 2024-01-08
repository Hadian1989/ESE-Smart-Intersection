#include "controller.h"
#include "intersection.h"
#include "car.h"
#include "street.h"
#include "pedestrian.h"

Controller::Controller(int id)
{
    // Create an Intersection instance
    Intersection intersection(1, {}); // Assuming Intersection ID is 1

    // Add four streets to the intersection
    Street street1(1, SOUTH, {}, {});
    Street street2(2, WEST, {}, {});
    Street street3(3, NORTH, {}, {});
    Street street4(4, EAST, {}, {});
    Pedestrian pedestrian1(1, SOUTH, true);
    Pedestrian pedestrian2(2, WEST, true);
    Car car1(1, 30, false, {20, 30}, SOUTH_To_EAST, SOUTH, EAST, 500, false, false);
    Car car2(2, 50, false, {205, 300}, NORTH_TO_SOUTH, NORTH, SOUTH, 300, false, false);
    Car car3(3, 30, false, {100, 100}, EAST_TO_NORTH, EAST, NORTH, 100, false, false);
    Car car4(4, 70, true, {60, 10}, WEST_TO_EAST, WEST, EAST, 10, false, false);
    Car car5(5, 40, true, {10, 10}, EAST_TO_WEST, EAST, WEST, 10, false, false);

    street1.addCar(car1);
    street2.addCar(car2);
    street2.addCar(car3);
    street3.addCar(car4);
    street1.addCar(car5);
    street4.addPedestrian(pedestrian1);
    street3.addPedestrian(pedestrian2);
    intersection.addStreet(street1); // South
    intersection.addStreet(street2); // West
    intersection.addStreet(street3); // North
    intersection.addStreet(street4); // East
};
void Controller::addCarToEachStreet(int intersectionId, int streetId, const std::vector<Car> &cars)
{
    intersection.addCarsToStreet(streetId, cars);
};
void Controller::addPedestrianToStreet(int intersectionId, int streetId, const std::vector<Pedestrian> &pedestrians)
{
    intersection.addPedestriansToStreet(streetId, pedestrians);
};
void Controller::displayInfo()
{
    std::cout << "Intersection ID: " << std::endl;
    std::cout << "Number of Streets: " << std::endl;
    intersection.displayIntersection();
}

bool Controller::calculateTrafficMode()
{
    std::vector<Street> streets = intersection.getStreets();
    for (auto &street : streets)
    {
        std::cout << "Traffic Calculation for street:" << street.getId() << std::endl;
        int totalCars = street.getCars().size();
        bool traffic = street.calculateTraffic();
        if (traffic)
        {
            std::cout << "The traffic in street " << street.getId() << ": With " << totalCars << " cars is HIGH" << std::endl;
            return true;
        }
        else
        {
            std::cout << "The traffic in street " << street.getId() << ": With " << totalCars << " cars is LOW" << std::endl;
        }
    }
    return false;
}
void Controller::calculatePriority()
{
    std::vector<Street> streets = intersection.getStreets();
    for (auto &street : streets)
    {
        std::vector<Car> cars = street.getCars();
        for (auto &car : cars)
        {
            if (car.isEmergency())
            {
                street.setPriority(EMERGENCY);
                break;
            }
        }
        if (street.calculateTraffic())
        {
            street.setPriority(HIGHTRAFFIC);
        }
        if (street.hasPedestrians())
        {
            street.setPriority(PASSENGER);
        }
        street.setPriority(NORMAL);
    }
}

void Controller::setPermission()
{
    std::vector<Street> streets = intersection.getStreets();
    for (auto &street : streets)
    {
        std::vector<Car> cars = street.getCars();
        for (auto &car : cars)
        {
            if (street.getPriority() == EMERGENCY)
            {
                car.setPermission(true);
                break;
            }
            switch (street.getPriority())
            {
            case EMERGENCY:
                car.setPermission(true);
                break;
            case HIGHTRAFFIC:
                car.setPermission(true);
                break;
            
            default:
                break;
            }
            
        }
    }
}
