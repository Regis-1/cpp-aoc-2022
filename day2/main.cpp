#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <numeric>

const unsigned int ASCII_X = 88;
const unsigned int ASCII_A = 65;

enum Move {
    Rock,
    Paper,
    Scissors
};

struct Play {
    int result(Play& other) {
        int dif = m_ - other.m_;
        if (dif == 0)
            return static_cast<int>(m_) + 1 + 3;
        else if (dif == -1 || dif == 2)
            return static_cast<int>(m_) + 1;
        else
            return static_cast<int>(m_) + 1 + 6;
    }

    Play(char c) 
        : m_(static_cast<Move>(int(c) % ASCII_X % ASCII_A)) {}

    Move m_;
};

int main(int argc, char** argv) {
    if (argc != 2) {
        std::cout << "Usage ./prog_1 <filename>" << std::endl;
        return 1;
    }

    std::ifstream fh(argv[1]);
    if (!fh) {
        std::cout << "Invalid file!" << std::endl;
        return 1;
    }

    std::string line;
    std::vector<int> scores;
    while (std::getline(fh, line)) {
        Play opponent(line[0]);
        Play response(line[2]);

        scores.push_back(response.result(opponent));
    }

    fh.close();

    int total_result = std::accumulate(scores.begin(), scores.end(), 0);
    std::cout << total_result << std::endl;

    return 0;
}
