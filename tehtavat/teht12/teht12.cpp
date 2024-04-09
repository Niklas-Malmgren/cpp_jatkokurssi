#include <iostream>
#include <vector>
#include <algorithm>

#include <thread>
#include <vector>
#include <mutex>
#include <iostream>
#include <chrono>
#include <future>

class functionObject
{
public:
    int operator() (int& x) { return x = (x <= 100) ? 0 : x - 100; };
};

void hit(int& x)
{
    x = (x <= 100) ? 0 : x - 100;
}

int main()
{
    std::vector<int> hitpoints;

    for (int i = 0; i < 20; i++)
    {
        hitpoints.push_back(i * 10);
    }

    //std::for_each(hitpoints.begin(), hitpoints.end(), hit);


    //functionObject function_object;
    //std::for_each(hitpoints.begin(), hitpoints.end(), function_object);


    //std::for_each(hitpoints.begin(), hitpoints.end(), [](int& x) {x = (x <= 100) ? 0 : x - 100; });


    auto lambda_func = [](int& x) {x = (x <= 100) ? 0 : x - 100; };
    std::for_each(hitpoints.begin(), hitpoints.end(), lambda_func);


    std::sort(hitpoints.begin(), hitpoints.end(), [](int a, int b) { return a > b; });

    for (int x : hitpoints)
    {
        std::cout << x << "\n";
    }
}
