#include <iostream>
#include <fstream>
#include <vector>
#include <numeric>
#include <algorithm>

int main(int argc, char** argv) {
    if (argc != 2) {
        std::cout << "Usage: ./prog_2 <filename>" << std::endl;
        return 1;
    }

    std::ifstream fh(argv[1]);

    if (!fh) {
        std::cout << "Invald file given." << std::endl;
        return 1;
    }

    std::string line;
    std::vector<int> calories;
    std::vector<int> elves_sum;

    while (std::getline(fh, line)) {
        if (line != "")
            calories.push_back(atoi(line.c_str()));
        else {
            elves_sum.push_back(std::accumulate(calories.begin(), calories.end(), 0));
            calories.clear();
        }
    }
    elves_sum.push_back(std::accumulate(calories.begin(), calories.end(), 0));
    std::sort(elves_sum.begin(), elves_sum.end());

    std::cout << std::accumulate(elves_sum.end() - 3, elves_sum.end(), 0) << std::endl;

    fh.close();

    return 0;
}
