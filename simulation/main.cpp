#include <iostream>
#include <algorithm>
#include <vector>
#include <chrono>
#include <thread>
#include <iomanip> // Include for setprecision
enum Direction
{
    SOUTH,
    WEST,
    NORTH,
    EAST
};
enum State
{
    NORMAL,
    EMERGENCY,
    PASSENGER,
    HIGHTRAFFIC
};
class Pedestrian
{
public:
    int id;
    Direction destination;
    bool isWaitingResponse;
    bool isPermitted;
    Pedestrian(int id, Direction destination)
        : id(id), destination(destination) {}
    void setPermission(bool newPermission)
    {
        this->isPermitted = newPermission;
    }
};
class Car
{
public:
    int id;
    double velocity;
    bool isEmergency;
    std::pair<int, int> position;
    Direction origin;
    Direction destination;
    double distance;
    bool isWaitingResponse;
    bool isPermitted;

    Car(int id, double velocity, bool isEmergency,
        std::pair<int, int> position, Direction origin, Direction destination,
        double distance, bool isWaitingResponse, bool isPermitted)
        : id(id), velocity(velocity), isEmergency(isEmergency),
          position(position), origin(origin), destination(destination),
          distance(distance), isWaitingResponse(isWaitingResponse), isPermitted(isPermitted) {}
    const int getId() const
    {
        return id;
    }
    void setPermission(bool newPermission)
    {
        this->isPermitted = newPermission;
    }

    void setVelocity(double newVelocity)
    {
        this->velocity = newVelocity;
    }

    static bool compareCarsByDistance(const Car car1, const Car car2)
    {
        return car1.distance < car2.distance;
    }
};
class Street
{
public:
    int id;
    Direction direction;
    State state;
    std::vector<Car> cars;
    std::vector<Pedestrian> pedestrians;

    Street(int id, Direction direction, State state) : id(id), direction(direction), state(state) {}

    void addCar(const Car car)
    {
        cars.push_back(car);
    }
    void addPedestrian(const Pedestrian pedestrian)
    {
        pedestrians.push_back(pedestrian);
    }
    void removeCar(const Car car)
    {
        for (auto it = cars.begin(); it != cars.end(); ++it)
        {
            if (it->id == car.id)
            {
                cars.erase(it);
                break;
            }
        }
    }
    void setCarPermission(int carId, bool permission)
    {
        this->cars[carId].setPermission(permission);
    }
    void setPedestrianPermission(int pedestrianId, bool permission)
    {
        this->pedestrians[pedestrianId].setPermission(permission);
    }
    void setCarVelocity(int car_id, double new_velocity)
    {
        this->cars[car_id].setVelocity(new_velocity);
    }
    const bool getCarPermission(int car_id) const
    {
        return cars[car_id].isPermitted;
    }
    bool calculateTraffic(std::vector<Car> cars) const
    {
        return cars.size() >= 15;
    }

    const std::vector<Car> getCars() const
    {
        return cars;
    }
    const double getCarVelocity(Car &car) const
    {
        return car.velocity;
    }

    const std::vector<Pedestrian> getPedestrians() const
    {
        return this->pedestrians;
    }

    const std::string getDirectionName() const
    {
        switch (direction)
        {
        case SOUTH:
            return "SOUTH";
        case WEST:
            return "WEST";
        case NORTH:
            return "NORTH";
        case EAST:
            return "EAST";
        default:
            return "UNKNOWN";
        }
    }
    const std::string getPriorityName() const
    {
        switch (this->state)
        {
        case EMERGENCY:
            return "EMERGENCY";
        case HIGHTRAFFIC:
            return "HIGHTRAFFIC";
        case PASSENGER:
            return "PEDESTRIAN";
        default:
            return "NORMAL";
        }
    }

    bool hasPedestrians()
    {
        return !pedestrians.empty();
    }

    void setState(State newState)
    {
        this->state = newState;
    }

    bool hasEmergencyCar(std::vector<Car> &cars) const
    {
        for (const auto &car : cars)
        {
            if (car.isEmergency)
            {
                return true;
            }
        }
        return false;
    }

    void sortAllStreetCarsByDistance(const Street &street)
    {
        std::vector<Car> streetCars = street.getCars();
        cars.insert(cars.end(), streetCars.begin(), streetCars.end());
        std::sort(cars.begin(), cars.end(), [](const Car &car1, const Car &car2)
                  { return car1.distance < car2.distance; });
    }
};
class Intersection
{
public:
    int id;
    std::vector<Street> streets;
    State state = NORMAL;
    bool isExtremeWeather;
    bool isDay;
    Intersection(int id, bool isExtremeWeather, bool isDay) : id(id), isExtremeWeather(isExtremeWeather), isDay(isDay) {}

    void addStreet(const Street &street)
    {
        streets.push_back(street);
    }

    void addCarsToStreet(int streetId, const Car &car)
    {
        if (streetId >= 0 && streetId < streets.size())
        {
            streets[streetId].addCar(car);
        }
        else
        {
            std::cerr << "Invalid street ID." << std::endl;
        }
    }
    void addPedestrianToStreet(int streetId, const Pedestrian &pedestrian)
    {
        if (streetId >= 0 && streetId < streets.size())
        {
            streets[streetId].addPedestrian(pedestrian);
        }
        else
        {
            std::cerr << "Invalid street ID." << std::endl;
        }
    }

    bool isThereEmergencyStreet()
    {
        for (const auto &street : streets)
        {
            if (street.getPriorityName() == "EMERGENCY")
            {
                return true;
                ;
            }
        }
        return false;
    }

    bool isThereHighCongestionStreet(std::vector<Street> streets) const
    {
        for (const auto &street : streets)
        {
            if (street.getPriorityName() == "HIGHTRAFFIC")
            {
                return true;
            }
        }
        return false;
    }

    bool isTherePedestrianStreet(std::vector<Street> streets) const
    {
        for (auto street : streets)
        {
            if (street.state == PASSENGER)
            {
                return true;
            }
        }
        return false;
    }

    const std::vector<Street> getStreets() const
    {
        return streets;
    }
    void sortAllIntersectionCarsByDistance(std::vector<Street> streets)
    {
        std::vector<Car> cars;
        for (const auto &street : streets)
        {
            std::vector<Car> streetCars = street.getCars();
            cars.insert(cars.end(), streetCars.begin(), streetCars.end());
        }

        std::sort(cars.begin(), cars.end(), [](const Car &car1, const Car &car2)
                  { return car1.distance < car2.distance; });
    }
};

class Controller
{
public:
    int id;
    Intersection intersection;
    double speed_limit = 40;
    double extreme_weather_speed_limit = 25;
    double passing_time = 3;
    double extreme_weather_passing_time = 5;
    bool is_there_emergency_street = false;
    bool is_there_pedestrian_street = false;
    bool normal_situation = false;
    Controller(int id, Intersection intersection) : id(id), intersection(intersection) {}

    void addCarToEachStreet(int intersectionId, int streetId, const Car &car)
    {
        intersection.addCarsToStreet(streetId, car);
    }

    void addPedestrianToStreet(int intersectionId, int streetId, const Pedestrian &pedestrian)
    {
        intersection.addPedestrianToStreet(streetId, pedestrian);
    }
    bool calculateTrafficCongestion(Intersection intersection)
    {
        std::vector<Street> streets = intersection.getStreets();
        for (auto &street : streets)
        {
            int totalCars = street.getCars().size();
            std::cout << "The traffic in " << street.getDirectionName() << " street: with " << totalCars << " cars is" << ((totalCars > 15) ? " HIGH" : " LOW") << std::endl;
        }
        return false;
    }

    void setStreetPriority(Intersection intersection)
    {
        std::cout << "set street priority task: start" << std::endl;
        std::vector<Street> streets = intersection.getStreets();
        for (auto &street : streets)
        {
            if (street.hasEmergencyCar(street.cars))
            {
                std::cout << street.getDirectionName() << " street has  EMERGENCY situation" << std::endl;

                intersection.state = State::EMERGENCY;
            }
            else if (street.hasPedestrians())
            {
                std::cout << street.getDirectionName() << " street has PEDESTRIAN situation" << std::endl;
                street.state = State::PASSENGER;
                intersection.state = State::PASSENGER;
            }
            else if (street.calculateTraffic(street.cars))
            {
                std::cout << street.getDirectionName() << " street has HIGH TRAFFIC situation" << std::endl;
                street.state = State::HIGHTRAFFIC;
                intersection.state = State::HIGHTRAFFIC;
            }
            else
            {
                street.state = State::NORMAL;
                intersection.state = State::NORMAL;
                std::cout << street.getDirectionName() << " street has  NORMAL situation " << std::endl;
            }
        }
        std::cout << "set street priority task: end" << std::endl;
    }
    void setPassPermission(Intersection intersection)
    {
        std::cout << "set permission task: start" << std::endl;
        std::vector<Street> streets = intersection.getStreets();
        switch (intersection.state)
        {
        case EMERGENCY:
            for (auto &street : streets)
            {
                if (street.state == EMERGENCY)
                {
                    std::vector<Car> cars = street.getCars();
                    std::vector<Pedestrian> pedestrians = street.getPedestrians();
                    for (auto &car : cars)
                    {
                        if (car.isEmergency)
                        {
                            street.setCarPermission(car.id, true);
                            if (intersection.isExtremeWeather)
                            {
                                street.setCarVelocity(car.id, extreme_weather_speed_limit);
                            }
                            else
                            {
                                street.setCarVelocity(car.id, speed_limit);
                            }

                            std::cout << "car id: " << car.id << " in " << street.getDirectionName() << " street got permit to pass" << std::endl;
                        }
                        else
                        {
                            std::cout << "car id: " << car.id << " in " << street.getDirectionName() << " street did not get permit to pass" << std::endl;
                            street.setCarPermission(car.id, false);
                            street.setCarVelocity(car.id, 0);
                        }
                    }
                    for (auto &pedestrian : pedestrians)
                    {
                        street.setPedestrianPermission(pedestrian.id, false);
                        std::cout << "pedestrian id: " << pedestrian.id << " in " << street.getDirectionName() << " street did not get permit to pass" << std::endl;
                    }
                }
                else
                {
                    std::vector<Car> cars = street.getCars();
                    for (auto &car : cars)
                    {
                        std::cout << "car id: " << car.id << " in " << street.getDirectionName() << " street did not get permit to pass" << std::endl;
                        street.setCarPermission(car.id, false);
                        street.setCarVelocity(car.id, 0);
                    }
                }
            }
        case PASSENGER:
            for (auto &street : streets)
            {
                street.sortAllStreetCarsByDistance(street);
                std::vector<Car> cars = street.getCars();
                std::vector<Pedestrian> pedestrians = street.getPedestrians();
                if (street.state == PASSENGER)
                {
                    for (auto &car : cars)
                    {
                        street.setCarPermission(car.id, false);

                        street.setCarVelocity(car.id, 0);
                        std::cout << "car " << car.id << " in " << street.getDirectionName() << " street did not get permit to pass" << std::endl;
                    }
                    for (auto &pedestrian : pedestrians)
                    {
                        street.setPedestrianPermission(pedestrian.id, true);
                        std::cout << "pedestrian id: " << pedestrian.id << " in " << street.getDirectionName() << " street got permit to pass" << std::endl;
                    }
                }
                else
                {
                    for (auto &car : cars)
                    {
                        if (car.destination == street.direction)
                        {
                            street.setCarPermission(car.id, false);
                            street.setCarVelocity(car.id, 0);
                            std::cout << "car " << car.id << " in " << street.getDirectionName() << " street did not get permit to pass" << std::endl;
                        }
                        else
                        {
                            std::cout << "car " << car.id << " in " << street.getDirectionName() << " street get permit to pass" << std::endl;
                            street.setCarPermission(car.id, true);
                            street.setCarVelocity(car.id, speed_limit);
                        }
                    }
                }
            }
        case HIGHTRAFFIC:
            for (auto &street : streets)
            {
                street.sortAllStreetCarsByDistance(street);
                std::vector<Car> cars = street.getCars();
                if (street.state == HIGHTRAFFIC)
                {
                    int max_index = 15;
                    int index = 0;
                    for (auto &car : cars)
                    {
                        if (index <= 15)
                        {
                            if (intersection.isExtremeWeather)
                            {
                                street.setCarVelocity(car.id, extreme_weather_speed_limit);
                            }
                            else
                            {
                                street.setCarVelocity(car.id, speed_limit);
                            }
                        }
                        street.setCarPermission(car.id, false);
                        street.setCarVelocity(car.id, 0);
                        index++;
                    }
                }
            }
        case NORMAL:
            for (auto &street : streets)
            {
                street.sortAllStreetCarsByDistance(street);
                std::vector<Car> cars = street.getCars();
                for (auto &car : cars)
                {
                    street.setCarPermission(car.id, true);
                    street.setCarVelocity(car.id, speed_limit);
                }
            }
        }
        std::cout << "set permission task: end" << std::endl;
    }
    void displayMovingSimulation(Intersection intersection)
    {
        std::vector<Street> streets = intersection.getStreets();

        std::cout << "moving simulation: start" << std::endl;
        for (auto &street : streets)
        {
            std::vector<Car> cars = street.getCars();
            for (auto car : cars)
            {
                std::cout << "Car Id: " << car.id << " in Street: " << street.getDirectionName() << ", with Priority: " << street.getPriorityName() << std::endl;
                std::cout << " Velocity: " << street.getCars()[car.id].velocity << (street.getCarPermission(car.id) ? " has permission to pass." : " has to stop and wait.") << std::endl;
            }
        }
        std::cout << "moving simulation: end" << std::endl
                  << std::endl;
    }
    void upadteTrafficFlowPermission(Intersection intersection)
    {
        std::cout << "update traffic flow task: start" << std::endl
                  << std::endl;
        std::vector<Street> streets = intersection.getStreets();
        if (intersection.isExtremeWeather)
        {

            std::this_thread::sleep_for(std::chrono::seconds(5));
        }
        else
        {
            std::this_thread::sleep_for(std::chrono::seconds(3));
        }
        for (auto &street : streets)
        {
            std::vector<Car> cars = street.getCars();

            for (auto car : cars)
            {
                if (car.isPermitted)
                {
                    std::cout << "Car: " << car.id << " in " << street.getDirectionName() << " street passed the intersection." << std::endl;
                    street.removeCar(car);
                }
            }
        }
        std::cout << "update traffic flow task: end" << std::endl;
    }
};
int main()
{
    // Create an Intersection instance with extream weather = true and day time = true.
    Intersection intersection(1, true, false);

    Street street1(0, SOUTH, State::NORMAL);
    Car car1(0, 35, false, {20, 30}, SOUTH, EAST, 50, false, false);
    Pedestrian pedestrian1(1, SOUTH);

    Street street2(1, WEST, State::NORMAL);
    Car car2(1, 72, true, {60, 10}, WEST, EAST, 10, false, false);

    Street street3(2, NORTH, State::NORMAL);
    Car car3(2, 43, false, {205, 300}, NORTH, SOUTH, 300, false, false);

    Street street4(3, EAST, State::NORMAL);
    Car car4(3, 31, false, {100, 100}, EAST, NORTH, 100, false, false);

    intersection.addStreet(street1);
    intersection.addStreet(street2);
    intersection.addStreet(street3);
    intersection.addStreet(street4);
    intersection.addCarsToStreet(0, car1);
    intersection.addCarsToStreet(1, car2);
    intersection.addCarsToStreet(2, car3);
    intersection.addCarsToStreet(3, car4);
    intersection.addPedestrianToStreet(0, pedestrian1);

    Controller controller(1, intersection);
    while (true)
    {
        controller.setStreetPriority(intersection);
        controller.setPassPermission(intersection);
        controller.displayMovingSimulation(intersection);
        controller.upadteTrafficFlowPermission(intersection);
    }

    return 0;
}