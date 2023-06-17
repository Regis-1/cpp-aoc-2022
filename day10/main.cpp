#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>

struct Instruction {
    bool modify_reg_;
    int value_;
    int cycle_duration_;

    Instruction(int cycle_duration, int val)
        : modify_reg_(true), value_(val), cycle_duration_(cycle_duration) {}

    Instruction(int cycle_duration)
        : modify_reg_(false), value_(0), cycle_duration_(cycle_duration) {}
};

class DeviceVideoSystem {
private:
    int cycle_{0};
    int reg_value_{1};

    void execute_instruction(const Instruction& inst) {
    }

public:
    void execute_instructions(const std::vector<Instruction>& insts) {
        for (auto inst : insts)
            execute_instruction(inst);
    }

    std::vector<int> exec_inst_with_signal_measures(const std::vector<Instruction>& insts,
            int num_of_measures) {

        std::vector<int> measures;

        // TODO

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
    vid_sys.exec_inst_with_signal_measures(instructions, 6);
    
    return 0;
}
