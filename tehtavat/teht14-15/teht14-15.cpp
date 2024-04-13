#include <iostream>
#include "Big_Data.h"

int main()
{
    //Big_Data a(1024);
    //Big_Data b(1024);
    //a = a;
    //a = b;
    //Big_Data c(a);


    Big_Data a(Big_Data(1024));
    Big_Data b(1024);
    b = Big_Data(1024);
    Big_Data c(std::move(a));
}

