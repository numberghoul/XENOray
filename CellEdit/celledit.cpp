#include "celledit.h"

int Menu()
{

	int input = 0;
	cout << "CellEdit v1.0\nby Logan Williamson\n\n";
	cout << "1) Start\n";
	cout << "2) Exit\n";

	while(input < 1 || input > 2)
	{
		cin >> input;
	}

	if(input == 1)
	{
		return 1;
	}
	else
	{
		return 0;
	}
}
