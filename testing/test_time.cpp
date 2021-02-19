#include <gtest/gtest.h>
#include "doglib/common/utils.h"
#include "doglib/time/timer.h"
#include <unistd.h>
using namespace doglib::time;

TEST(time, sleep){
    Timer timer;
    usleep(100000);
    auto t = timer.get_step_seconds();
    EXPECT_NEAR(t, 0.1, 0.010);
    timer.reset();
    usleep(100000);
    t = timer.get_step_seconds();
    EXPECT_NEAR(t, 0.1, 0.010);
    usleep(100000);
    t = timer.get_step_seconds();
    EXPECT_NEAR(t, 0.1, 0.010);
    t = timer.get_overall_seconds();
    EXPECT_NEAR(t, 0.2, 0.020);
}
