// A simple program that computes the square root of a number
#include <iostream>
#include <string>

#include "Config.h"
#include "Base64Codec.h"
#include "Authentication.h"
#include "CLI.h"

void base64CodecTesting(){
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

    return;
}

int main(int argc, char *argv[]) {
    if (argc < 2) {        // report version
        std::cout << argv[0] << " Version " << POP3_VERSION_MAJOR << "."
                  << POP3_VERSION_MINOR << std::endl;
        std::cout << "Usage: " << argv[0] << " number" << std::endl;
        return 1;
    }

    // Enter cli application
    mainEntry();

    std::cout << "[INFO] Goodbye!" << std::endl;

    return 0;
}

