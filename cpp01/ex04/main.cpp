// ./main.cpp
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

static std::string replaceAll(const std::string &content,
                              const std::string &s1,
                              const std::string &s2) {
    std::string result;
    size_t pos = 0;
    size_t found;

    while ((found = content.find(s1, pos)) != std::string::npos) {
        result.append(content, pos, found - pos);
        result.append(s2);
        pos = found + s1.length();
    }
    result.append(content, pos, std::string::npos);
    return result;
}

int main(int argc, char **argv) {
    if (argc != 4) {
        std::cerr << "Usage: " << (argc > 0 ? argv[0] : "./ex04")
                  << " <filename> <s1> <s2>" << std::endl;
        return 1;
    }

    std::string filename = argv[1];
    std::string s1 = argv[2];
    std::string s2 = argv[3];

    if (s1.empty()) {
        std::cerr << "Error: s1 must not be empty" << std::endl;
        return 1;
    }

    std::ifstream input(filename.c_str());
    if (!input.is_open()) {
        std::cerr << "Error: could not open file '" << filename << "'" << std::endl;
        return 1;
    }

    std::stringstream buffer;
    buffer << input.rdbuf();
    input.close();

    std::string content = buffer.str();
    std::string replaced = replaceAll(content, s1, s2);

    std::string outName = filename + ".replace";
    std::ofstream output(outName.c_str());
    if (!output.is_open()) {
        std::cerr << "Error: could not create file '" << outName << "'" << std::endl;
        return 1;
    }

    output << replaced;
    output.close();

    return 0;
}
