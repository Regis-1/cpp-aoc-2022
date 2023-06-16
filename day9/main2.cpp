#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <utility>
#include <set>

const int NUM_OF_KNOTS = 10;

struct Move {
    std::pair<int, int> direction_;
    int amount_;
};

struct Knot {
    int x_;
    int y_;
    bool is_tail_;

    std::set<std::pair<int, int>> visited_cells_;

    Knot(bool is_tail = false) : x_(0), y_(0), is_tail_(is_tail) {
        if (is_tail_)
            visited_cells_.insert({x_, y_});
    }

    void move(const Move& m) {
        x_ += m.direction_.first;
        y_ += m.direction_.second;
    }

    void move(const Knot& k) {
        int dif_x = k.x_ - x_;
        int dif_y = k.y_ - y_;

        // check if the tail should move
        if (dif_x <= -2 || dif_x >= 2 || dif_y <= -2 || dif_y >= 2) {
            int move_x = dif_x > 0 ? 1 : (dif_x == 0 ? 0 : -1);
            int move_y = dif_y > 0 ? 1 : (dif_y == 0 ? 0 : -1);
            
            x_ += move_x;
            y_ += move_y;

            if (is_tail_)
                visited_cells_.insert({x_, y_});
        }
    }
};

std::vector<Move> parse_input(std::vector<std::string> input) {
    std::vector<Move> move_list;

    for (auto line : input) {
        Move move;
        switch(line[0]) {
            case 'R': // right
                move.direction_ = {1, 0};
                break;
            case 'L': // left
                move.direction_ = {-1, 0};
                break;
            case 'U': // up
                move.direction_ = {0, 1};
                break;
            case 'D': // down
                move.direction_ = {0, -1};
                break;
        }

        move.amount_ = std::stoi(line.substr(2));
        move_list.push_back(move);
    }

    return move_list;
}

int process_moves(const std::vector<Move>& move_list) {
    std::vector<Knot> knots;
    for (int i = 0; i < NUM_OF_KNOTS; i++)
        knots.push_back(i == NUM_OF_KNOTS - 1 ? Knot{true} : Knot{});

    for (auto m : move_list)
        for (int i = 0; i < m.amount_; i++) {
            knots[0].move(m);
            for (auto k = knots.begin() + 1; k != knots.end(); k++) {
                (*k).move(*(k - 1));
            }
        }

    return knots[NUM_OF_KNOTS - 1].visited_cells_.size();
}

std::vector<std::string> load_file(const char* path) {
    std::vector<std::string> data;

    std::ifstream fh(path);

    std::string line; 
    while (std::getline(fh, line))
        data.push_back(line);

    fh.close();
    return data;
}

int main(int argc, char** argv) {
    if (argc != 2) {
        std::cout << "Usage ./prog_1 <filename>" << std::endl;
        return 1;
    }

    std::vector<std::string> data = load_file(argv[1]);

    std::vector<Move> move_list = parse_input(data);

    int tail_unique_cells = process_moves(move_list);
    std::cout << "The tail has visited " << tail_unique_cells << " unique cells."
        << std::endl;
    
    return 0;
}
