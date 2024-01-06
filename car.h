#ifndef CAR_H
#define CAR_H

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
    Car(int id, int velocity, bool is_emergency, 
        std::pair<int, int> position, Navigation intended_navigation,
        double distance, bool is_waiting_response, bool is_get_permit);
    void displayInfo() const;

private:
    int id;
    int velocity;
    bool is_emergency;
    std::pair<int, int> position; // Assuming a 2D position (x, y)
    Direction intended_navigation;  // Enum to represent intended direction
    double distance;
    bool is_waiting_response;
    bool is_get_permit;
};

#endif // CAR_H
