#include <iostream>
#include <fstream>
#include <string>
#include <cctype>

std::string readFile(const std::string& filename) {
    std::ifstream input(filename);
 
    if (!input.is_open()) {
        std::cout << "Error: Could not open file." << std::endl;
        return "";
    }
 
    std::string content;
    std::string line;
    while (std::getline(input, line)) {
        content += line + "\n";
    }
 
    input.close();
    return content;
}

void writeFile(const std::string& filename, const std::string& content) {
    std::ofstream output(filename);
 
    if (!output.is_open()) {
        std::cout << "Error: Could not open file for writing." << std::endl;
        return;
    }
 
    output << content << std::endl;
    output.close();
}

char shift(char c, int s){
    char base;
    if (std::isalpha(c)) {
        if(std::isupper(c)){
            base='A';
        } else {
            base='a';
        }
        return (c - base + s+26) % 26 + base;
    }
    return c;
}

std::string caesarCipher(const std::string& input, int key, bool encode){
    std::string result;
    for (char c : input) {
        if(encode){
            result += shift(c, key);
        } else {
            result += shift(c, -key);
        }
    }
    return result;
}

void fileCaesarCipher(const std::string& inputFile, const std::string& outputFile, int key, bool encode){
    std::string content = readFile(inputFile);
    std::string result= caesarCipher(content, key, encode);
    writeFile(outputFile, result);

    if(encode){
        std::cout << "File encrypted successfully!" << std::endl;
    } else {
        std::cout << "File decrypted successfully!" << std::endl;
    }
}

int main(){
    writeFile("input.txt", "Hello world! Dont share this super secret message with anyone");
    
    std::cout << "Original file content:" << std::endl;
    std::cout << readFile("input.txt") << std::endl;
    
    fileCaesarCipher("input.txt", "encrypted.txt", 3, true); // Encrypt
    std::cout << "Encrypted file content:" << std::endl;
    std::cout << readFile("encrypted.txt") << std::endl;

    fileCaesarCipher("encrypted.txt", "decrypted.txt", 3, false); // Decrypt
    std::cout << "Decrypted file content:" << std::endl;
    std::cout << readFile("decrypted.txt") << std::endl;
    return 0;
}