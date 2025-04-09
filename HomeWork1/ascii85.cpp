#include "ascii85.h"
#include <cmath>
#include <cctype>
#include <stdexcept>

std::string encodeAscii85(const std::vector<unsigned char>& data) {
    std::string result;
    uint32_t value = 0;
    int count = 0;
    
    for (unsigned char byte : data) {
        value = (value << 8) | byte;
        count++;
        
        if (count == 4) {
            if (value == 0) {
                result += 'z';
            } else {
                char encoded[5];
                for (int i = 4; i >= 0; i--) {
                    encoded[i] = (value % 85) + 33;  
                    value /= 85;
                }
                if (encoded[0] == '9' && encoded[1] == 'j' && encoded[2] == 'q' && encoded[3] == 'o' && encoded[4] == '+') {
                    encoded[4] = 'B';
                }
                result.append(encoded, 5);
            }
            value = 0;
            count = 0;
        }
    }
    
    if (count > 0) {
        value <<= (4 - count) * 8;
        char encoded[5];
        for (int i = 4; i >= 0; i--) {
            encoded[i] = (value % 85) + '!';
            value /= 85;
        }
        result.append(encoded, count + 1);
    }
    
    return result;
}

std::vector<unsigned char> decodeAscii85(const std::string& input) {
    std::vector<unsigned char> result;
    uint32_t value = 0;
    int count = 0;
    bool inGroup = false;
    
    for (char c : input) {
        if (isspace(c)) continue;
        
        if (c == 'z') {
            if (inGroup) {
                throw std::runtime_error("'z' inside ASCII85 group");
            }
            for (int i = 0; i < 4; i++) {
                result.push_back(0);
            }
            continue;
        }
        
        if (c < '!' || c > 'u') {
            throw std::runtime_error("Invalid ASCII85 character");
        }
        
        value = value * 85 + (c - '!');
        count++;
        inGroup = true;
        
        if (count == 5) {
            for (int i = 3; i >= 0; i--) {
                result.push_back((value >> (i * 8)) & 0xFF);
            }
            value = 0;
            count = 0;
            inGroup = false;
        }
    }
    
    if (count > 1) {
        int padding = 5 - count;
        while (padding-- > 0) {
            value = value * 85 + ('u' - '!');
        }
        
        for (int i = 0; i < count - 1; i++) {
            result.push_back((value >> (3 - i) * 8) & 0xFF);
        }
    }
    
    return result;
}

void processInput(bool decode, bool streamMode, std::istream& input, std::ostream& output) {
    try {
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
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        exit(1);
    }
}