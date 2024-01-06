#include "intersection.h"

Intersection::Intersection(int id) : id(id) {}

void Intersection::addStreet(const Street& street, int direction) {
    if (direction >= 0 && direction < 4) {
        streets[direction] = street;
    } else {
        std::cerr << "Invalid direction for adding street to intersection." << std::endl;
    }
}

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
