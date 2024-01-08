#include "street.h"
#include "car.h"
#include "pedestrian.h"
#include "controller.h"
#include "intersection.h"
#include <chrono>
#include <thread>

int main()
{
    Controller controller(1);
    // controller.addCarToEachStreet();
    // controller.addPedestrianToStreet();

    
    while (true)
    {
           auto startPriority = std::chrono::high_resolution_clock::now();
        std::cout << "Start Scheduling: " << std::endl;
        controller.calculateTrafficCongestion();
        auto endPriority = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double, std::milli> priorityDuration = endPriority - startPriority;
        std::cout << "Calculate Priority took " << priorityDuration.count() << " milliseconds." << std::endl;

        auto startPermission = std::chrono::high_resolution_clock::now();
        controller.setCarPermission();
        auto endPermission = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double, std::milli> permissionDuration = endPermission - startPermission;
        std::cout << "Set Permission took " << permissionDuration.count() << " milliseconds." << std::endl;

        std::this_thread::sleep_for(std::chrono::seconds(4)); // 4-second delay

        auto startDisplay = std::chrono::high_resolution_clock::now();
        controller.displayInfo();
        auto endDisplay = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double, std::milli> displayDuration = endDisplay - startDisplay;
        std::cout << "Display Info took " << displayDuration.count() << " milliseconds." << std::endl;

        std::cout << "End Scheduling" << std::endl;
    }
    return 0;
}
