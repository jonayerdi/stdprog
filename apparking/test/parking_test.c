#include "unity.h"
#include "unity_fixture.h"

//SUT
#include "domain/parking.h"
#include "domain/parking_spot_state_machine.h"

//Fakes
#include "test/fake_gpio.h"

#define PARKING_TEST_CONFIG "test.txt"
#define PARKING_SPOTS_COUNT 4

//Globals
static parking_t parking;
static gpio_input_t input[PARKING_SPOTS_COUNT], forced[PARKING_SPOTS_COUNT];

TEST_GROUP(parking);

TEST_SETUP(parking)
{
    //Init parking
    TEST_ASSERT_EQUAL(0, parking_init(&parking, PARKING_TEST_CONFIG));
    //Replace input GPIOs with fakes
    for(int i = 0 ; i < PARKING_SPOTS_COUNT ; i++)
    {
        fake_gpio_input_init(&input[i]);
        fake_gpio_set_value(&input[i], GPIO_VALUE_FREE);
        fake_gpio_input_init(&forced[i]);
        fake_gpio_set_value(&forced[i], GPIO_VALUE_FREE);
        gpio_input_destroy(parking.spots[i].input_source);
        gpio_input_destroy(parking.spots[i].forced_source);
        parking.spots[i].input_source = input[i];
        parking.spots[i].forced_source = forced[i];
    }
}

TEST_TEAR_DOWN(parking)
{
    //Destroy parking
    parking_destroy(&parking);
}

TEST(parking, parking_initial_state)
{
    //Check that initial state is set to Unknown
    for(int i = 0 ; i < PARKING_SPOTS_COUNT ; i++)
        TEST_ASSERT_EQUAL(parking_state_unknown, parking.spots[i].state_machine.estado_actual);
}

TEST(parking, parking_take_spot)
{
    //After first step, every spot transitions to Free
    parking_step(&parking, 0);
    for(int i = 0 ; i < PARKING_SPOTS_COUNT ; i++)
         TEST_ASSERT_EQUAL(parking_state_free, parking.spots[i].state_machine.estado_actual);
    //Start Taking a parking spot
    fake_gpio_set_value(&input[0], GPIO_VALUE_TAKEN);
    parking_step(&parking, 0);
    TEST_ASSERT_EQUAL(parking_state_taking, parking.spots[0].state_machine.estado_actual);
    for(int i = 1 ; i < PARKING_SPOTS_COUNT ; i++)
         TEST_ASSERT_EQUAL(parking_state_free, parking.spots[i].state_machine.estado_actual);
    //Wait for 5 seconds and assert that spot is Taken
    parking_step(&parking, 5000);
    TEST_ASSERT_EQUAL(parking_state_taken, parking.spots[0].state_machine.estado_actual);
    for(int i = 1 ; i < PARKING_SPOTS_COUNT ; i++)
         TEST_ASSERT_EQUAL(parking_state_free, parking.spots[i].state_machine.estado_actual);
}

TEST(parking, parking_free_spot)
{
    //Init GPIOs as Taken
    for(int i = 0 ; i < PARKING_SPOTS_COUNT ; i++)
        fake_gpio_set_value(&input[i], GPIO_VALUE_TAKEN);
    //After first step, every spot transitions to Taken
    parking_step(&parking, 0);
    for(int i = 0 ; i < PARKING_SPOTS_COUNT ; i++)
         TEST_ASSERT_EQUAL(parking_state_taken, parking.spots[i].state_machine.estado_actual);
    //Start Freeing a parking spot
    fake_gpio_set_value(&input[1], GPIO_VALUE_FREE);
    parking_step(&parking, 0);
    TEST_ASSERT_EQUAL(parking_state_taken, parking.spots[0].state_machine.estado_actual);
    TEST_ASSERT_EQUAL(parking_state_freeing, parking.spots[1].state_machine.estado_actual);
    TEST_ASSERT_EQUAL(parking_state_taken, parking.spots[2].state_machine.estado_actual);
    TEST_ASSERT_EQUAL(parking_state_taken, parking.spots[3].state_machine.estado_actual);
    //Wait for 5 seconds and assert that spot is Free
    parking_step(&parking, 5000);
    TEST_ASSERT_EQUAL(parking_state_taken, parking.spots[0].state_machine.estado_actual);
    TEST_ASSERT_EQUAL(parking_state_free, parking.spots[1].state_machine.estado_actual);
    TEST_ASSERT_EQUAL(parking_state_taken, parking.spots[2].state_machine.estado_actual);
    TEST_ASSERT_EQUAL(parking_state_taken, parking.spots[3].state_machine.estado_actual);
}

TEST(parking, parking_force_spot)
{
    //After first step, every spot transitions to Free
    parking_step(&parking, 0);
    for(int i = 0 ; i < PARKING_SPOTS_COUNT ; i++)
         TEST_ASSERT_EQUAL(parking_state_free, parking.spots[i].state_machine.estado_actual);
    //Force a parking spot to taken
    fake_gpio_set_value(&forced[2], GPIO_VALUE_TAKEN);
    parking_step(&parking, 0);
    TEST_ASSERT_EQUAL(parking_state_free, parking.spots[0].state_machine.estado_actual);
    TEST_ASSERT_EQUAL(parking_state_free, parking.spots[1].state_machine.estado_actual);
    TEST_ASSERT_EQUAL(parking_state_taken, parking.spots[2].state_machine.estado_actual);
    TEST_ASSERT_EQUAL(parking_state_free, parking.spots[3].state_machine.estado_actual);
    //Stop forcing spot
    fake_gpio_set_value(&forced[2], GPIO_VALUE_FREE);
    parking_step(&parking, 0);
    TEST_ASSERT_EQUAL(parking_state_free, parking.spots[0].state_machine.estado_actual);
    TEST_ASSERT_EQUAL(parking_state_free, parking.spots[1].state_machine.estado_actual);
    TEST_ASSERT_EQUAL(parking_state_free, parking.spots[2].state_machine.estado_actual);
    TEST_ASSERT_EQUAL(parking_state_free, parking.spots[3].state_machine.estado_actual);
}
