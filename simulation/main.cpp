#include "street.h"
#include "car.h"
#include "pedestrian.h"
#include "controller.h"
#include "intersection.h"

int main()
{
    Controller controller(1);
    // controller.addCarToEachStreet();
    // controller.addPedestrianToStreet();

    
    while (true)
    {
        std::cout << "Start Sceduling: " << std::endl;
        controller.calculatePriority();
        controller.setPermission();
        controller.displayInfo();
        std::cout << "End Sceduling" << std::endl;
    }
    return 0;
}
