#include "HelperFunctions.h"

Vector2<int> Raycast(Vector2<int> rayPos, Vector2<double> &rayDir, int &hit, int &side)
{
	//length of ray from current position to next x or y-side
	Vector2<double> sideDist;
	//what direction to step in x or y-direction (either +1 or -1)
	Vector2<double> stepDir;
	Vector2<int> mapPos(int(rayPos.x), int(rayPos.y));

	int hit = 0; //was there a wall hit?
	int side; //was a NS or a EW wall hit?

	//calculate step and initial sideDist
	if (rayDir.x < 0)
	{
		stepDir.x = -1;
		sideDist.x = (rayPos.x - mapPos.x) * deltaDist.x;
	}
	else
	{
		stepDir.x = 1;
		sideDist.x = (mapPos.x + 1.0 - rayPos.x) * deltaDist.x;
	}
	if (rayDir.y < 0)
	{
		stepDir.y = -1;
		sideDist.y = (rayPos.y - mapPos.y) * deltaDist.y;
	}
	else
	{
		stepDir.y = 1;
		sideDist.y = (mapPos.y + 1.0 - rayPos.y) * deltaDist.y;
	}

	//perform DDA
	while (hit == 0)
	{
		//jump to next map square, OR in x-direction, OR in y-direction
		if (sideDist.x < sideDist.y)
		{
			sideDist.x += deltaDist.x;
			mapPos.x += stepDir.x;
			side = 0;
		}
		else
		{
			sideDist.y += deltaDist.y;
			mapPos.y += stepDir.y;
			side = 1;
		}
		//Check if ray has hit a wall
		if (mMap[mapPos.x][mapPos.y].object > 0) hit = 1;
	}
}
