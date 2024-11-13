#include "cipher.h"

#include <iostream>

using namespace std;

static string upper_case_letter_to_number(char _letter) {
  if (_letter == 'J') {
    return "100";
  } else {
    for (int i = 0; i < 5; i++) {
      for (int j = 0; j < 5; j++) {
        if (_letter == uppercaseSquare[i][j]) {
          return "1" + to_string(i + 1) + to_string(j + 1);
        }
      }
    }
  }
  return "Letter not found!";
}

static string lower_case_letter_to_number(char _letter) {
  if (_letter == 'j') {
    return "200";
  } else {
    for (int i = 0; i < 5; i++) {
      for (int j = 0; j < 5; j++) {
        if (_letter == lowercaseSquare[i][j]) {
          return "2" + to_string(i + 1) + to_string(j + 1);
        }
      }
    }
  }
  return "Letter not found!";
}

static char number_to_letter(string num) {
  if (num == "100") {
    return 'J';
  } else if (num == "200") {
    return 'j';
  } else if (num[0] == '1') {
    return uppercaseSquare[num[1] - '0' - 1][num[2] - '0' - 1];
  } else if (num[0] == '2') {
    return lowercaseSquare[num[1] - '0' - 1][num[2] - '0' - 1];
  }
  return '\0';
}

static string encode_per_letter(char _input) {
  if (_input == ' ') {
    return "000";
  } else if ('a' <= _input && _input <= 'z') {
    return lower_case_letter_to_number(_input);
  } else {
    return upper_case_letter_to_number(_input);
  }
}

static char decode_per_number(string _input) {
  if (_input == "000") {
    return ' ';
  } else {
    return number_to_letter(_input);
  }
}

void encode_compact(string input_sentence) {
  for (std::string::size_type i = 0; i < input_sentence.length(); i++) {
    cout << encode_per_letter(input_sentence[i]);
  }
  cout << endl;
}

void print_error(int _argc, char* _argv[]) {
  // check number of arguments first
  if (_argc >= 4) {
    cout << "Too many options!" << endl;
  }
  string first_option = _argv[1];
  // if first argument "-h", then no more argument
  if (first_option == "-h" && _argc > 2) {
    cout << "Too many options!" << endl;
  }
  // else, check whether valid
  if (!(first_option == "-d" || first_option == "-e" || first_option == "-h" ||
        first_option == "--encrypt" || first_option == "--decrypt" ||
        first_option == "--help")) {
    cout << "Invalid option!" << endl;
  }
  // check second argument
  if (_argc == 3) {
    string second_option = _argv[2];
    if (second_option != "" &&
        (second_option != "-c" && second_option != "-s" &&
         second_option != "--compact" && second_option != "--sparse")) {
      cout << "Invalid option!" << endl;
    }
  }
}

void encode_sparse(std::string input_sentence) {
  for (std::string::size_type i = 0; i < input_sentence.length(); i++) {
    cout << encode_per_letter(input_sentence[i]);
    if (i < input_sentence.length() - 1) {
      cout << " ";
    }
  }
  cout << endl;
}

void decode_compact(std::string input_sentence) {
  for (std::string::size_type i = 0; i < input_sentence.length(); i = i + 3) {
    cout << decode_per_number(input_sentence.substr(i, 3));
  }
  cout << endl;
}

void decode_sparse(std::string input_sentence) {
  for (std::string::size_type i = 0; i < input_sentence.length(); i = i + 4) {
    cout << decode_per_number(input_sentence.substr(i, 3));
  }
  cout << endl;
}

void printHelp() {
  cout << "Encrypt or decrypt a message using the Polybius Square cipher.\n"
       << "Usage: ./ex3 <command> [outputMode]\n"
       << "Commands:\n"
       << "\t-e, --encrypt\tEncrypt a message\n"
       << "\t-d, --decrypt\tDecrypt a message\n"
       << "Output modes:\n"
       << "\t-c, --compact\tProcess the message without spaces\n"
       << "\t-s, --sparse\tProcess the message with spaces" << endl;
}

// Implement other functions here
