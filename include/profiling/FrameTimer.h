#pragma once
#include <chrono>

namespace Profiling {

    class FrameTimer {
    private:
        using clock= std::chrono::high_resolution_clock;
        std::chrono::time_point<clock> startTime;
        double frameTime = 0.0;

        public:
        void beginFrame() {
            startTime = clock::now();
        }
        void endFrame() {
            auto endTime = clock::now();
            frameTime = std::chrono::duration<double, std::milli>(endTime- startTime).count();
        }
        double getFrameTime() const { return frameTime; }
        double getFPS() const { return 1000.0 / frameTime; } // geschätzt auf einen frame


    };

}
