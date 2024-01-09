#include "street.h"
#include "car.h"
#include "pedestrian.h"
#include "controller.h"
#include "intersection.h"
#include <chrono>
#include <thread>

int main()
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

    // Create a Controller instance and pass the Intersection
    Controller controller(1, intersection);

    controller.calculateTrafficCongestion(intersection);
    controller.setCarPermission(intersection);
    auto startDisplay = std::chrono::high_resolution_clock::now();
    controller.movingSimulation(intersection);
    auto endDisplay = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double, std::milli> displayDuration = endDisplay - startDisplay;

    // while (true)
    // {
    // auto startPriority = std::chrono::high_resolution_clock::now();
    // std::cout << "Start Scheduling: " << std::endl;
    // controller.calculateTrafficCongestion();
    // auto endPriority = std::chrono::high_resolution_clock::now();
    // std::chrono::duration<double, std::milli> priorityDuration = endPriority - startPriority;
    // std::cout << "Calculate Priority took " << priorityDuration.count() << " milliseconds." << std::endl;

    // auto startPermission = std::chrono::high_resolution_clock::now();
    // controller.setCarPermission();
    // auto endPermission = std::chrono::high_resolution_clock::now();
    // std::chrono::duration<double, std::milli> permissionDuration = endPermission - startPermission;
    // std::cout << "Set Permission took " << permissionDuration.count() << " milliseconds." << std::endl;

    std::this_thread::sleep_for(std::chrono::seconds(4)); // 4-second delay

    // auto startDisplay = std::chrono::high_resolution_clock::now();
    // controller.movingSimulation();
    // auto endDisplay = std::chrono::high_resolution_clock::now();
    // std::chrono::duration<double, std::milli> displayDuration = endDisplay - startDisplay;

    std::cout << "Simulation took " << displayDuration.count() << " milliseconds." << std::endl;

    std::cout << "End Scheduling" << std::endl;
    // }
    return 0;
}
