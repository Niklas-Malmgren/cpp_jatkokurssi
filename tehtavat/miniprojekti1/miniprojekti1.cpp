#include <thread>
#include <vector>
#include <mutex>
#include <iostream>
#include <chrono>
#include <future>
#include "Game_Task.h"
#include "AI.h"
#include "World_Updater.h"
#include "TaskQueue.h"

int main()
{
    std::vector<Game_Task*> tasks;

    Game_Task* ai_ptr = new AI();
    Game_Task* updater_ptr = new World_Updater();

    tasks.insert(tasks.end(), { ai_ptr,updater_ptr,ai_ptr,updater_ptr,ai_ptr,updater_ptr,ai_ptr,updater_ptr,ai_ptr,updater_ptr,ai_ptr, updater_ptr });

    std::vector<std::future<void>> threads;

    for (int i = 0; i < tasks.size(); i++)
    {
        std::future<void> task = std::async(&Game_Task::perform, tasks[i]);
        threads.push_back(move(task));
    }
}

