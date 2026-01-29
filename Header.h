#pragma once
#include <iostream>
using namespace std;
extern void ManipulatePixel(unsigned char* img, int pixel, bool operation[4]);
extern void ComparePixel(unsigned char* imgR, unsigned char* imgC, int index, bool operation[4]);
string TextToAsciiB(string s);
extern bool comparePixels(unsigned char* imgR, unsigned char* imgC, int x, int y, int w, int h, float comparefactor);
extern void calxy(int count, int w, int retarray[2]);
extern std::string BitsToAscii(const std::vector<bool>& bits);