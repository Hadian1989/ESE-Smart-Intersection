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

// bool Controller::calculateTrafficCongestion(Intersection intersection)
// {
//     std::vector<Street> streets = intersection.getStreets();
//     for (auto &street : streets)
//     {
//         std::cout << "Traffic Calculation for street:" << street.getId() << std::endl;
//         int totalCars = street.getCars().size();
//         // bool traffic = street.calculateTraffic();
//         std::cout << "The traffic in street " << street.getId() << ": With " << totalCars << " cars is" << ((totalCars > 15) ? " HIGH" : " LOW") << std::endl;
//         if (totalCars > 15)
//         {
//             street.setPriority()
//         }
//     }
//     return false;
// }
void Controller::setStreetPriority(Intersection intersection)
{
    std::cout << "setStreetPriority Start" << std::endl;
    // Priority Orders: EMERGENCY > PEDESTRIAN > HIGH_CONGESTION > NORMAL
    std::vector<Street> streets = intersection.getStreets();
    for (auto &street : streets)
    {
        std::vector<Car> cars = street.getCars();
        if (street.checkEmergency(cars))
        {
            // std::cout << "street.setPriority(EMERGENCY)" << std::endl;
            street.setPriority(EMERGENCY);
            std::cout << street.getPriority() << std::endl;
            // break;
        }
        if (street.hasPedestrians())
        {
            // std::cout << "street.setPriority(PASSENGER)" << std::endl;

            street.setPriority(PASSENGER);
            std::cout << street.getPriority() << std::endl;

            // break;
        }
        if (street.calculateTraffic(cars))
        {
            // std::cout << "street.setPriority(HIGHTRAFFIC)" << std::endl;

            street.setPriority(HIGHTRAFFIC);
            // break;
        }
        // std::cout << "street.setPriority(NORMAL)" << std::endl;

        street.setPriority(NORMAL);
    }
        std::cout << "setStreetPriority END" << std::endl;

}

void Controller::setCarPermission(Intersection intersection)
{
    std::cout << "setCarPermission Start" << std::endl;
    double speed_limit = 40.0;
    std::vector<Street> streets = intersection.getStreets();
    if (intersection.isThereEmergencyStreet(streets))
    {
        std::cout << "Threr is Emergency Situation" << std::endl;
        for (auto &street : streets)
        {
            street.sortAllStreetCarsByDistance(street);
            std::vector<Car> cars = street.getCars();
            std::cout << "In the loop we are : " << street.getPriority() << std::endl;
            if (street.getPriority() == EMERGENCY)
            {
                std::cout << "Emergency Situation in street: " << street.getId() << std::endl;
                for (auto &car : cars)
                {
                    if (car.getIsEmergency())
                    {
                        car.setPermission(true);
                        std::cout << car.getPermission() << std::endl;
                        car.setVelocity(speed_limit);
                        std::cout << car.getVelocity() << std::endl;
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
    }
    else if (intersection.isTherePedestrianStreet(streets))
    {
        std::cout << "Pedestrian Situation" << std::endl;

        for (auto &street : streets)
        {
            street.sortAllStreetCarsByDistance(street);
            std::vector<Car> cars = street.getCars();
            if (street.getPriority() == PASSENGER)
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
    }
    else if (intersection.isThereHighCongestionStreet(streets))
    {
        std::cout << "Threr is High Congestion Situation" << std::endl;

        for (auto &street : streets)
        {
            street.sortAllStreetCarsByDistance(street);
            std::vector<Car> cars = street.getCars();
            if (street.getPriority() == HIGHTRAFFIC)
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
    std::cout << "setStreetPriority END" << std::endl;

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
            std::cout << car.getPermission() << std::endl;
            std::cout << "Car Id: " << car.getId() << " in Street: " << street.getDirectionName() << " - Velocity: " << car.getVelocity() << (car.getIsEmergency() ? " is an Emergency Vahicle" : " is a Normal Car") << (car.getPermission() ? " has permission to pass." : " has to stop and wait.") << std::endl;
            std::cout << "Car Id: " << car.getId()  << (car.getPermission() ? " has permission to pass." : " has to stop and wait.") << std::endl;
        }
    }
}
void Controller::upadteTrafficFlow(Intersection intersection)
{
}
