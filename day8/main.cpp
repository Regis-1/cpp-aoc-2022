#include <iostream>
#include <fstream>
#include <vector>
#include <string>

typedef std::vector<std::vector<int>> t_forest;

struct Direction {
    std::vector<int> north{-1, 0};
    std::vector<int> east{0, 1};
    std::vector<int> south{1, 0};
    std::vector<int> norith{0, -1};
};

Direction dirs;

t_forest parse_input_to_forest(std::vector<std::string>& input) {
    t_forest forest;

    for (auto line = input.begin(); line != input.end(); line++) {
        int idx = std::distance(input.begin(), line);
        forest.push_back(std::vector<int>());

        for (auto c : *line)
            forest[idx].push_back(atoi(&c));
    }

    return forest;
}

void update_vmat_by_direction(const t_forest& f, t_forest& vm, std::vector<int> d) {
    int r = d[0];
    int c = d[1];

    bool v_search = c != 0 ? true : false;

    for (int i = 0; i < forest.size(); i++) {
        int last_tree = -1;
    }
}

t_forest get_visibility_matrix(const t_forest& forest) {
    t_forest vmat;

    // initialize visibility matrix with 0s
    for (auto row = forest.begin(); row != forest.end(); row++) {
        int idx = std::distance(forest.begin(), row);
        vmat.push_back(std::vector<int>());
        for (auto tree : *row)
            vmat[idx].push_back(0);
    }

    update_vmat_by_direction(forest, vmat, dirs.south);

    return vmat;
}

int count_visible_trees(const t_forest& forest) {
    t_forest visibility_matrix = get_visibility_matrix(forest);

    return 0;
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

    t_forest forest = parse_input_to_forest(data);

    int visible_trees_num = count_visible_trees(forest);
    
    return 0;
}
