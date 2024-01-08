#include "intersection.h"

Intersection::Intersection(int id, std::vector<Street> streets) : id(id) , streets(streets){}

void Intersection::addStreet(const Street &street) {
    streets.push_back(street);
}
void Intersection::addCarsToStreet(int streetId, const std::vector<Car> &cars){
    for (const auto &car : cars){
        streets[streetId].addCar(car);
    }
};
void Intersection::addPedestriansToStreet(int streetId, const std::vector<Pedestrian> &pedestrians){
    for (const auto &pedestrian : pedestrians){
        streets[streetId].addPedestrian(pedestrian);
    }
};

void Intersection::displayIntersection() const {
    std::cout << "Intersection ID: " << id << std::endl;

    for (int i = 0; i < 4; ++i) {
        std::string direction;
        switch (i) {
            case 0:
                direction = "North";
                break;
            case 1:
                direction = "South";
                break;
            case 2:
                direction = "East";
                break;
            case 3:
                direction = "West";
                break;
        }

        std::cout << "Street in " << direction << " direction:" << std::endl;
        streets[i].displayTraffic();
        std::cout << std::endl;
    }
}
const std::vector<Street> Intersection::getStreets() const
{
    return streets;
}
