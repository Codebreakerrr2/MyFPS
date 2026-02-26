#include <string>
#include <iostream>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <vector>
#include <queue>
#include <functional>
#include <bits/cxxabi_tweaks.h>
using namespace std;

mutex mux;
condition_variable cv;


vector<thread> workers;
bool stop = false;

static queue<function<void()>> tasks;
struct person{
    person(const std::string& name) : name(name){};
    ~person(){std::cout <<"person destroyed\n";};
    std::string name;
};
vector<person*> ptrPersons;
void addTask(const string& name) {
    function<void()> task = [name]() {
        person p(name);
        cout<< p.name << "\n";
    };
    {
        lock_guard<mutex> lock(mux);
        tasks.push(task);
    }
    cout << "notifiying threads\n";
    cv.notify_one();

}

int main() {



    auto worker= [&]() {
        while (true) {
            function<void()> task;
            {
                unique_lock<mutex> lock(mux);
                cout <<"thread worker entered lock " << this_thread::get_id() << "\n";
                cv.wait(lock,[&](){ return stop || !tasks.empty(); });
                cout <<"lock is being used by " << this_thread::get_id() << "\n";
                if(stop && tasks.empty()){
                    cout << "no tasks and stop pressed\n";
                    return;
                }
                task = move(tasks.front());
                tasks.pop();
            }
            cout << "starting task\n";
            task();
        }
    };
    for (int i = 0; i < 3; i++) {
        workers.push_back(thread(worker));
    }

    addTask("usman");
    this_thread::sleep_for(chrono::milliseconds(100));
    {
        lock_guard<mutex> lock(mux);
        stop = true;
    }
    cv.notify_all();

        for (auto& threads : workers) {
            threads.join();

    }


}
