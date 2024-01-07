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
    Car car1(1, 30, false, {20, 30}, SOUTH_To_EAST, 500, false, false);
    Car car2(2, 30, false, {205, 304}, NORTH_TO_SOUTH, 300, false, false);
    Car car3(3, 30, false, {100, 100}, EAST_TO_NORTH, 100, false, false);
    Car car4(4, 30, false, {420, 10}, WEST_TO_EAST, 10, false, false);

    street1.addCar(car1);
    street2.addCar(car2);
    street2.addCar(car3);
    street3.addCar(car4);
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
void Controller::displayInfo(){
     std::cout << "Intersection ID: "  << std::endl;
    std::cout << "Number of Streets: " << std::endl;
    intersection.displayIntersection();

}
