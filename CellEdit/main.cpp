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

  cout << "Enter path for this map: " << endl;
  std::string path;
  cin >> path;

  LoadImage(path, mapImage);

  cout << "How many colors are in this map?: " << endl;
  while(colors < 1)
  {
    cin >> colors;
  }

  std::vector<ColorRGB> listColors;

  for(int i = 0; i < colors; i++)
  {
    ColorRGB tempColor;
    cout << "Enter R value for image" << i << ": ";
    cin >> tempColor.r;
    cout << "Enter G value for image" << i << ": ";
    cin >> tempColor.g;
    cout << "Enter B value for image" << i << ": ";
    cin >> tempColor.b;

    listColors.push_back(tempColor);
  }



  return 0;
}
