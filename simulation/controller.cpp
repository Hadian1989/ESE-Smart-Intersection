#include "controller.h"
#include "intersection.h"
#include "car.h"
#include "pedestrian.h"

Controller::Controller() {
    // Create an Intersection instance
    intersection = Intersection(1); // Assuming Intersection ID is 1

    // Add four streets to the intersection
    Street street1(1, SOUTH, 3, 1, 0);
    Street street2(2, WEST, 3, 1, 0);
    Street street3(3, NORTH, 3, 1, 0);
    Street street4(4, EAST, 3, 1, 0);
    Pedestrian pedestrian(1, SOUTH, false);
    Pedestrian pedestrian(2, WEST, false);
    Car car1(1,30,false,{20,30}, SOUTH_To_EAST, 500, false,false);
    Car car2(2,30,false,{20,30}, NORTH_TO_SOUTH, 300, false,false);
    Car car3(3,30,false,{20,30}, EAST_TO_NORTH, 100, false,false);
    Car car4(4,30,false,{20,30}, WEST_TO_EAST, 10, false,false);

    intersection.addStreet(street1, 0);  // South
    intersection.addStreet(street2, 1);  // West
    intersection.addStreet(street3, 2);  // North
    intersection.addStreet(street4, 3);  // East

    // Add random cars, pedestrians, and an emergency car
    addRandomCars();
    addRandomPedestrians();
    addRandomEmergencyCar();
}

void Controller::addRandomCars() {
    for (int i = 0; i < 4; ++i) {
        // Add three cars to each street
        for (int j = 0; j < 3; ++j) {
            // Generate random values for car properties
            int carId = rand() % 100 + 1;
            int velocity = rand() % 30 + 20; // Random velocity between 20 and 50
            bool isEmergency = false;
            std::pair<int, int> position = std::make_pair(0, 0); // Set position to (0, 0) for simplicity
            Navigation intendedNavigation = static_cast<Navigation>(rand() % 12);
            double distance = 0.0;
            bool isWaitingResponse = rand() % 2 == 0; // Randomly true or false
            bool isGetPermit = rand() % 2 == 0; // Randomly true or false

            Car car(carId, velocity, isEmergency, position, intendedNavigation, distance, isWaitingResponse, isGetPermit);
        
            // Add the car to the street
            intersection.Street.addCar(i, car);
        }
    }
}

void Controller::addRandomPedestrians() {

}

void Controller::addRandomEmergencyCar() {
    // Add an emergency car to a random street
    int randomStreet = rand() % 4;
    
    // Generate random values for emergency car properties
    int carId = rand() % 100 + 1;
    int velocity = rand() % 30 + 20; // Random velocity between 20 and 50
    bool isEmergency = true;
    std::pair<int, int> position = std::make_pair(0, 0); // Set position to (0, 0) for simplicity
    Navigation intendedNavigation = static_cast<Navigation>(rand() % 12);
    double distance = 0.0;
    bool isWaitingResponse = rand() % 2 == 0; // Randomly true or false
    bool isGetPermit = rand() % 2 == 0; // Randomly true or false

    Car emergencyCar(carId, velocity, isEmergency, position, intendedNavigation, distance, isWaitingResponse, isGetPermit);

    // Add the emergency car to the street
    intersection.addStreet(randomStreet, emergencyCar);
}
