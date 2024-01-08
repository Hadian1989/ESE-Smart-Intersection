#include "car.h"
#include "pedestrian.h"

Car::Car(int id, int velocity, bool isEmergency,
         std::pair<int, int> position, Navigation intended_navigation, Direction origin, Direction destination,
         double distance, bool isWaitingResponse, bool isPermitted)
    : id(id), velocity(velocity), isEmergency(isEmergency),
      position(position), intended_navigation(intended_navigation), origin(origin), destination(destination),
      distance(distance), isWaitingResponse(isWaitingResponse), isPermitted(isPermitted) {}

void Car::displayInfo() const {
    std::cout << "Car ID: " << id << std::endl;
    std::cout << "Velocity: " << velocity << " mph" << std::endl;
    std::cout << "Emergency Vehicle: " << (isEmergency ? "Yes" : "No") << std::endl;
    std::cout << "Position: (" << position.first << ", " << position.second << ")" << std::endl;

    // Display the intended navigation as a string
    std::string navigationString;
    switch (intended_navigation) {
        case NORTH_TO_SOUTH:
            navigationString = "North to South";
            break;
        case North_To_EAST:
            navigationString = "North to East";
            break;
        case NORTH_TO_WEST:
            navigationString = "North to West";
            break;
        case SOUTH_TO_NORTH:
            navigationString = "South to North";
            break;
        case SOUTH_To_EAST:
            navigationString = "South to East";
            break;
        case SOUTH_TO_WEST:
            navigationString = "South to West";
            break;
        case EAST_TO_WEST:
            navigationString = "East to West";
            break;
        case EAST_TO_SOUTH:
            navigationString = "East to South";
            break;
        case EAST_TO_NORTH:
            navigationString = "East to North";
            break;
        case WEST_TO_EAST:
            navigationString = "West to East";
            break;
        case WEST_TO_SOUTH:
            navigationString = "West to South";
            break;
        case WEST_TO_NORTH:
            navigationString = "West to North";
            break;
        default:
            navigationString = "Unknown";
    }

    std::cout << "Intended Navigation: " << navigationString << std::endl;
    std::cout << "Distance: " << distance << " miles" << std::endl;
    std::cout << "Waiting for Response: " << (isWaitingResponse ? "Yes" : "No") << std::endl;
}
const bool Car::isEmergency() const{
    return isEmergency;
};
void Car::setPermission(bool newPermission) const{
    is
};
