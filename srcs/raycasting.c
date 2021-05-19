#include "../includes/cub3d.h"

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
		color = (255 << 24);
		color = color | (info->gnl_info.cc[0] << 16);
		color = color | (info->gnl_info.cc[1] << 8);
		color = color | (info->gnl_info.cc[2] << 0);
		// color = color | (128);
		//printf("color: %x\n", color);

		//verLine(info, x, 0, drawStart, color);
		//void	verLine(t_info *info, int x, int y1, int y2, int color)
		int	z;

		z = 0;
		while (z <= drawStart)
		{
			info->buf[z][x] = color;
			z++;
		}

		color = (255 << 24);
		color = color | (info->gnl_info.ff[0] << 16);
		color = color | (info->gnl_info.ff[1] << 8);
		color = color | (info->gnl_info.ff[2] << 0);

		z = drawEnd;
		while (z <= info->height - 1)
		{
			info->buf[z][x] = color;
			z++;
		}

		x++;
	}

	for(int i = 0; i < info->sprite_stack; i++)
	{
		spriteOrder[i] = i;
		spriteDistance[i] =	dist(info->posX, info->posY, sprite[i].x, sprite[i].y);
	}
	sort_sprites(spriteOrder, spriteDistance, info->sprite_stack);

	for(int i = 0; i < info->sprite_stack; i++)
	{
		double spriteX = sprite[spriteOrder[i]].x - info->posX;
		double spriteY = sprite[spriteOrder[i]].y - info->posY;
		double invDet = 1.0 / (info->planeX * info->dirY - info->dirX * info->planeY);
		double transformX = invDet * (info->dirY * spriteX - info->dirX * spriteY);
		double transformY = invDet * (-info->planeY * spriteX + info->planeX * spriteY);
		int spriteScreenX = (int)((info->width / 2) * (1 + transformX / transformY));
		int vMoveScreen = (int)(vMove / transformY);
		int spriteHeight = (int)fabs((info->height / transformY) / vDiv);
		int drawStartY = -spriteHeight / 2 + info->height / 2 + vMoveScreen;
		if(drawStartY < 0) drawStartY = 0;
		int drawEndY = spriteHeight / 2 + info->height / 2 + vMoveScreen;
		if(drawEndY >= info->height) drawEndY = info->height - 1;
		int spriteWidth = (int)fabs((info->height / transformY) / uDiv);
		int drawStartX = -spriteWidth / 2 + spriteScreenX;
		if(drawStartX < 0) drawStartX = 0;
		int drawEndX = spriteWidth / 2 + spriteScreenX;
		if(drawEndX >= info->width) drawEndX = info->width - 1;
		for(int stripe = drawStartX; stripe < drawEndX; stripe++)
		{
			int texX = (int)((256 * (stripe - (-spriteWidth / 2 + spriteScreenX)) * info->tex[sprite[spriteOrder[i]].texture].tex_width / spriteWidth) / 256);
			if(transformY > 0 && stripe > 0 && stripe < info->width && transformY < info->zBuffer[stripe])
			for(int y = drawStartY; y < drawEndY; y++)
			{
				int d = (y-vMoveScreen) * 256 - info->height * 128 + spriteHeight * 128;
				int texY = ((d * info->tex[sprite[spriteOrder[i]].texture].tex_height) / spriteHeight) / 256;
				int color = info->texture[sprite[spriteOrder[i]].texture][info->tex[sprite[spriteOrder[i]].texture].tex_width * texY + texX];
				if((color & 0x00FFFFFF) != 0)
					info->buf[y][stripe] = color;
			}
		}
	}
}
