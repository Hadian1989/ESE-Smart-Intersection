#ifndef PEDESTRIAN_H
#define PEDESTRIAN_H

#include <iostream>
#include <string>

class Pedestrian {
public:
    Pedestrian(int id, Direction intended_direction , bool is_waiting_response);
    void displayInfo() const;

private:
    int id;
    Direction intended_direction; 
    bool is_waiting_response;
};

#endif // PEDESTRIAN_H