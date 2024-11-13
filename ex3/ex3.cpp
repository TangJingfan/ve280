#include <iostream>

#include "cipher.h"

int main(int argc, char* argv[]) {
  print_error(argc, argv);
  std::string first_option = argv[1];

  if (first_option == "-h" || first_option == "--help") {
    printHelp();
  }

  if (first_option == "-e" || first_option == "--encrypt") {
    std::string input_sentence;
    getline(std::cin, input_sentence);
    if (argc == 3) {
      std::string second_option = argv[2];
      if (second_option == "-c" || second_option == "--compact") {
        encode_compact(input_sentence);
      } else {
        encode_sparse(input_sentence);
      }
    } else {
      encode_compact(input_sentence);
    }
  } else if (first_option == "-d" || first_option == "--decrypt") {
    std::string input_sentence;
    getline(std::cin, input_sentence);
    if (argc == 3) {
      std::string second_option = argv[2];
      if (second_option == "-c" || second_option == "--compact") {
        decode_compact(input_sentence);
      } else {
        decode_sparse(input_sentence);
      }
    } else {
      decode_compact(input_sentence);
    }
  }
}