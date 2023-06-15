#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <utility>
#include <set>

struct Move {
    std::pair<int, int> direction_;
    int amount_;
};

struct Head {
    int x_;
    int y_;

    Head() : x_(0), y_(0) {}

    void move(const Move& m) {
        x_ += m.direction_.first;
        y_ += m.direction_.second;
    }
};

struct Tail {
    int x_;
    int y_;

    std::set<std::pair<int, int>> visited_cells_;

    Tail() : x_(0), y_(0) {}

    void move(const Head& h) {
        int dif_x = h.x_ - x_;
        int dif_y = h.y_ - y_;

        // check if the tail should move
        if (dif_x <= -2 || dif_x >= 2 || dif_y <= -2 || dif_y >= 2) {
            // TODO
        }
    }
};

std::vector<Move> parse_input(std::vector<std::string> input) {
    std::vector<Move> move_list;

    for (auto line : input) {
        Move move;
        switch(line[0]) {
            case 'R':
                move.direction_ = {1, 0};
                break;
            case 'L':
                move.direction_ = {-1, 0};
                break;
            case 'U':
                move.direction_ = {0, 1};
                break;
            case 'D':
                move.direction_ = {0, -1};
                break;
        }

        move.amount_ = std::stoi(line.substr(2));
        move_list.push_back(move);
    }

    return move_list;
}

int process_moves(const std::vector<Move>& move_list) {
    Head h;
    Tail t;

    for (auto m : move_list) {
        h.move(m);
        t.move(h);
    }

    return t.visited_cells_.size();
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
    
    return 0;
}
