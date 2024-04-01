#include <iostream>
#include <vector>
#include <future> 

int sum(std::vector<int> vector)
{
    int sum = 0;

    for (int value : vector)
    {
        sum += value;
    }
    return sum;
}


int main()
{
    int sumTotal = 0;

    std::vector<int> values;

    for (int i = 0; i < 100000000; i++)
    {
        values.push_back(1);
    }

    std::vector<int> half1(values.begin(), values.begin() + values.size() / 2);
    std::vector<int> half2(values.begin() + values.size() / 2, values.end());

    std::future<int> sum1 = std::async(sum, half1);
    std::future<int> sum2 = std::async(sum, half2);

    sumTotal = sum1.get() + sum2.get();

    std::cout << sumTotal;
}
