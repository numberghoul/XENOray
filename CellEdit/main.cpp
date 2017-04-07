#include "celledit.h"

int main()
{
	int input = 0;
	int colors = 0;
	int level[30][30];
	std::vector<ColorRGB> mapImage;

	input = Menu();

	if (input == 0)
	{
		return 0;
	}

	cout << "Enter file path: " << endl;
	std::string path;
	cin >> path;

	unsigned long w, h;

	if(loadImage(mapImage, w, h, path))
	{
		cout << "Error.";
		return 0;
	}

	cout << "How many colors are in this map?: " << endl;
	while(colors < 1)
	{
		cin >> colors;
	}

	std::vector<ColorRGB> listColors;

	for(int i = 0; i < colors; i++)
	{
		ColorRGB tempColor;
		cout << "Enter R value for color " << i+1 << ": ";
		cin >> tempColor.r;
		cout << "Enter G value for color " << i+1 << ": ";
		cin >> tempColor.g;
		cout << "Enter B value for color " << i+1 << ": ";
		cin >> tempColor.b;

		listColors.push_back(tempColor);
	}

	for(int i = 0; i < mapImage.size(); i++)
	{
		for(int j = 0; j < listColors.size(); j++)
		{
			if(mapImage[i] == listColors[j])
			{
				level[i/30][i%30] = j + 1;
				break;
			}
			else
			{
				level[i/30][i%30] = 0;
			}
		}
	}

	for(int i = 0; i < 30; i++)
	{
		cout << "{";

		for(int j = 0; j < 30; j++)
		{
			cout << level[i][j] << ",";
		}

		cout << "},";

		cout << endl;
	}

	return 0;
}
