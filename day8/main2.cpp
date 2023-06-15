#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <cmath>
#include <utility>
#include <numeric>
#include <functional>
#include <algorithm>

typedef std::vector<std::vector<int>> t_forest;

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

int calculate_score_for_tree(int idr, int idc, const t_forest& f) {
    int dim = f.size() - 1;
    std::pair<int, int> dirs[4] = {{-1, 0}, {0, 1}, {1, 0}, {0, -1}};
    int tree_height = f[idr][idc];

    int tree_scienic_score = 0;
    int dir_idx = 0;
    std::vector<int> dir_scores{0, 0, 0, 0};
    
    for (auto d : dirs) {
        int r = idr;
        int c = idc;
        
        while (r != 0 && r != dim && c != 0 && c != dim) {
            r += d.first;
            c += d.second;

            dir_scores[dir_idx] += 1;
            if (tree_height <= f[r][c])
                break;
        }

        dir_idx++;
    }

    return std::accumulate(dir_scores.begin(), dir_scores.end(), 1, std::multiplies<int>());
}

int get_max_scenic_score(const t_forest& forest) {
    // initialize visibility matrix with 0s
    int forest_dim = forest.size() - 1;
    std::vector<int> scienic_scores;

    for (int i = 1; i < forest_dim; i++)
        for (int j = 1; j < forest_dim; j++) {
            scienic_scores.push_back(calculate_score_for_tree(i, j, forest));
        }

    return *(std::max_element(scienic_scores.begin(), scienic_scores.end()));
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

    int visible_trees_num = get_max_scenic_score(forest);

    std::cout << "Total visible trees: " << visible_trees_num << std::endl;
    
    return 0;
}
