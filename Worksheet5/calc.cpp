#include <iostream>
#include <cstdlib>
#include "adder.h"

int main(int argc, char* argv[])
{
    if (argc != 3) {
        std::cout << "Usage: calcdynamic <a> <b>\n";
        return 1;
    }

    int a = std::atoi(argv[1]);
    int b = std::atoi(argv[2]);

    std::cout << add(a, b) << std::endl;
    return 0;
}
