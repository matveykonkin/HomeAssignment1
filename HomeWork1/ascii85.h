#ifndef ASCII85_H
#define ASCII85_H

#include <vector>
#include <string>
#include <stdexcept>
#include <iostream>

std::string encodeAscii85(const std::vector<unsigned char>& data);
std::vector<unsigned char> decodeAscii85(const std::string& input);
void processInput(bool decode, bool streamMode, std::istream& input, std::ostream& output);

#endif