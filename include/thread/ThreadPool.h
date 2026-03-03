#pragma once
#include <thread>
#include <condition_variable>
#include <mutex>
#include <vector>
#include <queue>
#include <functional>
#include <atomic>


namespace Thread {
    class ThreadPool{

    private:
        std::mutex mux;
        std::condition_variable cv;
        std::vector<std::thread> workers;
        std::queue<std::function<void()>> tasks;
        const size_t threadCount;
        std::atomic<bool> stop{false};
        void worker(){
            std::function<void()> task;

            while(true){

                {
                    std::unique_lock<std::mutex> lock(mux);
                    cv.wait(lock,[&](){return !tasks.empty() || stop.load();});
                    if(stop.load() && tasks.empty()){
                        return;
                    }
                    task = std::move(tasks.front());
                    tasks.pop();
                }

                task();
            }
        };


    public:
        ThreadPool(size_t threadCount) :threadCount(threadCount){
            for(size_t i = 0; i < threadCount; i++){

                workers.push_back(std::thread(&ThreadPool::worker,this));
            }

        };
        ~ThreadPool(){
            stopPool();
        }

        template<typename F, typename... Args>
        void AddTask(F&& f, Args&&... args){
            auto task = [actuallFunction = std::bind(std::forward<F>(f), std::forward<Args>(args)...)]() mutable{
                actuallFunction();
            };
            {
                std::lock_guard<std::mutex> lock(mux);
                tasks.push(task);
            }
            cv.notify_one();
        }


        void stopPool(){
            stop.store(true);
            cv.notify_all();
            for(auto& worker: workers){
                if(worker.joinable()) worker.join();
            }
        }
            




    };
}