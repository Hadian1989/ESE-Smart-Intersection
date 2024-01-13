#include <iostream>
#include <algorithm>
#include <vector>
#include <chrono>
#include <thread>

enum Direction
{
    SOUTH,
    WEST,
    NORTH,
    EAST
};
enum Priority
{
    NORMAL,
    EMERGENCY,
    PASSENGER,
    HIGHTRAFFIC
};
enum Navigation
{
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

class Pedestrian
{
public:
    int id;
    Direction destination;
    bool isWaitingResponse;
    Pedestrian(int id, Direction destination)
        : id(id), destination(destination) {}
};

class Car
{
    // private:
public:
    int id;
    double velocity;
    bool isEmergency;
    std::pair<int, int> position;
    Navigation intended_navigation;
    Direction origin;
    Direction destination;
    double distance;
    bool isWaitingResponse;
    bool isPermitted;

    Car(int id, double velocity, bool isEmergency,
        std::pair<int, int> position, Navigation intended_navigation, Direction origin, Direction destination,
        double distance, bool isWaitingResponse, bool isPermitted)
        : id(id), velocity(velocity), isEmergency(isEmergency),
          position(position), intended_navigation(intended_navigation), origin(origin), destination(destination),
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

    static bool compareCarsByDistance(const Car &car1, const Car &car2)
    {
        return car1.distance < car2.distance;
    }
};

class Street
{
    // private:
public:
    int id;
    Direction direction;
    Priority priority;
    std::vector<Car> cars;
    std::vector<Pedestrian> pedestrians;

    // public:
    Street(int id, Direction direction, Priority priority) : id(id), direction(direction), priority(priority) {}

    void addCar(const Car &car)
    {
        cars.push_back(car);
    }
    void addPedestrian(const Pedestrian &pedestrian)
    {
        pedestrians.push_back(pedestrian);
    }
    void removeCar(const Car &car)
    {
        std::cout << cars.size() << std::endl;
        for (auto it = cars.begin(); it != cars.end(); ++it)
        {
            if (it->id == car.id)
            {
                cars.erase(it);
                break;
            }
        }
        std::cout << cars.size() << std::endl;
    }
    void setCarPermission(int car_id, bool permission)
    {
        this->cars[car_id].isPermitted = permission;
        this->cars[car_id].setPermission(permission);
    }
    void setCarVelocity(Car &car, double new_velocity)
    {
        car.velocity = new_velocity;
        this->cars[car.id].setVelocity(new_velocity);
    }
    bool getCarPermission(int car_id)
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
        switch (this->priority)
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

    void setPriority(Priority newPriority)
    {
        this->priority = newPriority;
    }

    bool checkEmergency(std::vector<Car> cars) const
    {
        for (const auto &car : cars)
        {
            if (car.isEmergency)
            {
                return true;
                ;
            }
        }
        return false;
    }

    void sortAllStreetCarsByDistance(const Street street)
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
    Intersection(int id, std::vector<Street> streets) : id(id), streets(streets) {}

    void addStreet(Street street)
    {
        this->streets.push_back(street);
    }

    void addCarsToStreet(int streetId, std::vector<Car> cars)
    {
        for (auto car : cars)
        {
            this->streets[streetId].addCar(car);
            std::cout << streetId << streets[streetId].getDirectionName() << std::endl;
        }
    }

    void addPedestriansToStreet(int streetId, std::vector<Pedestrian> pedestrians)
    {
        for (auto pedestrian : pedestrians)
        {
            streets[streetId].addPedestrian(pedestrian);
        }
    }

    bool isThereEmergencyStreet()
    {
        for (const auto street : streets)
        {
            if (street.getPriorityName() == "EMERGENCY")
            {
                return true;
                ;
            }
            if (street.priority == EMERGENCY)
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
                ;
            }
        }
        return false;
    }

    bool isTherePedestrianStreet(std::vector<Street> streets) const
    {
        for (auto street : streets)
        {
            if (street.priority == PASSENGER)
            {
                return true;
                ;
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
    // private:
public:
    int id;
    Intersection intersection;
    double speed_limit = 40.0;
    double extreme_weather_speed_limit = 25;
    double passing_time = 3;
    double extreme_weather_passing_time = 5;
    bool is_there_emergency_street = false;
    bool is_there_pedestrian_street = false;
    bool normal_situation = false;

    // public:
    Controller(int id, Intersection intersection) : intersection(intersection)
    {
    }

    void addCarToEachStreet(int intersectionId, int streetId, const std::vector<Car> &cars)
    {
        intersection.addCarsToStreet(streetId, cars);
    }

    void addPedestrianToStreet(int intersectionId, int streetId, const std::vector<Pedestrian> &pedestrians)
    {
        intersection.addPedestriansToStreet(streetId, pedestrians);
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
        std::cout << "set street priority Start" << std::endl;
        std::vector<Street> streets = intersection.getStreets();
        for (auto &street : streets)
        {
            std::vector<Car> cars = street.getCars();
            if (street.checkEmergency(cars))
            {
                std::cout << street.getDirectionName() << " STREET HAS EMERGENCY SITUATION" << std::endl;
                street.priority = EMERGENCY;
                is_there_emergency_street = true;
                ;
            }
            else if (street.hasPedestrians())
            {
                std::cout << street.getDirectionName() << " STREET HAS PASSENGER SITUATION" << std::endl;
                street.priority = PASSENGER;
                is_there_pedestrian_street = true;
                ;
            }
            else if (street.calculateTraffic(cars))
            {
                std::cout << street.getDirectionName() << " STREET HAS HIGH TRAFFIC SITUATION" << std::endl;
                street.priority = HIGHTRAFFIC;
            }
            else
            {
                street.priority = NORMAL;
                normal_situation = true;
                std::cout << street.getDirectionName() << " STREET HAS NORMAL SITUATION " << std::endl;
            }
        }
        std::cout << "set street priority END" << std::endl
                  << std::endl;
        std::cout << "set car permission Start" << std::endl
                  << std::endl;
        if (is_there_emergency_street)
        {
            for (auto &street : streets)
            {
                std::cout << street.getDirectionName() << " : " << street.getPriorityName() << std::endl;
                // street.sortAllStreetCarsByDistance(street);
                std::vector<Car> cars = street.getCars();
                if (street.priority == EMERGENCY)
                {
                    std::cout << "Emergency Situation in street: " << street.getDirectionName() << std::endl;
                    for (auto &car : cars)
                    {
                        if (car.isEmergency)
                        {
                            street.setCarPermission(car.id, true);
                            street.setCarVelocity(car, speed_limit);
                            std::cout << "car " << car.id << " in " << street.getDirectionName() << " street got permitted to pass" << std::endl;
                        }
                        else
                        {
                            std::cout << "car " << car.id << " in " << street.getDirectionName() << " street did not get permitted to pass" << std::endl;
                            street.setCarPermission(car.id, false);
                            street.setCarVelocity(car, 0);
                        }
                    }
                }
                else
                {
                    for (auto &car : cars)
                    {
                        std::cout << "car " << car.id << " in " << street.getDirectionName() << " street did not get permitted to pass" << std::endl;
                        street.setCarPermission(car.id, false);
                        street.setCarVelocity(car, 0);
                    }
                }
            }
        }
        else if (is_there_pedestrian_street)
        {
            std::cout << "Pedestrian Situation" << std::endl;

            for (auto &street : streets)
            {
                street.sortAllStreetCarsByDistance(street);
                std::vector<Car> cars = street.getCars();
                if (street.priority == PASSENGER)
                {
                    for (auto &car : cars)
                    {
                        std::cout << "car " << car.id << " in " << street.getDirectionName() << " street did not get permitted to pass" << std::endl;

                        car.isPermitted = false;
                        car.velocity = 0;
                    }
                }
                else
                {
                    for (auto car : cars)
                    {
                        if (car.destination == street.direction)
                        {
                            std::cout << "car " << car.id << " in " << street.getDirectionName() << " street did not get permitted to pass" << std::endl;

                            car.isPermitted = false;
                            car.velocity = 0;
                        }
                        else
                        {
                            std::cout << "car " << car.id << " in " << street.getDirectionName() << " street get permitted to pass" << std::endl;

                            car.isPermitted = true;
                            ;
                            car.velocity = speed_limit;
                        }
                    }
                }
            }
        }
        else if (intersection.isThereHighCongestionStreet(streets))
        {
            std::cout << "Threr is High Congestion Situation" << std::endl;

            for (auto &street : streets)
            {
                street.sortAllStreetCarsByDistance(street);
                std::vector<Car> cars = street.getCars();
                if (street.priority == HIGHTRAFFIC)
                {
                    int max_index = 20;
                    int index = 0;
                    for (auto car : cars)
                    {

                        if (index <= 20)
                        {
                            car.setPermission(true);
                            car.setVelocity(speed_limit);
                        }
                        car.setPermission(false);
                        car.setVelocity(0);
                        index++;
                    }
                }
            }
        }
        else if (normal_situation)
        {
            for (auto &street : streets)
            {
                // street.sortAllStreetCarsByDistance(street);
                std::vector<Car> cars = street.getCars();
                // Normal Condition in All streets towards the intersection
                for (auto &car : cars)
                {
                    car.setPermission(true);
                    car.setPermission(speed_limit);
                }
            }
        }
        std::cout << "set car permission END" << std::endl
                  << std::endl;
        std::cout << "moving simulation START" << std::endl
                  << std::endl;
        // for (int i = 0; i < 4; i++)
        for (auto street : streets)
        {
            std::vector<Car> cars = street.getCars();
            for (auto car : cars)
            {
                std::cout << "Car Id: " << car.id << " in Street: " << street.getDirectionName() << " - Velocity: " << street.getCars()[car.id].velocity << ", with Priority: "
                          << street.getPriorityName() << (street.getCarPermission(car.id) ? " has permission to pass." : " has to stop and wait.") << std::endl;
            }
        }
        std::cout << "moving simulation END" << std::endl
                  << std::endl;
        std::cout << "wait for 3 seconds start" << std::endl
                  << std::endl;
        std::this_thread::sleep_for(std::chrono::seconds(3));
        for (auto street : streets)
        {
            std::vector<Car> cars = street.getCars();

            for (auto &car : cars)
            {
                if (car.isEmergency && car.isPermitted)
                {
                    street.removeCar(car);
                }
            }
        }
    }

    void setCarPermission(Intersection intersection)
    {
        std::cout << "setCarPermission Start" << std::endl;
        std::vector<Street> streets = intersection.getStreets();
        if (intersection.isThereEmergencyStreet())
        {
            std::cout << "Threr is Emergency Situation" << std::endl;
            for (auto &street : streets)
            {
                street.sortAllStreetCarsByDistance(street);
                std::vector<Car> cars = street.getCars();
                if (street.priority == EMERGENCY)
                {
                    std::cout << "Emergency Situation in street: " << street.id << std::endl;
                    for (auto &car : cars)
                    {
                        if (car.isEmergency)
                        {
                            car.setPermission(true);
                            car.setVelocity(speed_limit);
                        }

                        car.setPermission(false);
                        car.setVelocity(0);
                    }
                }
                else
                {
                    for (auto &car : cars)
                    {
                        car.setPermission(false);
                        car.setVelocity(0);
                    }
                }
            }
        }
        else if (intersection.isTherePedestrianStreet(streets))
        {
            std::cout << "Pedestrian Situation" << std::endl;

            for (auto &street : streets)
            {
                street.sortAllStreetCarsByDistance(street);
                std::vector<Car> cars = street.getCars();
                if (street.priority == PASSENGER)
                {
                    for (auto &car : cars)
                    {
                        car.setPermission(false);
                        car.setVelocity(0);
                    }
                }
                else
                {
                    for (auto &car : cars)
                    {
                        if (car.destination == street.direction)
                        {
                            car.setPermission(false);
                            car.setVelocity(0);
                        }
                        else
                        {
                            car.setPermission(true);
                            car.setVelocity(speed_limit);
                        }
                    }
                }
            }
        }
        else if (intersection.isThereHighCongestionStreet(streets))
        {
            std::cout << "Threr is High Congestion Situation" << std::endl;

            for (auto &street : streets)
            {
                street.sortAllStreetCarsByDistance(street);
                std::vector<Car> cars = street.getCars();
                if (street.priority == HIGHTRAFFIC)
                {
                    int max_index = 20;
                    int index = 0;
                    for (auto &car : cars)
                    {

                        if (index <= 20)
                        {
                            car.setPermission(true);
                            car.setVelocity(speed_limit);
                        }
                        car.setPermission(false);
                        car.setVelocity(0);
                        index++;
                    }
                }
            }
        }
        else
        {
            for (auto &street : streets)
            {
                street.sortAllStreetCarsByDistance(street);
                std::vector<Car> cars = street.getCars();
                for (auto &car : cars)
                {
                    car.setPermission(true);
                    car.setPermission(speed_limit);
                }
            }
        }
        std::cout << "setCarPermission END" << std::endl;
    }

    void movingSimulation(Intersection intersection)
    {
        std::vector<Street> streets = intersection.getStreets();

        for (auto &street : streets)
        {
            std::vector<Car> cars = street.getCars();

            for (auto &car : cars)
            {
                std::cout << "Car Id: " << car.id << " in Street: " << street.getDirectionName() << " - Velocity: " << car.velocity << ", with Priority: " << street.getPriorityName() << (car.isEmergency ? " has permission to pass." : " has to stop and wait.") << std::endl;
            }
        }
    }

    void upadteTrafficFlow(Intersection intersection)
    {
        // Implement your code here
        // ...
    }
};

int main()
{
    // Create an Intersection instance
    Intersection intersection(1, {}); // Assuming Intersection ID is 1

    // Add four streets to the intersection
    Street street1(1, SOUTH, NORMAL);
    Street street2(2, WEST, NORMAL);
    Street street3(3, NORTH, NORMAL);
    Street street4(4, EAST, NORMAL);
    Pedestrian pedestrian1(1, SOUTH);
    Pedestrian pedestrian2(2, WEST);
    Car car1(1, 35, false, {20, 30}, SOUTH_To_EAST, SOUTH, EAST, 50, false, false);
    Car car2(2, 40, false, {205, 300}, NORTH_TO_SOUTH, NORTH, SOUTH, 300, false, false);
    Car car3(3, 30, false, {100, 100}, EAST_TO_NORTH, EAST, NORTH, 100, false, false);
    Car car4(4, 70, true, {60, 10}, WEST_TO_EAST, WEST, EAST, 10, false, false);

    
    intersection.addStreet(Street(1, SOUTH, NORMAL)); // South
    intersection.addStreet(Street(2, WEST, NORMAL));  // West
    intersection.addStreet(Street(3, NORTH, NORMAL)); // North
    intersection.addStreet(Street(4, EAST, NORMAL));  // East
    intersection.addCarsToStreet(1, {car1});
    intersection.addCarsToStreet(2, {car2, car3});
    intersection.addCarsToStreet(3, {car4});
    // intersection.addCarsToStreet(4, {car1});
    street4.addPedestrian(pedestrian1);
    street3.addPedestrian(pedestrian2);

    // Create a Controller instance and pass the Intersection
    Controller controller(1, intersection);
    // controller.calculateTrafficCongestion(intersection);
    controller.setStreetPriority(intersection);
    // controller.setCarPermission(intersection);
    auto startDisplay = std::chrono::high_resolution_clock::now();
    // controller.movingSimulation(intersection);
    auto endDisplay = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double, std::milli> displayDuration = endDisplay - startDisplay;

    // while (true;)
    // {
    // Your loop logic goes here

    // Call methods or perform actions within the loop
    // controller.setStreetPriority(intersection);
    // controller.movingSimulation(intersection);

    // Sleep for a certain duration (e.g., 1 second) before the next iteration
    std::this_thread::sleep_for(std::chrono::seconds(1));
    // }

    return 0;
}