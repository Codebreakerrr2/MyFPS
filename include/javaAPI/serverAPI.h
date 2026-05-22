#pragma once

#include <thread>
#include <queue>
#include <string>
#include <mutex>
#include <condition_variable>
#include <iostream>

#include "httplib/httplib.h"

class serverAPI {
public:
    void start() {
        running = true;

        networkThread = std::thread(&serverAPI::networkLoop, this);
        workerThread  = std::thread(&serverAPI::workerLoop, this);

        std::cout << "server started\n";
    }

    void stop() {
        running = false;
        cv.notify_all();

        if (networkThread.joinable()) networkThread.join();
        if (workerThread.joinable()) workerThread.join();
    }

private:


    void networkLoop() {

    }


    void workerLoop() {
        while (running) {
            std::unique_lock<std::mutex> lock(mtx);

            cv.wait(lock, [this] {
                return !queue.empty() || !running;
            });

            if (!running) break;

            auto msg = queue.front();
            queue.pop();

            lock.unlock();

            std::cout << "Processing: " << msg << std::endl;


        }
    }

    std::thread networkThread;
    std::thread workerThread;


    std::queue<std::string> queue;
    std::mutex mtx;
    std::condition_variable cv;

    bool running = false;
};