#include <string>
#include <iostream>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <vector>
#include <queue>
#include <functional>
using namespace std;

struct person{
    person(const std::string& name) : name(name){};
    ~person(){std::cout <<"person destroyed\n";};
    std::string name;
};


int main() {
    mutex mux;
    condition_variable cv;
    vector<person*> ptrPersons;
    queue<function<void(const string& name)>> tasks;
    vector<thread> workers;
    bool stop = false;

    auto createPerson = [](const string& name){
        person p(name);
        cout <<p.name;
    };
    auto worker= [&](const string& name) {
        while (true) {
            function<void(const string& name)> task;
            {
                unique_lock<mutex> lock(mux);
                cv.wait(lock,[&](){ return stop || !tasks.empty(); });
                if(stop && tasks.empty()){
                    return;
                }
                task = move(tasks.front());
                tasks.pop();
            }
            task(name);
        }
    };

    tasks.push(createPerson);

}
