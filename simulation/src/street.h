#ifndef STREET_H
#define STREET_H

#include <vector>
#include <string>
#include "car.h"
#include "pedestrian.h"
enum State
{
    NORMAL,
    EMERGENCY,
    PASSENGER,
    HIGHTRAFFIC
};

class Street
{
private:
    int id;
    Direction direction;
    State state;
    std::vector<Car> cars;
    std::vector<Pedestrian> pedestrians;

public:
    Street(int id, Direction direction, State state);  // Constructor
    bool calculateTraffic(std::vector<Car> cars) const;
    void setCarPermission(int carId, bool permission);
    void setPedestrianPermission(int pedestrianId, bool permission);
    void sortStreetCarsByDistance(const Street &street);



    bool hasEmergencyCar(std::vector<Car> &cars) const;
    void addCar(const Car car);
    void addPedestrian(const Pedestrian pedestrian);
    void removeCar(const Car car);

    

    void setCarVelocity(int car_id, double new_velocity);
    const bool getCarPermission(int car_id) const;
    const std::vector<Car> getCars() const;
    const double getCarVelocity(Car &car) const;
    const std::vector<Pedestrian> getPedestrians() const;
    const std::string getDirectionName() const;
    const std::string getPriorityName() const;
    bool hasPedestrians();
    void setState(State newState);
    const State getState();

    
};

#endif // STREET_H
