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
    Street street1(1, SOUTH);
    Street street2(2, WEST);
    Street street3(3, NORTH);
    Street street4(4, EAST);
    Pedestrian pedestrian1(1, SOUTH, true);
    Pedestrian pedestrian2(2, WEST, true);
    Car car1(1, 35, false, {20, 30}, SOUTH_To_EAST, SOUTH, EAST, 500, false, false);
    Car car2(2, 40, false, {205, 300}, NORTH_TO_SOUTH, NORTH, SOUTH, 300, false, false);
    Car car3(3, 30, false, {100, 100}, EAST_TO_NORTH, EAST, NORTH, 100, false, false);
    Car car4(4, 70, true, {60, 10}, WEST_TO_EAST, WEST, EAST, 10, false, false);
    Car car5(5, 80, true, {10, 10}, EAST_TO_WEST, EAST, WEST, 10, false, false);

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

bool Controller::calculateTrafficCongestion()
{
    std::vector<Street> streets = intersection.getStreets();
    for (auto &street : streets)
    {
        std::cout << "Traffic Calculation for street:" << street.getId() << std::endl;
        int totalCars = street.getCars().size();
        bool traffic = street.calculateTraffic();
        std::cout << "The traffic in street " << street.getId() << ": With " << totalCars << " cars is" << (traffic ? "HIGH" : "LOW") << std::endl;
        if (traffic)
        {
            return true;
        }
    }
    return false;
}
void Controller::setStreetPriority()
{
    // Priority Orders: EMERGENCY > PEDESTRIAN > HIGH_CONGESTION > NORMAL
    std::vector<Street> streets = intersection.getStreets();
    for (auto &street : streets)
    {
        std::vector<Car> cars = street.getCars();
        if (street.checkEmergency())
        {
            street.setPriority(EMERGENCY);
            break;
        }
        if (street.hasPedestrians())
        {
            street.setPriority(PASSENGER);
            break;
        }
        if (street.calculateTraffic())
        {
            street.setPriority(HIGHTRAFFIC);
            break;
        }
        street.setPriority(NORMAL);
    }
}

void Controller::setCarPermission()
{
    std::vector<Street> streets = intersection.getStreets();
    if (intersection.isThereEmergencyStreet())
    {
        for (auto &street : streets)
        {
            std::vector<Car> cars = street.sortAllStreetCarsByDistance(street);
            if (street.getPriority() == EMERGENCY)
            {
                for (auto &car : cars)
                {
                    if (car.getIsEmergency())
                    {
                        car.setPermission(true);
                    }

                    car.setPermission(false);
                }
            }
            else
            {
                for (auto &car : cars)
                {
                    car.setPermission(false);
                }
            }
        }
        return;
    }
    else if (intersection.isTherePedestrianStreet())
    {
        for (auto &street : streets)
        {
            std::vector<Car> cars = street.sortAllStreetCarsByDistance(street);
            if (street.getPriority() == PASSENGER)
            {
                for (auto &car : cars)
                {
                    car.setPermission(false);
                }
            }
            else
            {
                for (auto &car : cars)
                {
                    if (car.getDestination() == street.getDirection())
                    {
                        car.setPermission(false);
                    }
                    else
                    {
                        car.setPermission(true);
                    }
                }
            }
        }
        return;
    }
    else if (intersection.isThereHighCongestionStreet())
    {
        for (auto &street : streets)
        {
            std::vector<Car> cars = street.sortAllStreetCarsByDistance(street);
            if (street.getPriority() == HIGHTRAFFIC)
            {
                int max_index = 20;
                int index = 0;
                for (auto &car : cars)
                {

                    if (index <= 20)
                    {
                        car.setPermission(true);
                    }
                    car.setPermission(false);
                    index++;
                }
            }
            else
            {
                std::vector<Car> allCars = intersection.sortAllIntersectionCarsByDistance();
                // Normal Condition in All streets towards the intersection
                for (auto &car : allCars)
                {
                    car.setPermission(true);
                }
            }
        }
        return;
    }
    else
    {
    }
}
void Controller::checkVehiclesCollision()
{
    std::vector<Street> streets = intersection.getStreets();
    for (auto &street : streets)
    {
        std::vector<Car> cars = street.getCars();
        for (auto &car : cars)
        {
            // switch (car.getDistance())
            // {
            // case /* constant-expression */:
            //     /* code */
            //     break;

            // default:
            //     break;
            // }
        }
    };
}
