#include "unity.h"
#include "unity_fixture.h"

//SUT
#include "domain/parking.h"

#define PARKING_TEST_CONFIG "test.txt"
#define PARKING_SPOTS_COUNT 4

TEST_GROUP(parking_config);

TEST_SETUP(parking_config)
{
}

TEST_TEAR_DOWN(parking_config)
{
}

TEST(parking_config, parking_init)
{
    parking_t parking;
    //Init parking
    TEST_ASSERT_EQUAL(0, parking_init(&parking, PARKING_TEST_CONFIG));
    //Assert configuration matches with expected
    TEST_ASSERT_EQUAL(0, parking.has_graphics);
    TEST_ASSERT_EQUAL(2, parking.cameraCount);
    TEST_ASSERT_EQUAL(2, parking.cameras[0].imageFilesCount);
    TEST_ASSERT_EQUAL(4, parking.cameras[1].imageFilesCount);
    TEST_ASSERT_EQUAL(PARKING_SPOTS_COUNT, parking.count);
    //Destroy parking
    parking_destroy(&parking);
}
