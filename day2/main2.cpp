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

enum Outcome {
    Lose,
    Draw,
    Win
};

int result(Outcome& outcome, Move&& other) {
    int result_;

    switch (outcome) {
        case Outcome::Lose:
            result_ = static_cast<int>((other + 2) % 3) + 1;
            break;
        case Outcome::Draw:
            result_ = static_cast<int>(other) + 1 + 3;
            break;
        case Outcome::Win:
            result_ = static_cast<int>((other + 1) % 3) + 1 + 6;
            break;
    }
    std::cout << result_ << std::endl;

    return result_;
}

int main(int argc, char** argv) {
    if (argc != 2) {
        std::cout << "Usage ./prog_2 <filename>" << std::endl;
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
        Outcome outcome = static_cast<Outcome>(int(line[2] % ASCII_X));

        scores.push_back(result(outcome, static_cast<Move>(int(line[0]) % ASCII_A)));
    }

    fh.close();

    int total_result = std::accumulate(scores.begin(), scores.end(), 0);
    std::cout << total_result << std::endl;

    return 0;
}
