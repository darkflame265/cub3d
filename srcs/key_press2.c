/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_press2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kihkim <kihkim@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/20 01:29:17 by kihkim            #+#    #+#             */
/*   Updated: 2021/05/20 01:29:25 by kihkim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	key_w_s(t_info *info)
{
	if (info->key_check[K_W] == 1)
	{
		if (info->worldMap[(int)(info->posX +
		info->dirX * info->moveSpeed)][(int)(info->posY)] != '1')
			info->posX += info->dirX * info->moveSpeed;
		if (info->worldMap[(int)(info->posX)][(int)(info->posY +
		info->dirY * info->moveSpeed)] != '1')
			info->posY += info->dirY * info->moveSpeed;
	}
	if (info->key_check[K_S] == 1)
	{
		if (info->worldMap[(int)(info->posX -
		info->dirX * info->moveSpeed)][(int)(info->posY)] != '1')
			info->posX -= info->dirX * info->moveSpeed;
		if (info->worldMap[(int)(info->posX)][(int)(info->posY -
		info->dirY * info->moveSpeed)] != '1')
			info->posY -= info->dirY * info->moveSpeed;
	}
}

void	key_d(t_info *info)
{
	double old_dir_x;
	double old_plane_x;

	old_dir_x = info->dirX;
	old_plane_x = info->planeX;
	if (info->key_check[K_D] == 1)
	{
		info->dirX = info->dirX * cos(-info->rotSpeed) -
		info->dirY * sin(-info->rotSpeed);
		info->dirY = old_dir_x * sin(-info->rotSpeed) +
		info->dirY * cos(-info->rotSpeed);
		info->planeX = info->planeX * cos(-info->rotSpeed) -
		info->planeY * sin(-info->rotSpeed);
		info->planeY = old_plane_x * sin(-info->rotSpeed) +
		info->planeY * cos(-info->rotSpeed);
	}
}

void	key_a(t_info *info)
{
	double old_dir_x;
	double old_plane_x;

	old_dir_x = info->dirX;
	old_plane_x = info->planeX;
	if (info->key_check[K_A] == 1)
	{
		info->dirX = info->dirX * cos(info->rotSpeed) -
		info->dirY * sin(info->rotSpeed);
		info->dirY = old_dir_x * sin(info->rotSpeed) +
		info->dirY * cos(info->rotSpeed);
		info->planeX = info->planeX * cos(info->rotSpeed) -
		info->planeY * sin(info->rotSpeed);
		info->planeY = old_plane_x * sin(info->rotSpeed) +
		info->planeY * cos(info->rotSpeed);
	}
}

int		key_press(t_info *info)
{
	key_w_s(info);
	key_d(info);
	key_a(info);
	if (info->key_check[K_ESC] == 1)
		exit(0);
	return (0);
}
