#include "../E_Def.h"

Vector2<int> Raycast(mapTile map[][mapHeight], Vector2<double> rayPos, Vector2<double> rayDir,	Vector2<double> &stepDir,
	int &hit, int &side)
{
	//length of ray from current position to next x or y-side
	Vector2<double> sideDist;

	//length of ray from one x or y-side to next x or y-side
   Vector2<double> deltaDist(sqrt(1 + (rayDir.y * rayDir.y) / (rayDir.x * rayDir.x)),
							 sqrt(1 + (rayDir.x * rayDir.x) / (rayDir.y * rayDir.y)));

	Vector2<int> mapPos(int(rayPos.x), int(rayPos.y));

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
		if (map[mapPos.x][mapPos.y].object > 0) hit = 1;
	}

	return mapPos;
}

void BAD() // WHEN DID HAPPEN BAD?!
{
	std::cout << "BAD" << std::endl;
}
