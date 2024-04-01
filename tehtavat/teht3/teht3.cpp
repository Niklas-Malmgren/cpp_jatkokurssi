#include <thread>
#include <vector>
#include <mutex>
#include <iostream>
#include <chrono>
#include "Game_Task.h"
#include "AI.h"
#include "World_Updater.h"


// ~11s ilman rinnakkaistamista.
// ~2.5s rinnakkaistettuna (11 säiettä)
int main()
{
    const int processor_count = std::thread::hardware_concurrency();
    std::cout << "Max threads: " << processor_count << "\n";

    std::chrono::time_point<std::chrono::system_clock> start, end;
    start = std::chrono::system_clock::now();

    std::vector<Game_Task*> tasks;

    Game_Task* ai_ptr = new AI();
    Game_Task* updater_ptr = new World_Updater();

    tasks.insert(tasks.end(), { ai_ptr,updater_ptr,ai_ptr,updater_ptr,ai_ptr,updater_ptr,ai_ptr,updater_ptr,ai_ptr,updater_ptr,ai_ptr });

    std::vector<std::thread> threads;

    int number_of_tasks = tasks.size();
    for (int i = 0; i < number_of_tasks; i++)
    {
        //tasks[i]->perform();

        std::thread thread(&Game_Task::perform, tasks[i]);
        threads.push_back(move(thread));
    }

    for (int i = 0; i < number_of_tasks; i++)
    {
        threads[i].join();
    }

    end = std::chrono::system_clock::now();
    std::cout << std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count() / 1000.0 << " seconds passed.\n";
}
