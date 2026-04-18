#include <iostream>
#include <fstream>
#include <string>

void readFile(const std::string& filename) {
    std::ifstream infile(filename);
    if (!infile.is_open()) {
        std::cerr << "Error opening file: " << filename << std::endl;
        return;
    }
    std::cout << "Contents of the file:" << std::endl;
    std::string line;
    while (std::getline(infile, line)) {
        std::cout << line << std::endl;
    }
    std::cout << "End of file reached." << std::endl;
    infile.close();
}

void appendFile(const std::string& filename, const std::string& content) {
    std::ofstream outfile(filename, std::ios::app);
    if (!outfile.is_open()) {
        std::cerr << "Error opening file: " << filename << std::endl;
        return;
    }
    outfile << content << std::endl;
    std::cout << "Content appended to the file." << std::endl;
    outfile.close();
}

int main() {
    std::string filename = "test.txt";
    appendFile(filename, "This is a new line of text.");
    readFile(filename);
    appendFile(filename, "This is another line of text.");
    readFile(filename);
    return 0;
}