#include "../includes/cub3d.h"

float dist(float ax, float ay, float bx, float by)
{
	return ( sqrt ((bx - ax) * (bx - ax) + (by - ay) * (by - ay)));
}

void	sort_order(t_pair *orders, int amount)
{
	t_pair	tmp;

	for (int i = 0; i < amount; i++)
	{
		for (int j = 0; j < amount - 1; j++)
		{
			if (orders[j].first > orders[j + 1].first)
			{
				tmp.first = orders[j].first;
				tmp.second = orders[j].second;
				orders[j].first = orders[j + 1].first;
				orders[j].second = orders[j + 1].second;
				orders[j + 1].first = tmp.first;
				orders[j + 1].second = tmp.second;
			}
		}
	}
}

void	sortSprites(int *order, double *dist, int amount)
{
	t_pair	*sprites;

	//std::vector<std::pair<double, int>> sprites(amount);
	sprites = (t_pair*)malloc(sizeof(t_pair) * amount);
	for (int i = 0; i < amount; i++)
	{
		sprites[i].first = dist[i];
		sprites[i].second = order[i];
	}
	sort_order(sprites, amount);
	//std::sort(sprites.begin(), sprites.end());
	for (int i = 0; i < amount; i++)
	{
		dist[i] = sprites[amount - i - 1].first;
		order[i] = sprites[amount - i - 1].second;
	}
	free(sprites);
}

void	calc(t_info *info)
{
	int	x;

	x = 0;
	while (x < info->width) //윈도우 화면의 가로 길이만큼, 광선을 발사.
	{

		double cameraX = 2 * x / (double)info->width - 1;
		double rayDirX = info->dirX + info->planeX * cameraX;
		double rayDirY = info->dirY + info->planeY * cameraX;

		int mapX = (int)info->posX;
		int mapY = (int)info->posY;

		//length of ray from current position to next x or y-side: 플레이어에서 벽까지의 거리.
		double sideDistX;
		double sideDistY;

		 //length of ray from one x or y-side to next x or y-side: 벽에서 벽까지의 거리.
		double deltaDistX = fabs(1 / rayDirX);
		double deltaDistY = fabs(1 / rayDirY);
		double perpWallDist;

		//what direction to step in x or y-direction (either +1 or -1)
		int stepX;
		int stepY;

		int hit = 0; //was there a wall hit?
		int side; //was a NS or a EW wall hit?

		if (rayDirX < 0) //x벡터가 음수 -> 광선이 왼쪽으로 이동.
		{
			stepX = -1;
			sideDistX = (info->posX - mapX) * deltaDistX;
		}
		else //x벡터가 양수 -> 광선이 오른쪽으로 이동.
		{
			stepX = 1;
			sideDistX = (mapX + 1.0 - info->posX) * deltaDistX;
		}
		if (rayDirY < 0) //y벡터가 음수 -> 광선이 ???쪽으로 이동.
		{
			stepY = -1;
			sideDistY = (info->posY - mapY) * deltaDistY;
		}
		else
		{
			stepY = 1;
			sideDistY = (mapY + 1.0 - info->posY) * deltaDistY;
		}

		while (hit == 0)
		{
			//jump to next map square, OR in x-direction, OR in y-direction
			if (sideDistX < sideDistY) //남북(x축) 벽에 부딪힘.
			{
				sideDistX += deltaDistX;
				mapX += stepX;
				side = 0;
			}
			else //동서 벽에 부딪힘.
			{
				sideDistY += deltaDistY;
				mapY += stepY;
				side = 1;
			}
			//Check if ray has hit a wall
			if (info->worldMap[mapX][mapY] == '1') hit = 1;
		}

		if (side == 0)
			perpWallDist = (mapX - info->posX + (1 - stepX) / 2) / rayDirX;
		else
			perpWallDist = (mapY - info->posY + (1 - stepY) / 2) / rayDirY;


		//이렇게 perpWallDist, 즉 벽까지의 거리를 구했다.

		//Calculate height of line to draw on screen
		//화면의 높이의 값과 비교해서 그 비율을 알아내고, 그려야 할 벽의 높이를 알아냄.
		int lineHeight = (int)(info->height / perpWallDist);

		//시작점: 화면의 중앙에서 벽의 높이만큼(정확히는 그절반) 위로.
		int drawStart = -lineHeight / 2 + info->height / 2;
		if(drawStart < 0)
			drawStart = 0;
		//도착점: 화면의 중앙에서 벽의 높이만큼(정확히는 그절반) 아래로.
		int drawEnd = lineHeight / 2 + info->height / 2;
		if(drawEnd >= info->height)
			drawEnd = info->height - 1;
		// printf("mapX: %d, mapY: %d\n", mapX, mapY);
		// printf("info->worldMap[%d][%d]: %c\n", mapX, mapY, info->worldMap[mapX][mapY]);

		//아래 월드맵 mapX, mapY 바꿨음. 원래는 [mapY][mapX]
		int	color;
		if (info->worldMap[mapX][mapY] == '1')
			color = 0xFF0000;

		//texturing calculations
		//int texNum = info->worldMap[mapX][mapY] - 1; //1 subtracted from it so that texture 0 can be used!

		int texNum = 0;
		if (info->worldMap[mapX][mapY] == '1')
			texNum = 0;


		//atoi사용.

		//calculate value of wallX
		double wallX; //where exactly the wall was hit
		if (side == 0) wallX = info->posY + perpWallDist * rayDirY;
		else           wallX = info->posX + perpWallDist * rayDirX;
		wallX -= floor((wallX));

		//x coordinate on the texture
		int texX = (int) (wallX * (double)texWidth);
		// 기본은 동쪽. (texNum == 1)


		if(side == 0 && rayDirX > 0)
		{
			texX = texWidth - texX - 1;
			texNum++; //서
		}
		if(side == 1 && rayDirY < 0)
		{
			texX = texWidth - texX - 1;
			texNum += 3; //남
		}
		if(side == 1 && rayDirY > 0)
		{
			//texX = texWidth - texX - 1;
			texNum += 2; //북
		}


		double step = 1.0 * texHeight / lineHeight;
		// Starting texture coordinate
		double texPos = (drawStart - info->height / 2 + lineHeight / 2) * step;
		for(int y = drawStart; y<drawEnd; y++)
		{
			// Cast the texture coordinate to integer, and mask with (texHeight - 1) in case of overflow
			int texY = (int)texPos & (texHeight - 1);
			texPos += step;
			color = info->texture[texNum][texHeight * texY + texX];
			//make color darker for y-sides: R, G and B byte each divided through two with a "shift" and an "and"
			//if(side == 1) color = (color >> 1) & 8355711;
			info->buf[y][x] = color;
		}

		// Z-버퍼에 플레이어(카메라)에서 벽까지의 거리 값을 담는다.
		info->zBuffer[x] = perpWallDist;

		//천장 색칠.
		//verLine(info, x, 0, drawStart, 0xFFFFFF);
		color = (255 << 24);
		color = color | (info->gnl_info.cc[0] << 16);
		color = color | (info->gnl_info.cc[1] << 8);
		color = color | (info->gnl_info.cc[2] << 0);
		// color = color | (128);
		//printf("color: %x\n", color);

		verLine(info, x, 0, drawStart, color);

		//바닥 색칠.
		color = (255 << 24);
		color = color | (info->gnl_info.ff[0] << 16);
		color = color | (info->gnl_info.ff[1] << 8);
		color = color | (info->gnl_info.ff[2] << 0);
		verLine(info, x, drawEnd, info->height - 1, color);
		//verLine(info, x, drawEnd, height - 1, 0xFFFFFF);
		x++;
	}

	//스프라이트 기능.(Sprite culture)
	for(int i = 0; i < info->sprite_stack; i++)
	{
		spriteOrder[i] = i;
		spriteDistance[i] =	dist(info->posX, info->posY, sprite[i].x, sprite[i].y);
	}
	sortSprites(spriteOrder, spriteDistance, info->sprite_stack);

	for(int i = 0; i < info->sprite_stack; i++)
	{
		//translate sprite position to relative to camera
		double spriteX = sprite[spriteOrder[i]].x - info->posX;
		double spriteY = sprite[spriteOrder[i]].y - info->posY;

			//transform sprite with the inverse camera matrix
			// [ planeX   dirX ] -1                                       [ dirY      -dirX ]
			// [               ]       =  1/(planeX*dirY-dirX*planeY) *   [                 ]
			// [ planeY   dirY ]                                          [ -planeY  planeX ]

		double invDet = 1.0 / (info->planeX * info->dirY - info->dirX * info->planeY); //required for correct matrix multiplication

		double transformX = invDet * (info->dirY * spriteX - info->dirX * spriteY);
		double transformY = invDet * (-info->planeY * spriteX + info->planeX * spriteY); //this is actually the depth inside the screen, that what Z is in 3D, the distance of sprite to player, matching sqrt(spriteDistance[i])

		int spriteScreenX = (int)((info->width / 2) * (1 + transformX / transformY));

		//parameters for scaling and moving the sprites
		#define uDiv 1
		#define vDiv 1
		#define vMove 0.0
		int vMoveScreen = (int)(vMove / transformY);

			//calculate height of the sprite on screen
		int spriteHeight = (int)fabs((info->height / transformY) / vDiv); //using "transformY" instead of the real distance prevents fisheye
			//calculate lowest and highest pixel to fill in current stripe
		int drawStartY = -spriteHeight / 2 + info->height / 2 + vMoveScreen;
		if(drawStartY < 0) drawStartY = 0;
		int drawEndY = spriteHeight / 2 + info->height / 2 + vMoveScreen;
		if(drawEndY >= info->height) drawEndY = info->height - 1;

			//calculate width of the sprite
		int spriteWidth = (int)fabs((info->height / transformY) / uDiv);
		int drawStartX = -spriteWidth / 2 + spriteScreenX;
		if(drawStartX < 0) drawStartX = 0;
		int drawEndX = spriteWidth / 2 + spriteScreenX;

		if(drawEndX >= info->width) drawEndX = info->width - 1;

			//loop through every vertical stripe of the sprite on screen
		//if (x == 1)
		//printf("ss: %d\n", sprite[spriteOrder[i]].texture);
		//printf("width: %d\n", info->tex[sprite[spriteOrder[i]].texture].tex_width);
		for(int stripe = drawStartX; stripe < drawEndX; stripe++)
		{
			int texX = (int)((256 * (stripe - (-spriteWidth / 2 + spriteScreenX)) * info->tex[sprite[spriteOrder[i]].texture].tex_width / spriteWidth) / 256);
			if(transformY > 0 && stripe > 0 && stripe < info->width && transformY < info->zBuffer[stripe])
			for(int y = drawStartY; y < drawEndY; y++) //for every pixel of the current stripe
			{
				int d = (y-vMoveScreen) * 256 - info->height * 128 + spriteHeight * 128; //256 and 128 factors to avoid floats
				int texY = ((d * info->tex[sprite[spriteOrder[i]].texture].tex_height) / spriteHeight) / 256;
				int color = info->texture[sprite[spriteOrder[i]].texture][info->tex[sprite[spriteOrder[i]].texture].tex_width * texY + texX]; //get current color from the texture
				if((color & 0x00FFFFFF) != 0)
					info->buf[y][stripe] = color; //paint pixel if it isn't black, black is the invisible color
			}
		}
	}
}

//Map에 표기해서 플레이어 소환 위치 지정하는 기능.
// => 이를 위해서는 우선 worldMap을 char로 바꿔야함.
// (0 == 빈공간, 1== 벽, 2 = 스프라이트, w,e,s,n = 플레이어.)
