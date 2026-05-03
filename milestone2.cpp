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

void rotFile(const std::string& inputFile, const std::string& outputFile, int rotAmount, bool encode) {
    std::string content = readFile(inputFile);
    std::string result = caesarCipher(content, rotAmount, encode);
    writeFile(outputFile, result);
    if (encode) {
        std::cout << "ROT" << rotAmount << "File encrypted successfully!" << outputFile << std::endl;
    } else {
        std::cout << "ROT" << rotAmount << "File decrypted successfully!" << outputFile << std::endl;
    }
}


int main(){
    writeFile("input.txt", "Hello world! Dont share this super secret message with anyone");
    
    std::cout << "Original file content:" << std::endl;
    std::cout << readFile("input.txt") << std::endl;
    
    //ecrypt the file w/ key of 3
    fileCaesarCipher("input.txt", "encrypted.txt", 3, true);
    std::cout << "Encrypted file content:" << std::endl;
    std::cout << readFile("encrypted.txt") << std::endl;

    //decrypt the file w/ key of 3
    fileCaesarCipher("encrypted.txt", "decrypted.txt", 3, false); 
    std::cout << "Decrypted file content:" << std::endl;
    std::cout << readFile("decrypted.txt") << std::endl;

    // test ROT13
    rotFile("input.txt", "rot13_encoded.txt", 13, true);
    std::cout << "ROT13 Encoded:" << std::endl;
    std::cout << readFile("rot13_encoded.txt") << std::endl;

    rotFile("rot13_encoded.txt", "rot13_decoded.txt", 13, false);
    std::cout << "ROT13 Decoded:" << std::endl;
    std::cout << readFile("rot13_decoded.txt") << std::endl;
    return 0;
}