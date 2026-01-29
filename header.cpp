#pragma warning(disable : 4996)
#include <iostream>
#include <stb_image.h>
#include <stb_image_write.h>
#include <algorithm>
#include <string>
#include <bitset>
#include <vector>
using namespace std;
void ManipulatePixel(unsigned char* img, int index, bool operation[4])
{
	for (size_t z = 0; z < 3; z++)
	{
		if (!operation[z])img[index + z]--;
		else if (operation[z])img[index + z]++;
	}
}
void ComparePixel(unsigned char* imgR, unsigned char* imgC, int index, bool operation[4])
{
	for (size_t z = 0; z < 3; z++)
	{
		if (imgR[index + z] == imgC[index + z] + 1) operation[z] = false;
		else operation[z] = true;
	}
}
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
char byteToAscii(uint8_t byte)
{
	return static_cast<char>(byte);
}
string AsciiBToText(string s)
{
	string TextS;
	string value;
	for (int i = 0; i < s.length(); i = i + 8)
	{
		value.clear();
		for (int z = 0; z < 7; z++)
		{
			value = value + to_string(s[i + z]);
		}
		TextS = TextS + byteToAscii(static_cast<uint8_t>(stoi(value, nullptr, 2)));
	}
	return TextS;
}

void calxy(int count, int w, int retarray[2])
{
	retarray[0] = count / w;
	retarray[1] = count % w;
}

//imgR = imageResult (the encoded), imgC=Image to compare to (original)
bool comparePixels(unsigned char* imgR, unsigned char* imgC, int x, int y, int w, int h, float comparefactor)
{
	int index;
	index = (y * w + x) * 4;
	if (imgR[index + 0] == (unsigned char)clamp(imgC[index + 0] * comparefactor, 0.0f, 255.0f)
		&& imgR[index + 1] == (unsigned char)clamp(imgC[index + 1] * comparefactor, 0.0f, 255.0f)
		&& imgR[index + 2] == (unsigned char)clamp(imgC[index + 2] * comparefactor, 0.0f, 255.0f)
		&& imgR[index + 3] == (unsigned char)clamp(imgC[index + 3] * comparefactor, 0.0f, 255.0f))
	{
		return true;
	}
	else return false;
}