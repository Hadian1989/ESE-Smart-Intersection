#include "car.h"
#include "pedestrian.h"

Car::Car(int id, double velocity, bool isEmergency,
         std::pair<int, int> position, Navigation intended_navigation, Direction origin, Direction destination,
         double distance, bool isWaitingResponse, bool isPermitted)
    : id(id), velocity(velocity), isEmergency(isEmergency),
      position(position), intended_navigation(intended_navigation), origin(origin), destination(destination),
      distance(distance), isWaitingResponse(isWaitingResponse), isPermitted(isPermitted) {}

const int Car::getId()
{
    return id;
};
const bool Car::getIsEmergency()
{
    return isEmergency;
};
const Direction Car::getOrigin()
{
    return origin;
};
const Direction Car::getDestination()
{
    return destination;
};
const double Car::getVelocity()
{
    return velocity;
};
const Navigation Car::getIntendedNavigation()
{
    return intended_navigation;
};
const double Car::getDistance() const
{
    return distance;
}
const bool Car::getPermission() {
    return isPermitted;
};
void Car::setPermission(bool newPermission)
{
     isPermitted = newPermission;
}
void Car::setVelocity(double newVelocity)
{
    velocity = newVelocity;
}
bool Car::compareCarsByDistance(const Car& car1, const Car& car2) {
    return car1.getDistance() < car2.getDistance();
}

