#include "Render.h"

void Render(Vector2<double> position, Vector2<double> direction, Vector2<double> cameraPlane, int w, int h,
	int worldMap[][24])
{
	for(int x = 0; x < w; x++)
	{
		//calculate ray position and direction
		double cameraX = 2 * x / double(w) - 1; //x-coordinate in camera space

		Vector2<double> rayPos(position.x, position.y);
		Vector2<double> rayDir(direction.x + cameraPlane.x * cameraX, direction.y + cameraPlane.y * cameraX);

		//which box of the map we're in
		Vector2<int> mapPos(int(rayPos.x), int(rayPos.y));

		//length of ray from current position to next x or y-side
		Vector2<double> sideDist;

		 //length of ray from one x or y-side to next x or y-side
		Vector2<double> deltaDist(sqrt(1 + (rayDir.y * rayDir.y) / (rayDir.x * rayDir.x)),
								  sqrt(1 + (rayDir.x * rayDir.x) / (rayDir.y * rayDir.y)));
		double perpWallDist;

		//what direction to step in x or y-direction (either +1 or -1)
		Vector2<int> stepDir;

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
			if (worldMap[mapPos.x][mapPos.y] > 0) hit = 1;
		}
		//Calculate distance projected on camera direction (oblique distance will give fisheye effect!)
		if (side == 0) perpWallDist = (mapPos.x - rayPos.x + (1 - stepDir.x) / 2) / rayDir.x;
		else		   perpWallDist = (mapPos.y - rayPos.y + (1 - stepDir.y) / 2) / rayDir.y;

		//Calculate height of line to draw on screen
		int lineHeight = (int)(h / perpWallDist);

		//calculate lowest and highest pixel to fill in current stripe
		int drawStart = -lineHeight / 2 + h / 2;
		if(drawStart < 0)drawStart = 0;
		int drawEnd = lineHeight / 2 + h / 2;
		if(drawEnd >= h)drawEnd = h - 1;

		//choose wall color
		ColorRGB color;
		switch(worldMap[mapPos.x][mapPos.y])
		{
			case 1:	color = RGB_Red;	break; //red
			case 2:	color = RGB_Green;	break; //green
			case 3:	color = RGB_Blue;	 break; //blue
			case 4:	color = RGB_White;	break; //white
			default: color = RGB_Yellow; break; //yellow
		}

		//give x and y sides different brightness
		if (side == 1) {color = color / 2;}

		//draw the pixels of the stripe as a vertical line
		verLine(x, drawStart, drawEnd, color);
	}
}
