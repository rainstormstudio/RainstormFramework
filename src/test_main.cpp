#include "REngine.h"

struct Timer {
    std::string name;
    std::chrono::high_resolution_clock::time_point start;

    Timer(const std::string &name) : name{name}, start{std::chrono::high_resolution_clock::now()} {}
    ~Timer() {
        auto end = std::chrono::high_resolution_clock::now();
        std::cout << name << " : " << std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count() << std::endl;
    }
};

void Spin(float milliseconds)
{
    milliseconds /= 1000.0f;
    std::chrono::high_resolution_clock::time_point t1 = std::chrono::high_resolution_clock::now();
    double ms = 0;
    while (ms < milliseconds)
    {
        std::chrono::high_resolution_clock::time_point t2 = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double> time_span = std::chrono::duration_cast<std::chrono::duration<double>>(t2 - t1);
        ms = time_span.count();
    }
}

int main() {

    JobSystem::initialize();

    {
        auto t = Timer("serial");
        for (int i = 0; i < 16; i ++) {
            Spin(100);
        }
    }

    {
        auto t = Timer("parallel");
        //std::vector<std::thread> threads(16);
        for (int i = 0; i < 16; i ++) {
            //threads[i] = std::thread(Spin, 100);
            JobSystem::execute([]{Spin(100);});
        }/*
        for (auto& th : threads) {
            th.join();
        }*/

        JobSystem::sync();
    }
    std::cout << "done" << glm::sin(3.14) << std::endl;


    JobSystem::destroy();

    return 0;
}