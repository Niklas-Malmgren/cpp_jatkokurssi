#include <thread>
#include <vector>
#include <mutex>
#include <iostream>

int sumTotal = 0;
std::mutex mutex;

void sum(std::vector<int> vector)
{
    for (int value : vector)
    {
        mutex.lock();
        sumTotal += value;
        mutex.unlock();
    }
}


int main()
{

    std::vector<int> values;

    for (int i = 0; i < 10000000; i++)
    {
        values.push_back(1);
    }

    std::vector<int> half1(values.begin(), values.begin() + values.size() / 2);
    std::vector<int> half2(values.begin() + values.size() / 2, values.end());

    std::thread first(sum, half1);
    std::thread second(sum, half2);

    first.join();
    second.join();

    std::cout << sumTotal;
}
