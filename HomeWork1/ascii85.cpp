#include <iostream>
#include <vector>
#include <string>
#include <stdexcept>
#include <algorithm>
#include <cmath>

std::string encodeAscii85(const std::vector<unsigned char>& data) {
    std::string result;
    size_t i = 0;
    
    while (i < data.size()) {
        uint32_t value = 0;
        int bytes = 0;
        
        for (; bytes < 4 && i + bytes < data.size(); bytes++) {
            value = (value << 8) | data[i + bytes];
        }
        
        i += bytes;
        
        if (bytes == 4 && value == 0) {
            result += 'z';
            continue;
        }
        
        char chars[5];
        for (int j = 4; j >= 0; j--) {
            chars[j] = (value % 85) + '!';
            value /= 85;
        }
        
        for (int j = 0; j < bytes + 1; j++) {
            result += chars[j];
        }
    }
    
    return result;
}

std::vector<unsigned char> decodeAscii85(const std::string& input) {
    std::vector<unsigned char> result;
    size_t i = 0;
    
    while (i < input.size()) {
        if (isspace(input[i])) {
            i++;
            continue;
        }
        
        if (input[i] == 'z') {
            for (int j = 0; j < 4; j++) {
                result.push_back(0);
            }
            i++;
            continue;
        }
        
        uint32_t value = 0;
        int chars = 0;
        
        for (; chars < 5 && i + chars < input.size(); chars++) {
            char c = input[i + chars];
            
            if (c < '!' || c > 'u') {
                throw std::runtime_error("Invalid ASCII85 character");
            }
            
            value = value * 85 + (c - '!');
        }
        
        i += chars;
        
        if (chars < 5) {
            value *= pow(85, 5 - chars);
        }
        
        for (int j = 3; j >= 0; j--) {
            if (j < chars - 1) {
                result.push_back((value >> (8 * j)) & 0xFF);
            }
        }
    }
    
    return result;
}