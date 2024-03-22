#include <iostream>
#include <iomanip>
#include <string>
#include <vector>
#include <sstream>

int RaDecConvertor(std::string string){
    std::vector<std::string> new_string;

    std::stringstream ss(string);
    std::string token;
    while (getline(ss, token, ' ')) {
        new_string.push_back(token);
    }

    std::string string_1 = new_string[0];
    std::vector<std::string> new_string_1;
    std::stringstream ss1(string_1);
    std::string token1;
    while (getline(ss1, token1, ':')) {
        new_string_1.push_back(token1);
    }

    std::string string_2 = new_string[1];
    std::vector<std::string> new_string_2;
    std::stringstream ss2(string_2);
    std::string token2;
    while (getline(ss2, token2, ':')) {
        new_string_2.push_back(token2);
    }
    
    std::cout << "RADEC " << new_string_1[1] << "," << new_string_2[1];


    return 0;
}

int main() {
    RaDecConvertor("ra:0.120194 dec:-60.070832");
}