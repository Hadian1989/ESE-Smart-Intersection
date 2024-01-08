#ifndef PEDESTRIAN_H
#define PEDESTRIAN_H

#include <iostream>
#include <string>

enum Direction {
    SOUTH,
    WEST,
    NORTH,
    EAST
};
class Pedestrian {
public:
    Pedestrian(int id, Direction intended_direction , bool isWaitingResponse);
    void displayInfo() const;

private:
    int id;
    Direction intended_direction; 
    bool isWaitingResponse;
};

#endif // PEDESTRIAN_H