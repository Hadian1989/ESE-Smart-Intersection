#include "street.h"
#include "car.h"
#include "pedestrian.h"
#include "intersection.h"

int main() {
    // Create instances of Car
    Car car1(1, 60, false, {10, 20}, EAST_TO_WEST, 25.5, false, true);
    Car car2(2, 45, true, {30, 40}, SOUTH_TO_NORTH, 15.0, true, false);

    // Create instances of Pedestrian
    Pedestrian pedestrian1(101, EAST, false);
    Pedestrian pedestrian2(102, WEST, true);

    // Create instances of Street
    Street street1(1001, EAST, 10, 2, 5);
    street1.addCar(car1);
    street1.addCar(car2);
    street1.addPedestrian(pedestrian1);
    street1.addPedestrian(pedestrian2);

    // Create an instance of Intersection
    Intersection intersection(500);
    intersection.addStreet(street1, NORTH);

    // Display information about the intersection
    intersection.displayIntersection();

    return 0;
}
