#include <thread>
#include <mutex>
#include <iostream>

std::mutex mutex;
int bankAccount = 0;

void deposit()
{
    const std::lock_guard<std::mutex>lock(mutex);

    for (int i = 0; i < 5000; i++)
    {
        bankAccount += 15;
    }
}

void withdraw()
{
    const std::lock_guard<std::mutex>lock(mutex);

    for (int i = 0; i < 5000; i++)
    {
        bankAccount -= 15;
    }
}

int main()
{


    std::thread first(deposit);
    std::thread second(withdraw);

    first.join();
    second.join();

    std::cout << bankAccount;
}
