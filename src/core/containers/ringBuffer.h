/**
 * @file ringBuffer.h
 * @author Daniel Hongyu Ding
 * @brief This file defines the ring buffer
 * @version 0.1
 * @date 2021-01-16
 * @ref https://wickedengine.net/2018/11/24/simple-job-system-using-standard-c/
 *
 * @copyright Copyright (c) 2021
 *
 */

#ifndef RS_RING_BUFFER_H
#define RS_RING_BUFFER_H

#include <mutex>
#include <thread>

template <typename T, size_t size>
class RingBuffer {
    T data[size];
    size_t front = 0;
    size_t end = 0;
    std::mutex lock;

   public:
    /**
     * @brief push an item to the buffer if possible
     *
     * @param item
     * @return true
     * @return false
     */
    inline bool push_back(const T& item) {
        bool isSuccess = false;
        lock.lock();
        size_t next = (front + 1) % size;
        if (next != end) {
            data[front] = item;
            front = next;
            isSuccess = true;
        }
        lock.unlock();
        return isSuccess;
    }

    /**
     * @brief get an item if possible
     *
     * @param item
     * @return true
     * @return false
     */
    inline bool pop_front(T& item) {
        bool isSuccess = false;
        lock.lock();
        if (front != end) {
            item = data[end];
            end = (end + 1) % size;
            isSuccess = true;
        }
        lock.unlock();
        return isSuccess;
    }
};

#endif
