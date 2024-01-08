#include "pedestrian.h"


Pedestrian::Pedestrian(int id, Direction intended_direction, bool isWaitingResponse)
    : id(id), intended_direction(intended_direction), isWaitingResponse(isWaitingResponse) {}

void Pedestrian::displayInfo() const {
    std::cout << "Pedestrian ID: " << id << std::endl;

    // Display the intended navigation as a string
    std::string navigationString;
    switch (intended_direction) {
        case SOUTH:
            navigationString = "South";
            break;
        case WEST:
            navigationString = "West";
            break;
        case NORTH:
            navigationString = "North";
            break;
        case EAST:
            navigationString = "East";
            break;
        default:
            navigationString = "Unknown";
    }

    std::cout << "Intended Navigation: " << navigationString << std::endl;
    std::cout << "Waiting for Response: " << (isWaitingResponse ? "Yes" : "No") << std::endl;
}
