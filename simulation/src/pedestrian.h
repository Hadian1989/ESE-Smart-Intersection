#ifndef PEDESTRIAN_H
#define PEDESTRIAN_H
enum Direction
{
    SOUTH,
    WEST,
    NORTH,
    EAST
};
class Pedestrian
{
public:
    int id;
    Direction destination;
    bool isWaitingResponse;
    bool isPermitted;

    Pedestrian(int id, Direction destination);
    void setPermission(bool newPermission);
};

#endif // PEDESTRIAN_H