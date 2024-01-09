#include "controller.h"
#include "intersection.h"
#include "car.h"
#include "street.h"
#include "pedestrian.h"

Controller::Controller(int id, Intersection intersection){};
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

bool Controller::calculateTrafficCongestion(Intersection intersection)
{
    std::vector<Street> streets = intersection.getStreets();
    for (auto &street : streets)
    {
        std::cout << "Traffic Calculation for street:" << street.getId() << std::endl;
        int totalCars = street.getCars().size();
        bool traffic = street.calculateTraffic();
        std::cout << "The traffic in street " << street.getId() << ": With " << totalCars << " cars is" << (traffic ? " HIGH" : " LOW") << std::endl;
        if (traffic)
        {
            return true;
        }
    }
    return false;
}
void Controller::setStreetPriority(Intersection intersection)
{
    calculateTrafficCongestion(intersection);
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

void Controller::setCarPermission(Intersection intersection)
{
    setStreetPriority(intersection);
    double speed_limit = 40.0;
    std::vector<Street> streets = intersection.getStreets();
    if (intersection.isThereEmergencyStreet(streets))
    {
        std::cout << "Threr is Emergency Situation"<< std::endl;
        for (auto &street : streets)
        {
            street.sortAllStreetCarsByDistance(street);
            std::vector<Car> cars = street.getCars();
            if (street.getPriority() == 0)
            {
                for (auto &car : cars)
                {
                    if (car.getIsEmergency())
                    {
                        car.setPermission(true);
                    }

                    car.setPermission(false);
                    car.setVelocity(0);
                }
            }
            else
            {
                for (auto &car : cars)
                {
                    car.setPermission(false);
                    car.setVelocity(0);
                }
            }
        }
        return;
    }
    else if (intersection.isTherePedestrianStreet(streets))
    {
        std::cout << "Threr is Pedestrian Situation" << std::endl;

        for (auto &street : streets)
        {
            street.sortAllStreetCarsByDistance(street);
            std::vector<Car> cars = street.getCars();
            if (street.getPriority() == 1)
            {
                for (auto &car : cars)
                {
                    car.setPermission(false);
                    car.setVelocity(0);
                }
            }
            else
            {
                for (auto &car : cars)
                {
                    if (car.getDestination() == street.getDirection())
                    {
                        car.setPermission(false);
                        car.setVelocity(0);
                    }
                    else
                    {
                        car.setPermission(true);
                        car.setVelocity(speed_limit);
                    }
                }
            }
        }
        return;
    }
    else if (intersection.isThereHighCongestionStreet(streets))
    {
        std::cout << "Threr is High Congestion Situation"<< std::endl;

        for (auto &street : streets)
        {
            street.sortAllStreetCarsByDistance(street);
            std::vector<Car> cars = street.getCars();
            if (street.getPriority() == 2)
            {
                int max_index = 20;
                int index = 0;
                for (auto &car : cars)
                {

                    if (index <= 20)
                    {
                        car.setPermission(true);
                        car.setVelocity(speed_limit);
                    }
                    car.setPermission(false);
                    car.setVelocity(0);
                    index++;
                }
            }
            else
            {
                for (auto &street : streets)
                {
                    street.sortAllStreetCarsByDistance(street);
                    std::vector<Car> cars = street.getCars();
                    // Normal Condition in All streets towards the intersection
                    for (auto &car : cars)
                    {
                        car.setPermission(true);
                    }
                }
            }
        }
        return;
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
void Controller::movingSimulation(Intersection intersection)
{

    setCarPermission(intersection);
    std::vector<Street> streets = intersection.getStreets();

    for (auto &street : streets)
    {
        std::vector<Car> cars = street.getCars();

        for (auto &car : cars)
        {
            std::cout << "Car Id: " << car.getId() << " in Street: " << street.getDirectionName() << " - Velocity: " << car.getVelocity() << (car.getIsEmergency() ? " is an Emergency Vahicle" : "")
                      << (car.getPermission() ? " has permission to pass." : " has to stop and wait.") << std::endl;
        }
    }
}
void Controller::upadteTrafficFlow(Intersection intersection)
{
}
