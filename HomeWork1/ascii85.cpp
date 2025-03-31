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