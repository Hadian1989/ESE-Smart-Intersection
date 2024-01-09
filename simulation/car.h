#ifndef CAR_H
#define CAR_H
#include "pedestrian.h"
#include <iostream>
#include <string>


enum Navigation {
    NORTH_TO_SOUTH,
    North_To_EAST,
    NORTH_TO_WEST,
    SOUTH_TO_NORTH,
    SOUTH_To_EAST,
    SOUTH_TO_WEST,
    EAST_TO_WEST,
    EAST_TO_SOUTH,
    EAST_TO_NORTH,
    WEST_TO_EAST,
    WEST_TO_SOUTH,
    WEST_TO_NORTH 
};

class Car {
public:
    Car(int id, double velocity, bool isEmergency, 
        std::pair<int, int> position, Navigation intended_navigation, Direction origin, Direction destination,
        double distance, bool isWaitingResponse, bool isPermitted);
    void displayInfo() const;
    void setPermission(bool permission);
    void setVelocity(double velocity);
    const int getId();
    const bool getPermission();
    const bool getIsEmergency();
    const Direction getOrigin();
    const Direction getDestination();
    const double getVelocity();
    const Navigation getIntendedNavigation();
    const double getDistance() const;
    bool compareCarsByDistance(const Car& car1, const Car& car2);

private:
    int id;
    int velocity;
    bool isEmergency;
    std::pair<int, int> position; // Assuming a 2D position (x, y)
    Navigation intended_navigation;  // Enum to represent intended direction
    Direction origin;
    Direction destination;
    double distance;
    bool isWaitingResponse;
    bool isPermitted;
};

#endif // CAR_H
