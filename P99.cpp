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
using std::cout;
using std::endl;
int main(int argc, char* argv[])
{
	switch (argc)
	{
	case 1:
	{
		bool end = false;

		vector<bool> decoded;
		string placeholder;
		int w, h, channels;
		int stringI = 0;
		int byteI = 0;

		if (argc == 1)
		{
			cout << "Encode (E) or Decode (D):";
			cin >> placeholder;
		}
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
	}
	break;
	default:
	{
		bool end = false;
		//argument checking

		if (string(argv[1]) != "E" && string(argv[1]) != "D")end = true;
		if (string(argv[1]) == "E" && (argc > 3 || argc < 2))end = true;
		if (string(argv[1]) == "D" && (argc > 4 || argc < 3))end = true;
		if (end)
		{
			cout << "Wrong command entered.\nP99 Syntax:\n";
			cout << "P99.exe E/D (inputFileName)/(EncodedFileName OriginalFileName) (TEXT)/()\n";
			cout << "Given Syntax: P99.exe ";
			for (int i = 0; i < argc; i++)
			{
				cout << argv[i] << " ";
			}
			return 0;
		}
		vector<bool> decoded;
		string placeholder;
		int w, h, channels;
		int stringI = 0;
		int byteI = 0;

		if (argv[0] == "E")
		{
			unsigned char* img = stbi_load(string(argv[2]).c_str(), &w, &h, &channels, 4);
			if (img != nullptr)cout << "Loaded image.\n";
			else
			{
				cout << "Failed to load image.";
				return 0;
			}

			string s = TextToAsciiB(string(argv[3]));
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
		else if (placeholder == "D" || argv[0] == "D")
		{
			unsigned char* imgR = stbi_load(string(argv[2]).c_str(), &w, &h, &channels, 4);
			cout << "Loading image '" << placeholder << "'...";
			if (imgR == nullptr)
			{
				cout << "\nFailed to load image, exiting.";
				return 0;
			}
			cout << "\nLoaded image.\n";
			unsigned char* imgC = stbi_load(string(argv[3]).c_str(), &w, &h, &channels, 4);
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
	}
	break;
	}

	return 0;
}