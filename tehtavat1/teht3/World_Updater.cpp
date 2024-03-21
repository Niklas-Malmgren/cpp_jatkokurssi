#include "World_Updater.h"

void World_Updater::perform()
{
	int x = 0;
    for (int i = 0; i < 2000000000; i++)
    {
        x++;
    }
	std::cout << "Update\n";
}