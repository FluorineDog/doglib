#include "../common/common.h"
#include <chrono>
#include <functional>
namespace doglib {
namespace time {
using namespace std::chrono;
class Timer {
  public:
    Timer() {
        reset();
    }
    double get_overall_seconds() {
        auto now = high_resolution_clock::now();
        auto diff = now - init_record;
        step_record = now;
        return (double)duration_cast<microseconds>(diff).count() * 1e-6;
    }

    double get_step_seconds() {
        auto now = high_resolution_clock::now();
        auto diff = now - step_record;
        step_record = now;
        return (double)duration_cast<microseconds>(diff).count() * 1e-6;
    }

    void reset() {
        step_record = init_record = high_resolution_clock::now();
    }

  private:
    time_point<system_clock, nanoseconds> init_record;
    time_point<system_clock, nanoseconds> step_record;
};

class TimerAdvanced : public Timer {
  public:
    TimerAdvanced(std::function<void(void)> functor): functor(functor) {
        Timer::reset();
    }
    void reset() {
        functor();
        Timer::reset();
    }
    double get_overall_seconds() {
        functor();
        return Timer::get_overall_seconds();
    }
    double get_step_seconds() {
        functor();
        return Timer::get_step_seconds();
    }
  private:
    std::function<void(void)> functor;
};

}    // namespace time
}    // namespace doglib