#pragma warning(disable : 4996)
#define STB_IMAGE_IMPLEMENTATION
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include <iostream>
#include <stb_image.h>
#include <stb_image_write.h>
#include <algorithm>
#include <string>
#include <vector>
#include "Header.h"
using namespace std;
int main()
{
	vector<bool> decoded;
	string placeholder;
	int w, h, channels;
	int length;
	int xy[2];
	bool bit;
	bool breakOut = false;
	bool prepOp[4];
	int stringI = 0;
	int byteI = 0;
	bool end = false;
	cout << "Encode (E) or Decode (D):";
	cin >> placeholder;
	if (placeholder == "E")
	{
		cout << "Enter text:";
		cin >> placeholder;
		string s = TextToAsciiB(placeholder);
		cout << "\nText to AscciBinary:" << s << endl;
		cout << "Size of text:" << s.length() << endl;
		cout << "Encoding...\n";
		cout << "Loading image 'input.png'...\n";
		unsigned char* img = stbi_load("input.png", &w, &h, &channels, 4);
		if (img != nullptr)cout << "Loaded images.\n";
		else
		{
			cout << "Failed to load image.";
			return 0;
		}
		cout << "Loaded image.\n";
		cout << "Writing compare image...\n";
		stbi_write_png("compare.png", w, h, 4, img, 4 * w);
		//Magik
		while (true)
		{
			cout << "byteI:" << byteI << endl;
			cout << "stringI:" << stringI << endl;
			if (img[byteI] > 0 && img[byteI] < 255)
			{
				if (s[stringI] == '0')
				{
					img[byteI]--;
					stringI++;
				}
				else if (s[stringI] == '1')
				{
					img[byteI]++;
					stringI++;
				}
			}
			byteI++;
			if (stringI == s.length()) {
				break;
			}
		}
		cout << "Writing file 'output.png'...\n";
		stbi_write_png("output.png", w, h, 4, img, 4 * w);
		stbi_image_free(img);
		cout << "Finished.\n";
	}
	else if (placeholder == "D")
	{
		placeholder.clear();
		cout << "Decoding...\n";
		cout << "Loading 'output.png' and 'compare.png'...\n";
		unsigned char* imgR = stbi_load("output.png", &w, &h, &channels, 4);
		unsigned char* imgC = stbi_load("compare.png", &w, &h, &channels, 4);
		if (imgR != nullptr && imgC != nullptr)cout << "Loaded images.\n";
		else
		{
			cout << "Failed to load images.";
			return 0;
		}
		while (!end)
		{
			cout << "byteI:" << byteI << endl;
			cout << "stringI:" << stringI << endl;
			if (imgC[byteI] > 0 && imgC[byteI] < 255)
			{
				if (imgR[byteI] == imgC[byteI] - 1)
				{
					decoded.push_back(false);
					stringI++;
				}
				else if (imgR[byteI] == imgC[byteI] + 1)
				{
					decoded.push_back(true);
					stringI++;
				}
				else
				{
					end = true;
				}
			}
			byteI++;
		}
		cout << "Read following binary:";
		for (bool i : decoded)
		{
			if (i == false)cout << "0";
			if (i == true)cout << "1";
		}
		cout << "\nWhich in ascci is:" << BitsToAscii(decoded);
		stbi_image_free(imgR);
		stbi_image_free(imgC);
		cout << "Finished";
	}

	return 0;
}