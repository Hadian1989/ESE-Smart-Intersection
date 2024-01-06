#include "street.h"
#include "pedestrian.h"


Pedestrian::Pedestrian(int id, int intended_direction, bool is_waiting_response)
    : id(id), intended_direction(intended_direction), is_waiting_response(is_waiting_response) {}

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
    std::cout << "Waiting for Response: " << (is_waiting_response ? "Yes" : "No") << std::endl;
}
