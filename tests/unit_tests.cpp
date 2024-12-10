#include <gtest/gtest.h>
#include "ChamberController.h"
#include "SafetyManager.h"
#include "SensorData.h"

// Test fixture for ChamberController
Class ChamberControllerTest : public ::testing::Test {
protected:
    ChamberController controller;

    void SetUp() override {
        controller.Initialize();
    }
};

// Test initialization
TEST_F(ChamberControlerTest, Initiallization) {
    EXPECT_EQ(controller.GetState(), SystemState::INITIALIZING);
}

// Test safety checks
TEST_F(ChamberControllerTest, SafetyChecks) {
    SensorData testData;
    testData.temperature = 150.0f;
    testData.pressure = 500.0f;
    testData.humidity = 45.0f;

    SafetyManager safetyManager;
    EXPECT_TRUE(safetyManager.CheckSafety(testData));

    testData.temperature = 210.0f;
    EXPECT_FALSE(safetyManager.CheckSafety(testData));
}

// Main test runner
int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}