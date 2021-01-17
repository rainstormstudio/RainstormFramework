#include "jobSystem.h"
#include "../containers/ringBuffer.h"
#include "../../utilities/includes.h"
#include <thread>
#include <atomic>
#include <mutex>
#include <condition_variable>

namespace jobsystem {
    uint32_t nThreads = 0;
    RingBuffer<std::function<void()>, 256> taskPool;
    std::condition_variable wakeCondition;
    std::mutex wakeMutex;
    uint64_t currentID = 0;
    std::atomic<uint64_t> finishedID;
    bool isRunning = false;

    void initialize() {
        finishedID.store(0);
        auto nCores = std::thread::hardware_concurrency();  // number of hardware threads
        nThreads = std::max(1u, nCores);

        isRunning = true;

        for (uint32_t threadID = 0; threadID < nThreads; threadID ++) {
            std::thread worker(
                [] {
                    std::function<void()> task;
                    while (true) {
                        if (!isRunning) break;
                        if (taskPool.pop_front(task)) {
                            task();
                            finishedID.fetch_add(1);
                        } else {
                            std::unique_lock<std::mutex> lock(wakeMutex);
                            wakeCondition.wait(lock);
                        }
                    }
                }
            );
            worker.detach();
        }
    }

    void destroy() {
        isRunning = false;
        wakeCondition.notify_all();
    }

    void execute(const std::function<void()>& task) {
        currentID ++;
        while (!taskPool.push_back(task)) {
            wakeCondition.notify_one();
            std::this_thread::yield();
        }
        wakeCondition.notify_one();
    }

    bool isBusy() {
        return finishedID.load() < currentID;
    }

    void sync() {
        while (isBusy()) {
            wakeCondition.notify_one();
            std::this_thread::yield();
        }
    }
}