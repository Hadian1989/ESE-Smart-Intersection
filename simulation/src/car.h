#ifndef CAR_H
#define CAR_H

#include "pedestrian.h"
#include <utility>

class Car
{
private:
    int id;
    double velocity;
    bool isEmergency;
    std::pair<int, int> location;
    Direction origin;
    Direction destination;
    double distance;
    bool isWaitingResponse;
    bool isPermitted;

public:
    Car(int id, double velocity, bool isEmergency,
        std::pair<int, int> location, Direction origin, Direction destination,
        double distance, bool isWaitingResponse, bool isPermitted);

    const int getId() const;

    void setPermission(bool newPermission);

    void setVelocity(double newVelocity);

    static bool compareCarsByDistance(const Car car1, const Car car2);
};

#endif // CAR_H
