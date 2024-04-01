#include <iostream>
#include <thread>
#include <vector>
#include <mutex>
#include <chrono>
#include <algorithm>
#include <execution>

void increment(int &x)
{
    x++;
}

// seq n. 0.3s
// par n. 0.06s
// par_unseq n. 0.06s
int main()
{
    std::chrono::time_point<std::chrono::system_clock> start, end;

    std::vector<int> values;

    for (int i = 0; i < 100000000; i++)
    {
        values.push_back(i);
    }

    start = std::chrono::system_clock::now();
    std::for_each(std::execution::seq, values.begin(), values.end(), &increment);
    end = std::chrono::system_clock::now();
    std::cout << std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count() / 1000.0 << " seconds passed.\n";

    start = std::chrono::system_clock::now();
    std::for_each(std::execution::par, values.begin(), values.end(), &increment);
    end = std::chrono::system_clock::now();
    std::cout << std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count() / 1000.0 << " seconds passed.\n";

    start = std::chrono::system_clock::now();
    std::for_each(std::execution::par_unseq, values.begin(), values.end(), &increment);
    end = std::chrono::system_clock::now();
    std::cout << std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count() / 1000.0 << " seconds passed.\n";
}

