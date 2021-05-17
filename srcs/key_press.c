#include "../includes/cub3d.h"

int Button_down(int keycode, t_info *info)
{
	if (keycode >= 300 && keycode != K_ESC)
		return (-1);
	info->key_check[keycode] = 1;
	return (0);
}

int Button_release(int keycode, t_info *info)
{
	if (keycode >= 300 && keycode != K_ESC)
		return (-1);
	info->key_check[keycode] = 0;
	return (0);
}

int	key_press(t_info *info)
{
	if (info->key_check[K_W] == 1)
	{
		// if (!info->worldMap[(int)(info->posX + info->dirX * info->moveSpeed)][(int)(info->posY)])
		// 	info->posX += info->dirX * info->moveSpeed;
		// if (!info->worldMap[(int)(info->posX)][(int)(info->posY + info->dirY * info->moveSpeed)])
		// 	info->posY += info->dirY * info->moveSpeed;
		if (info->worldMap[(int)(info->posX + info->dirX * info->moveSpeed)][(int)(info->posY)] != '1')
			info->posX += info->dirX * info->moveSpeed;
		if (info->worldMap[(int)(info->posX)][(int)(info->posY + info->dirY * info->moveSpeed)] != '1')
			info->posY += info->dirY * info->moveSpeed;
	}
	//move backwards if no wall behind you
	if (info->key_check[K_S] == 1)
	{
		// if (!info->worldMap[(int)(info->posX - info->dirX * info->moveSpeed)][(int)(info->posY)])
		// 	info->posX -= info->dirX * info->moveSpeed;
		// if (!info->worldMap[(int)(info->posX)][(int)(info->posY - info->dirY * info->moveSpeed)])
		// 	info->posY -= info->dirY * info->moveSpeed;
		if (info->worldMap[(int)(info->posX - info->dirX * info->moveSpeed)][(int)(info->posY)] != '1')
			info->posX -= info->dirX * info->moveSpeed;
		if (info->worldMap[(int)(info->posX)][(int)(info->posY - info->dirY * info->moveSpeed)] != '1')
			info->posY -= info->dirY * info->moveSpeed;
	}
	//rotate to the right
	if (info->key_check[K_D] == 1)
	{
		//both camera direction and camera plane must be rotated
		double oldDirX = info->dirX;
		info->dirX = info->dirX * cos(-info->rotSpeed) - info->dirY * sin(-info->rotSpeed);
		info->dirY = oldDirX * sin(-info->rotSpeed) + info->dirY * cos(-info->rotSpeed);
		double oldPlaneX = info->planeX;
		info->planeX = info->planeX * cos(-info->rotSpeed) - info->planeY * sin(-info->rotSpeed);
		info->planeY = oldPlaneX * sin(-info->rotSpeed) + info->planeY * cos(-info->rotSpeed);
	}
	//rotate to the left
	if (info->key_check[K_A] == 1)
	{
		//both camera direction and camera plane must be rotated
		double oldDirX = info->dirX;
		info->dirX = info->dirX * cos(info->rotSpeed) - info->dirY * sin(info->rotSpeed);
		info->dirY = oldDirX * sin(info->rotSpeed) + info->dirY * cos(info->rotSpeed);
		double oldPlaneX = info->planeX;
		info->planeX = info->planeX * cos(info->rotSpeed) - info->planeY * sin(info->rotSpeed);
		info->planeY = oldPlaneX * sin(info->rotSpeed) + info->planeY * cos(info->rotSpeed);
	}
	if (info->key_check[K_ESC] == 1)
		exit(0);
	return (0);
}
