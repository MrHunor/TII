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
	int stringI = 0;
	int byteI = 0;
	bool end = false;
	cout << "Encode (E) or Decode (D):";
	cin >> placeholder;
	if (placeholder == "E")
	{
		cout << "Enter filename:";
		cin >> placeholder;
		cout << "\nLoading image '" << placeholder << "'...\n";
		unsigned char* img = stbi_load(placeholder.c_str(), &w, &h, &channels, 4);
		if (img != nullptr)cout << "Loaded image.\n";
		else
		{
			cout << "Failed to load image.";
			return 0;
		}
		cout << "Enter text:";
		cin >> placeholder;
		string s = TextToAsciiB(placeholder);
		cout << "\nText to AscciBinary:" << s << endl;
		cout << "Size of text:" << s.length() << endl;
		cout << "Encoding...\n";
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
		stbi_write_png_compression_level = 9;
		stbi_write_png("output.png", w, h, 4, img, 4 * w);
		stbi_image_free(img);
		cout << "Finished.\n";
	}
	else if (placeholder == "D")
	{
		cout << "Enter Encoded Filename:";
		cin >> placeholder;
		unsigned char* imgR = stbi_load(placeholder.c_str(), &w, &h, &channels, 4);
		cout << "Loading image '" << placeholder << "'...";
		if (imgR == nullptr)
		{
			cout << "\nFailed to load image, exiting.";
			return 0;
		}
		cout << "\nLoaded image.\n";
		cout << "Enter Original Filename:";
		cin >> placeholder;
		unsigned char* imgC = stbi_load(placeholder.c_str(), &w, &h, &channels, 4);
		if (imgC == nullptr)
		{
			cout << "\nFailed to load image, exiting.";
			return 0;
		}
		cout << "\nLoaded image.\n";
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
		cout << "\nWhich in ascci is:\n" << BitsToAscii(decoded) << endl;
		stbi_image_free(imgR);
		stbi_image_free(imgC);
		cout << "Finished";
	}

	return 0;
}