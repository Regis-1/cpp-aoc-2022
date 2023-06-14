#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <cmath>
#include <utility>
#include <numeric>

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

void check_if_visible(int idr, int idc, const t_forest& f, t_forest& vm) {
    int dim = f.size() - 1;
    std::pair<int, int> dirs[4] = {{-1, 0}, {0, 1}, {1, 0}, {0, -1}};
    int tree_height = f[idr][idc];

    for (auto d : dirs) {
        int r = idr;
        int c = idc;
        
        while (r != 0 && r != dim && c != 0 && c != dim) {
            r += d.first;
            c += d.second;

            if (tree_height <= f[r][c]) {
                vm[idr][idc] = 0;
                break;
            }
            else
                vm[idr][idc] = 1;
        }

        // if is visible from at least one direction end loop
        if (vm[idr][idc] == 1 )
            break;
    }
}

void update_vmat_by_direction(const t_forest& forest, t_forest& vmat) {
    int forest_dim = forest.size() - 1;

    for (int i = 1; i < forest_dim; i++)
        for (int j = 1; j < forest_dim; j++) {
            check_if_visible(i, j, forest, vmat);
        }
}

t_forest get_visibility_matrix(const t_forest& forest) {
    t_forest vmat;

    // initialize visibility matrix with 0s
    for (auto row = forest.begin(); row != forest.end(); row++) {
        int idx = std::distance(forest.begin(), row);
        vmat.push_back(std::vector<int>());
        for (auto tree : *row)
            vmat[idx].push_back(1);
    }

    update_vmat_by_direction(forest, vmat);

    return vmat;
}

int count_visible_trees(const t_forest& forest) {
    t_forest visibility_matrix = get_visibility_matrix(forest);
    int total_visible = 0;

    for (auto row : visibility_matrix)
        total_visible += std::accumulate(row.begin(), row.end(), 0);

    return total_visible;
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

    std::cout << "Total visible trees: " << visible_trees_num << std::endl;
    
    return 0;
}
