/**
 * @file jobSystem.h
 * @author Daniel Hongyu Ding
 * @brief This file defines a job system
 * @version 0.1
 * @date 2021-01-16
 * @ref https://wickedengine.net/2018/11/24/simple-job-system-using-standard-c/
 *
 * @copyright Copyright (c) 2021
 *
 */

#ifndef RS_JOB_MANAGER_H
#define RS_JOB_MANAGER_H

#include <atomic>
#include <functional>

namespace jobManager {

/**
 * @brief initialize the job system
 *
 */
void initialize();

void destroy();

/**
 * @brief add a task to be executed asynchronously
 *
 * @param task for executing a function 'foo()', pass
 * lambda []{foo();}
 */
void execute(const std::function<void()>& task);

/**
 * @brief checks if some threads are not finished
 *
 * @return true
 * @return false
 */
bool isBusy();

/**
 * @brief wait for synchronization
 *
 */
void sync();
}  // namespace jobManager

#endif
