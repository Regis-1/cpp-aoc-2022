#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <utility>

std::vector<std::string> load_file(const char* path) {
    std::vector<std::string> data;

    std::ifstream fh(path);

    std::string line; 
    while (std::getline(fh, line))
        data.push_back(line);

    fh.close();
    return data;
}

struct SectionRange {
    int begin_;
    int end_;

    SectionRange() = delete;
    SectionRange(int begin, int end) : begin_(begin), end_(end) {}
    SectionRange(std::pair<int, int> pair) : begin_(pair.first), end_(pair.second) {}

    bool fully_contains(const SectionRange& other) {
        return (other.begin_ >= begin_) && (other.end_ <= end_);
    }
};

std::pair<int, int> extract_range(std::string text_range) {
    std::string delimiter = "-";
    int delim_loc = text_range.find(delimiter);

    std::string beg = text_range.substr(0, delim_loc);
    std::string end = text_range.substr(delim_loc + 1, text_range.length());

    return std::make_pair(std::stoi(beg), std::stoi(end));
}

int main(int argc, char** argv) {
    if (argc != 2) {
        std::cout << "Usage ./prog_1 <filename>" << std::endl;
        return 1;
    }

    std::vector<std::string> data = load_file(argv[1]);
    int contained_counter = 0;

    std::string delimiter = ",";
    for (auto p : data) {
        int delim_loc = p.find(delimiter);
        std::string first_pair = p.substr(0, delim_loc);
        std::string second_pair = p.substr(delim_loc + 1, p.length());

        SectionRange rng1{extract_range(first_pair)};
        SectionRange rng2{extract_range(second_pair)};

        if (rng1.fully_contains(rng2) || rng2.fully_contains(rng1))
            contained_counter++;
    }

    std::cout << "Number of pairs with fully containment: "
              << contained_counter << std::endl;

    return 0;
}
