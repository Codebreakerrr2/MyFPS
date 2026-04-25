#pragma once

#include <thread>
#include <queue>
#include <string>
#include <mutex>
#include <condition_variable>
#include <iostream>

#include <winsock2.h>
#include <ws2tcpip.h>

#pragma comment(lib, "ws2_32.lib")

class serverAPI {
public:
    void start() {
        running = true;

        networkThread = std::thread(&serverAPI::networkLoop, this);
        workerThread  = std::thread(&serverAPI::workerLoop, this);
        std::cout<<"server started\n";
    }

    void stop() {
        running = false;
        cv.notify_all();

        if (networkThread.joinable()) networkThread.join();
        if (workerThread.joinable()) workerThread.join();
    }

private:

    // =========================
    // NETWORK THREAD (WIN SOCKET)
    // =========================
    void networkLoop() {

        WSADATA wsaData;
        WSAStartup(MAKEWORD(2,2), &wsaData);

        SOCKET server_fd = socket(AF_INET, SOCK_STREAM, 0);

        sockaddr_in address;
        ZeroMemory(&address, sizeof(address));

        address.sin_family = AF_INET;
        address.sin_port = htons(8081);
        address.sin_addr.s_addr = INADDR_ANY;

        bind(server_fd, (sockaddr*)&address, sizeof(address));
        listen(server_fd, SOMAXCONN);

        while (running) {
            std::cout<<"waiting for connectin \n";
            SOCKET client_fd = accept(server_fd, nullptr, nullptr);

            if (client_fd != INVALID_SOCKET) {
                char buffer[1024] = {0};
                int bytes = recv(client_fd, buffer, sizeof(buffer), 0);
                std::cout<<"dara recieved\n";
                if (bytes > 0) {
                    std::lock_guard<std::mutex> lock(mtx);
                    queue.push(std::string(buffer, bytes));
                    cv.notify_one();
                    std::cout<<"data in queue\n";
                }

                closesocket(client_fd);
            }
        }

        closesocket(server_fd);
        WSACleanup();
    }

    // =========================
    // WORKER THREAD
    // =========================
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

    // =========================
    // THREADS
    // =========================
    std::thread networkThread;
    std::thread workerThread;

    // =========================
    // SHARED QUEUE
    // =========================
    std::queue<std::string> queue;
    std::mutex mtx;
    std::condition_variable cv;

    bool running = false;
};