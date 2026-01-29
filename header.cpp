#pragma warning(disable : 4996)
#include <iostream>
#include <stb_image.h>
#include <stb_image_write.h>
#include <algorithm>
#include <string>
#include <bitset>
#include <vector>
using namespace std;

string TextToAsciiB(string s)
{
	string asciiS;
	for (char c : s) {
		std::bitset<8> b(c); // Convert char to 8-bit binary
		asciiS += b.to_string();
	}
	return asciiS;
}
std::string BitsToAscii(const std::vector<bool>& bits)
{
	if (bits.size() % 8 != 0)
		throw std::runtime_error("Bit vector length must be a multiple of 8");

	std::string result;
	result.reserve(bits.size() / 8);

	for (size_t i = 0; i < bits.size(); i += 8)
	{
		unsigned char value = 0;

		for (int b = 0; b < 8; ++b)
		{
			value <<= 1;
			value |= bits[i + b] ? 1 : 0;
		}

		result.push_back(static_cast<char>(value));
	}

	return result;
}