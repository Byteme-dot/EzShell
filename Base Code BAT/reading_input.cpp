#include "reading_input.h"
#include <iostream>
#include <sstream>

std::vector<std::string> read_input() {
    std::string text;

    if (!std::getline(std::cin, text)) {
        return {};
    }

    std::istringstream iss(text);
    std::vector<std::string> words;
    std::string word;

    while (iss >> word) {
        words.push_back(word);
    }

    return words;
}