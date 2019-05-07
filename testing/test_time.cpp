#include <gtest/gtest.h>
#include "doglib/common/utils.h"
#include "doglib/time/timer.h"
#include <unistd.h>
using namespace doglib::time;

TEST(time, sleep){
    Timer timer;
    usleep(10000);
    auto t = timer.get_seconds();
    EXPECT_NEAR(t, 0.01, 0.0005);
    usleep(10000);
    t = timer.get_seconds();
    EXPECT_NEAR(t, 0.02, 0.001);
    timer.reset();
    usleep(10000);
    t = timer.get_seconds();
    EXPECT_NEAR(t, 0.01, 0.0005);
}