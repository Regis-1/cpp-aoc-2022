#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <unordered_map>
#include <sstream>

struct File {
    File* parent_;
    std::unordered_map<std::string, File*> children_;

    int size_;
    bool is_dir_;

    File() = delete;
    File(File* parent, int size, bool is_dir)
        : parent_(parent), size_(size), is_dir_(is_dir) {}
};

void process_ls_cmd(auto& line, auto data_end, std::vector<File*>& fs_stack) {
    line++;

    for (; line != data_end; line++) {
        if ((*line)[0] == '$') {
            line--;
            break;
        }

        std::vector<std::string> tokens;
        std::istringstream iss;
        iss.str(*line);
        for (std::string t; std::getline(iss, t, ' '); )
            tokens.push_back(t);

        int size = 0;
        bool is_dir = true;
        try {
            size = std::stoi(tokens[0]);
            is_dir = false;
        }
        catch (std::exception& e) {}

        File* f = new File{fs_stack.back(), size, is_dir};
        fs_stack.back()->children_[tokens[1]] = f;
    }
}

void process_cd_cmd(std::vector<File*>& fs_stack, std::string path) {
    if (path == "..")
        fs_stack.pop_back();
    else
        fs_stack.push_back(fs_stack.back()->children_[path]);
}

File create_file_structure(std::vector<std::string>& data) {
    File file_str{nullptr};
    std::vector<File*> fs_stack;
    fs_stack.push_back(&file_str);

    // iterating line by line, but skippng the first '$ cd /' - already processed
    for (auto line = data.begin() + 1; line != data.end(); line++ ) {
        std::istringstream iss;
        iss.str(*line);
        std::vector<std::string> tokens;

        if (*line == "")
            break;

        for (std::string t; std::getline(iss, t, ' '); )
            tokens.push_back(t);

        if (tokens[0] == "$")
            if (tokens[1] == "ls")
                process_ls_cmd(line, data.end(), fs_stack);
            else if (tokens[1] == "cd")
                process_cd_cmd(fs_stack, tokens[2]);
    }

    return file_str;
}

void calculate_all_sizes(File& fs) {
    std::vector<File*> fs_stack;
    fs_stack.push_back(&fs);

    // TODO
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

    File files_structure = create_file_structure(data);
    calculate_all_sizes(files_structure);
    
    return 0;
}
