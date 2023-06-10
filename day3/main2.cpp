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

char get_group_badge(std::vector<std::string>::iterator group_begin,
        std::vector<std::string>::iterator group_end) {

    if (std::distance(group_begin, group_end) != 3)
        return '\0';

    std::unordered_map<char, int> char_frequency[3];

    int cnt = 0;
    for (auto elf = group_begin; elf != group_end; elf++) {
        for (char c : *elf)
            char_frequency[cnt][c] += 1;

        cnt++;
    }
    
    // find the unique mutual character 
    for (char c : *group_begin)
        if (char_frequency[0][c] > 0 && char_frequency[1][c] > 0 && char_frequency[2][c] > 0)
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

    for (auto g = data.begin(); g != data.end(); g += 3)
        unique_chars.push_back(get_group_badge(g, g+3));

    std::vector<int> encoded_chars;
    std::transform(unique_chars.begin(), unique_chars.end(),
            std::back_inserter(encoded_chars), get_char_code);

    int total = std::accumulate(encoded_chars.begin(), encoded_chars.end(), 0);
    std::cout << "Total: " << total << std::endl;

    return 0;
}
