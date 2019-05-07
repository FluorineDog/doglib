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
        return duration_cast<microseconds>(diff).count() * 1e-6;
    }

    double reset() {
        record = high_resolution_clock::now();
    }

  private:
    time_point<system_clock, nanoseconds> record;
};

}    // namespace time
}    // namespace doglib