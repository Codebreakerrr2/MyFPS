#pragma once
#include <chrono>
namespace Profiling {
    class ScopedTimer {
    public:
        ScopedTimer(double& resultRef)
            : result(resultRef), start(clock::now()) {}

        ~ScopedTimer() {
            auto end = clock::now();
            result = std::chrono::duration<double, std::milli>(end - start).count();
        }

    private:
        using clock = std::chrono::high_resolution_clock;
        double& result;
        std::chrono::time_point<clock> start;

    };
}