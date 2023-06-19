#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>
#include <numeric>
#include <unordered_map>

struct Instruction {
    bool modify_reg_;
    int value_;
    int cycle_duration_;

    Instruction(int cycle_duration, int val)
        : modify_reg_(true), value_(val), cycle_duration_(cycle_duration) {}

    Instruction(int cycle_duration)
        : modify_reg_(false), value_(0), cycle_duration_(cycle_duration) {}
};

bool in_range(int low, int high, int val) {
    return ((unsigned int)(val-low) <= (high-low));
}

class DeviceVideoSystem {
private:
    int cycle_{1};
    int reg_value_{1};
    std::unordered_map<int, int> sig_timeline_;

    void execute_instruction(const Instruction& inst) {
        cycle_ += inst.cycle_duration_;

        if (inst.modify_reg_)
            reg_value_ += inst.value_;
            
        sig_timeline_[cycle_] = reg_value_;
    }

public:
    int measure_start_{20};
    int measures_offset_{40};

    std::vector<int> exec_inst_with_signal_measures(const std::vector<Instruction>& insts,
            int num_of_measures) {

        std::vector<int> measures;

        for (auto i : insts)
            execute_instruction(i);

        for (int i = 0; i <= measure_start_ + measures_offset_ * (num_of_measures - 1); i++) {
            for (int j = 0; j < num_of_measures; j++)
                if (i == measure_start_ + measures_offset_ * j) {
                    int measured_value = sig_timeline_[i];
                    if (measured_value == 0)
                        measures.push_back(sig_timeline_[i-1] * i);
                    else
                        measures.push_back(measured_value * i);
                }
        }

        return measures;
    }
};

std::vector<Instruction> parse_input(const std::vector<std::string>& input) {
    std::vector<Instruction> instructions;

    for (auto line : input) {
        std::istringstream iss;
        iss.str(line);
        std::string token;
        std::vector<std::string> separated;
        while (std::getline(iss, token, ' '))
            separated.push_back(token);

        if (separated[0] == "noop")
            instructions.push_back({1});
        else if (separated[0] == "addx")
            instructions.push_back({2, std::stoi(separated[1])});
    }

    return instructions;
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

    std::vector<Instruction> instructions = parse_input(data);
    DeviceVideoSystem vid_sys;
    std::vector<int> measures = vid_sys.exec_inst_with_signal_measures(instructions, 6);

    std::cout << "The sum of those six signals equals: "
        << std::accumulate(measures.begin(), measures.end(), 0) << std::endl;
    
    return 0;
}
