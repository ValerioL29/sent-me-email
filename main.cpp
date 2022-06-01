// A simple program that computes the square root of a number
#include <iostream>
#include <string>

#include "Config.h"
#include "MathFunctions.h"
#include "Base64Codec.h"

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

    // Codec testings

    bool all_tests_passed = true;
    
    std::string rest0_original = "abc";
    std::string rest0_reference = "YWJj";

    std::string rest0_encoded = base64_encode(reinterpret_cast<const unsigned char*>(rest0_original.c_str()),
      rest0_original.length());
    std::string rest0_decoded = base64_decode(rest0_encoded);

    if (rest0_decoded != rest0_original) {
      std::cout << "rest0_decoded != rest0_original" << std::endl;
      all_tests_passed = false;
    }
    if (rest0_reference != rest0_encoded) {
      std::cout << "rest0_reference != rest0_encoded" << std::endl;
      all_tests_passed = false;
    }

    std::cout << "encoded:   " << rest0_encoded << std::endl;
    std::cout << "reference: " << rest0_reference << std::endl;
    std::cout << "decoded:   " << rest0_decoded << std::endl << std::endl;

    return 0;
}

