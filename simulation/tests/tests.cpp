#include <gtest/gtest.h>
// #include "../src/main.cpp"
#include <iostream>
#include "controller.h"
#include "intersection.h"
#include "street.h"
#include "car.h"

class IntersectionTest : public ::testing::Test
{
protected:
    // Constructor for the test fixture
    IntersectionTest() : intersection(1, true), controller(1, intersection) {} // Assuming Intersection ID is 1

    // Set up the test fixture
    void SetUp() override
    {
        // Create an Intersection instance
        intersection.addStreet(Street(1, SOUTH, NORMAL)); // South
        intersection.addStreet(Street(2, WEST, NORMAL));  // West
        intersection.addStreet(Street(3, NORTH, NORMAL)); // North
        intersection.addStreet(Street(4, EAST, NORMAL));  // East

        // Add cars to streets
        intersection.addCarsToStreet(1, {Car(1, 35, false, {20, 30}, SOUTH, EAST, 50, false, false)});
        intersection.addCarsToStreet(2, {Car(2, 40, false, {205, 300}, NORTH, SOUTH, 300, false, false)});
        intersection.addCarsToStreet(4, {Car(3, 30, false, {100, 100}, EAST, NORTH, 100, false, false)});
        intersection.addCarsToStreet(3, {Car(4, 70, true, {60, 10}, WEST, EAST, 10, false, false)});
    }

    // Declare variables and methods needed for testing

    Intersection intersection;
    Controller controller;
};

TEST(SetStreetPriorityTest, EmergencySituation)
{
    // Arrange
    Intersection intersection(1, true);
    Street emergencyStreet(1, SOUTH, EMERGENCY);
    intersection.addStreet(emergencyStreet);
    Controller controller(1, intersection);
    // Add an emergency car to the street
    Car emergencyCar(1, 50, true, {0, 0}, SOUTH, EAST, 0, false, false);
    intersection.addCarsToStreet(1, emergencyCar);

    // Act
    controller.setStreetPriority(intersection);

    // Assert
    EXPECT_EQ(emergencyStreet.getState(), EMERGENCY);
};
// Test case for calculateTrafficCongestion
TEST_F(IntersectionTest, TrafficCongestionTest)
{
    // Assuming the implementation of calculateTrafficCongestion is in your Intersection class
    bool congestion = controller.calculateTrafficCongestion(intersection);

    // Assert that the method returns the expected result
    ASSERT_FALSE(congestion);
}

int main(int argc, char **argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}