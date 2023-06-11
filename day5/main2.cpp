#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>
#include <algorithm>

typedef std::vector<std::vector<char>> t_stockpile;

struct Instruction {
    int quantity;
    int source;
    int destiny;
};

std::vector<std::string> load_file(const char* path) {
    std::vector<std::string> data;

    std::ifstream fh(path);

    std::string line; 
    while (std::getline(fh, line))
        data.push_back(line);

    fh.close();
    return data;
}

t_stockpile set_up_crates(std::vector<std::string>::iterator beg,
        std::vector<std::string>::iterator end) {

    t_stockpile crates;
    int offset = 1;
    int stride = 4;
    unsigned int len = (*beg).length();

    for (int i = offset; i < len; i += stride) {
        crates.push_back(std::vector<char>());
        for (auto l = beg; l != end; l++)
            if ((*l)[i] != ' ')
                crates[(i-1) / stride].push_back((*l)[i]);
        auto b = crates[(i-1) / stride].begin();
        auto e = crates[(i-1) / stride].end();
        std::reverse(b, e);
    }

    return crates;
}

Instruction parse_instruction(const std::string& text_inst) {
    const std::string delimiter = " ";

    size_t pos = 0;
    std::vector<int> num_vals;
    std::istringstream iss_inst;
    iss_inst.str(text_inst);
    for (std::string token; std::getline(iss_inst, token, ' '); )
        try {
            num_vals.push_back(std::stoi(token));
        }
        catch(const std::exception& e) {}

    // return Instruction with adjusted source & destiny indexes
    return Instruction{num_vals[0], num_vals[1] - 1, num_vals[2] - 1};
}

void execute_instruction(const Instruction& inst, t_stockpile& crates) {
    crates[inst.destiny].insert(crates[inst.destiny].end(),
            crates[inst.source].end() - inst.quantity, crates[inst.source].end());

    for (int i = 0; i < inst.quantity; i++)
        crates[inst.source].pop_back();
}

void process_crane_steps(std::vector<std::string>::iterator begin,
        std::vector<std::string>::iterator end, t_stockpile& crates) {

    for (auto line = begin; line != end; line++) {
        Instruction instruction = parse_instruction(*line);
        execute_instruction(instruction, crates);
    }
}

int main(int argc, char** argv) {
    if (argc != 2) {
        std::cout << "Usage ./prog_1 <filename>" << std::endl;
        return 1;
    }

    std::vector<std::string> data = load_file(argv[1]);

    unsigned int sep_line_loc;
    for (int i = 0; i < data.size(); i++)
        if (data[i] == "") {
            sep_line_loc = i;
            break;
        }

    t_stockpile crates = set_up_crates(data.begin(), data.begin() + sep_line_loc - 1);
    process_crane_steps(data.begin() + sep_line_loc + 1, data.end(), crates);

    for (auto pile : crates)
        std::cout << pile.back() << " ";

    std::cout << std::endl;

    return 0;
}
