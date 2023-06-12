#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <unordered_map>

std::vector<std::string> load_file(const char* path) {
    std::vector<std::string> data;

    std::ifstream fh(path);

    std::string line; 
    while (std::getline(fh, line))
        data.push_back(line);

    fh.close();
    return data;
}

int find_start_of_packet(std::string signal) {
    std::unordered_map<char, int> frequency;
    const int buffer_size = 4;
    int unique_counter = 0;
    std::string::iterator last_char = signal.begin();

    // initial freq populating
    for (auto c = signal.begin(); c != signal.begin() + buffer_size; c++)
        frequency[*c] += 1;

    for (auto c = signal.begin() + buffer_size; c != signal.end(); c++) {
        unique_counter = 0;

        // scanning frequency to find all unique characters
        for (auto um = frequency.begin(); um != frequency.end(); um++)
            if (um->second == 1)
                unique_counter++;

        // check if whole buffer is unique
        if (unique_counter == buffer_size)
            return std::distance(signal.begin(), c);

        frequency[*last_char] -= 1;
        last_char++;
        frequency[*c] += 1;
    }
    
    return 0;
}

int main(int argc, char** argv) {
    if (argc != 2) {
        std::cout << "Usage ./prog_1 <filename>" << std::endl;
        return 1;
    }

    std::vector<std::string> data = load_file(argv[1]);

    int start_of_packet = find_start_of_packet(data[0]);

    std::cout << "The marker index: " << start_of_packet << std::endl;
    
    return 0;
}
