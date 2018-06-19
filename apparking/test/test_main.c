#include "unity_fixture.h"

TEST_GROUP_RUNNER(parking_config)
{
  RUN_TEST_CASE(parking_config, parking_init);
}

TEST_GROUP_RUNNER(parking)
{
  RUN_TEST_CASE(parking, parking_initial_state);
  RUN_TEST_CASE(parking, parking_take_spot);
  RUN_TEST_CASE(parking, parking_free_spot);
  RUN_TEST_CASE(parking, parking_force_spot);
}

static void RunAllTests(void)
{
  RUN_TEST_GROUP(parking_config);
  RUN_TEST_GROUP(parking);
}

int main(int argc, const char * argv[])
{
  return UnityMain(argc, argv, RunAllTests);
}
