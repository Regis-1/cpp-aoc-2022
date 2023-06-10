#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <unordered_map>
#include <algorithm>
#include <numeric>

std::vector<std::string> load_file(const char* path) {
    std::vector<std::string> data;

    std::ifstream fh(path);

    std::string line; 
    while (std::getline(fh, line))
        data.push_back(line);

    fh.close();
    return data;
}

char get_unique_mutual_char(std::string& str1, std::string& str2) {
    std::unordered_map<char, int> char_frequency1;
    std::unordered_map<char, int> char_frequency2;

    for (char c : str1)
        char_frequency1[c] += 1;

    for (char c : str2)
        char_frequency2[c] += 1;

    // find the unique mutual character 
    for (char c : str1)
        if (char_frequency1[c] > 0)
            if (char_frequency2[c] > 0)
                return c;

    return '\0';
}

int get_char_code(char c) {
    int ascii_code = int(c);
    if (ascii_code >= 97 && ascii_code <= 122)
        return ascii_code - (97 - 1);
    else
        return ascii_code - (65 - 27);
}

int main(int argc, char** argv) {
    if (argc != 2) {
        std::cout << "Usage ./prog_1 <filename>" << std::endl;
        return 1;
    }

    std::vector<std::string> data = load_file(argv[1]);
    std::vector<char> unique_chars;

    for (auto l : data) {
        auto middle = l.begin() + l.length() / 2;
        std::string first_half{l.begin(), middle};
        std::string second_half{middle, l.end()};

        unique_chars.push_back(get_unique_mutual_char(first_half, second_half));
    }

    std::vector<int> encoded_chars;
    std::transform(unique_chars.begin(), unique_chars.end(),
            std::back_inserter(encoded_chars), get_char_code);

    int total = std::accumulate(encoded_chars.begin(), encoded_chars.end(), 0);
    std::cout << "Total: " << total << std::endl;

    return 0;
}
