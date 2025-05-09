#include "ascii85.h"
#include <gtest/gtest.h>
#include <sstream>

TEST(Ascii85Test, EncodeEmpty) {
std::vector<unsigned char> empty;
EXPECT_EQ(encodeAscii85(empty), "");
}

TEST(Ascii85Test, EncodeSingleChar) {
std::vector<unsigned char> data = {'A'};
EXPECT_EQ(encodeAscii85(data), "5l");
}

TEST(Ascii85Test, EncodeFourZeros) {
std::vector<unsigned char> data = {0, 0, 0, 0};
EXPECT_EQ(encodeAscii85(data), "z");
}

TEST(Ascii85Test, DecodeEmpty) {
std::string empty;
auto result = decodeAscii85(empty);
EXPECT_TRUE(result.empty());
}

TEST(Ascii85Test, DecodeSingleChar) {
std::string input = "5l";
auto result = decodeAscii85(input);
EXPECT_EQ(result.size(), 1);
EXPECT_EQ(result[0], 'A');
}

TEST(Ascii85Test, DecodeFourZeros) {
std::string input = "z";
auto result = decodeAscii85(input);
EXPECT_EQ(result.size(), 4);
for (auto b : result) {
EXPECT_EQ(b, 0);
}
}

TEST(Ascii85Test, RoundTrip) {
std::vector<unsigned char> data = {'H', 'e', 'l', 'l', 'o', ' ', 'W', 'o', 'r', 'l', 'd', '!'};
auto encoded = encodeAscii85(data);
auto decoded = decodeAscii85(encoded);
EXPECT_EQ(decoded, data);
}

TEST(Ascii85Test, ProcessInputEncode) {
std::stringstream input("Hello");
std::stringstream output;
processInput(false, false, input, output);
EXPECT_EQ(output.str(), "87cURDZ");
}

TEST(Ascii85Test, ProcessInputDecode) {
std::stringstream input("87cURDZ");
std::stringstream output;
processInput(true, false, input, output);
EXPECT_EQ(output.str(), "Hello");
}

TEST(Ascii85Test, ProcessInputStreamMode) {
std::stringstream input("Hello");
std::stringstream output;
processInput(false, true, input, output);
EXPECT_EQ(output.str(), "87cURDZ");
}

TEST(Ascii85Test, HobbesLeviathanQuote) {
std::string quote = "Man is distinguished, not only by his reason, but by this singular passion from other animals, which is a lust of the mind, that by a perseverance of delight in the continued and indefatigable generation of knowledge, exceeds the short vehemence of any carnal pleasure.";
std::vector<unsigned char> data(quote.begin(), quote.end());
auto encoded = encodeAscii85(data);
auto decoded = decodeAscii85(encoded);
std::string decoded_str(decoded.begin(), decoded.end());
EXPECT_EQ(decoded_str, quote);
}

int main(int argc, char **argv) {
testing::InitGoogleTest(&argc, argv);
return RUN_ALL_TESTS();
}