#include "../common/common.h"
#include <chrono>
namespace doglib {
namespace time {
using namespace std::chrono;
class Timer {
  public:
    Timer() {
        reset();
    }
    double get_seconds() {
        auto now = high_resolution_clock::now();
        auto diff = now - record;
        return (double)duration_cast<microseconds>(diff).count() * 1e-6;
    }

    void reset() {
        record = high_resolution_clock::now();
    }

  private:
    time_point<system_clock, nanoseconds> record;
};

template <class Functor>
class TimerAdvanced : public Timer {
  public:
    TimerAdvanced() {
        reset();
    }
    void reset() {
        Functor()();
        Timer::reset();
        
    }
    double get_seconds(){
        Functor()();
        return Timer::get_seconds();
    }
};

}    // namespace time
}    // namespace doglib