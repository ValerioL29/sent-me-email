// A simple program that computes the square root of a number
#include <iostream>
#include <string>

#include "Config.h"
#include "MathFunctions.h"

int main(int argc, char *argv[]) {
    if (argc < 2) {        // report version
        std::cout << argv[0] << " Version " << POP3_VERSION_MAJOR << "."
                  << POP3_VERSION_MINOR << std::endl;
        std::cout << "Usage: " << argv[0] << " number" << std::endl;
        return 1;
    }

    // convert input to double
    const double inputValue = std::stod(argv[1]);

    // calculate square root
    const double outputValue = mysqrt(inputValue);
    std::cout << "The square root of " << inputValue << " is " << outputValue
              << std::endl;
    return 0;
}

