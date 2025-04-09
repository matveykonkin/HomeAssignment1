#include "ascii85.h"
#include <cmath>
#include <cctype>

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
            if (i + 1 < input.size() && !isspace(input[i+1])) {
                throw std::runtime_error("'z' must be followed by whitespace or end of input");
            }
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
            
            if (c == 'z') {
                throw std::runtime_error("'z' can only appear as a complete 4-zero-bytes encoding");
            }
            
            if (c < '!' || c > 'u') {
                throw std::runtime_error("Invalid ASCII85 character");
            }
            
            value = value * 85 + (c - '!');
        }
        
        i += chars;
        
        if (chars < 5) {
            for (int j = chars; j < 5; j++) {
                value = value * 85 + ('u' - '!');
            }
        }
        
        for (int j = 3; j >= 0; j--) {
            if (j < chars - 1 || chars == 5) {
                result.push_back((value >> (8 * j)) & 0xFF);
            }
        }
    }
    
    return result;
}

void processInput(bool decode, bool streamMode, std::istream& input, std::ostream& output) {
    if (streamMode) {
        if (decode) {
            std::string buffer;
            char c;
            while (input.get(c)) {
                if (isspace(c)) continue;
                buffer += c;
                if (buffer.size() >= 5) {
                    auto decoded = decodeAscii85(buffer.substr(0, 5));
                    output.write(reinterpret_cast<const char*>(decoded.data()), decoded.size());
                    buffer = buffer.substr(5);
                }
            }
            if (!buffer.empty()) {
                auto decoded = decodeAscii85(buffer);
                output.write(reinterpret_cast<const char*>(decoded.data()), decoded.size());
            }
        } else {
            std::vector<unsigned char> buffer;
            char c;
            while (input.get(c)) {
                buffer.push_back(c);
                if (buffer.size() == 4) {
                    output << encodeAscii85(buffer);
                    buffer.clear();
                }
            }
            if (!buffer.empty()) {
                output << encodeAscii85(buffer);
            }
        }
    } else {
        std::vector<unsigned char> data;
        char c;
        while (input.get(c)) {
            data.push_back(c);
        }
        
        if (decode) {
            std::string inputStr(data.begin(), data.end());
            auto decoded = decodeAscii85(inputStr);
            output.write(reinterpret_cast<const char*>(decoded.data()), decoded.size());
        } else {
            auto encoded = encodeAscii85(data);
            output << encoded;
        }
    }
}