/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kihkim <kihkim@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/23 00:07:14 by kihkim            #+#    #+#             */
/*   Updated: 2021/05/23 00:07:14 by kihkim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	next_step(t_info *info)
{
	if (info->calc.rayDirX < 0)
	{
		info->calc.stepX = -1;
		info->calc.sideDistX = (info->posX - info->calc.mapX)
		* info->calc.deltaDistX;
	}
	else
	{
		info->calc.stepX = 1;
		info->calc.sideDistX = (info->calc.mapX + 1.0 - info->posX)
		* info->calc.deltaDistX;
	}
	if (info->calc.rayDirY < 0)
	{
		info->calc.stepY = -1;
		info->calc.sideDistY = (info->posY - info->calc.mapY)
		* info->calc.deltaDistY;
	}
	else
	{
		info->calc.stepY = 1;
		info->calc.sideDistY = (info->calc.mapY + 1.0 - info->posY)
		* info->calc.deltaDistY;
	}
}

void	check_hit_wall(t_info *info)
{
	while (info->calc.hit == 0)
	{
		if (info->calc.sideDistX < info->calc.sideDistY)
		{
			info->calc.sideDistX += info->calc.deltaDistX;
			info->calc.mapX += info->calc.stepX;
			info->calc.side = 0;
		}
		else
		{
			info->calc.sideDistY += info->calc.deltaDistY;
			info->calc.mapY += info->calc.stepY;
			info->calc.side = 1;
		}
		if (info->worldMap[info->calc.mapX][info->calc.mapY] == '1')
			info->calc.hit = 1;
	}
}

void	get_clean_dist(t_info *info)
{
	if (info->calc.side == 0)
		info->calc.perpWallDist = (info->calc.mapX - info->posX
		+ (1 - info->calc.stepX) / 2) / info->calc.rayDirX;
	else
		info->calc.perpWallDist = (info->calc.mapY - info->posY
		+ (1 - info->calc.stepY) / 2) / info->calc.rayDirY;
}

void	get_pixel_destination(t_info *info)
{
	info->calc.lineHeight = (int)(info->height / info->calc.perpWallDist);
	info->calc.drawStart = (info->height / 2) - (info->calc.lineHeight / 2);
	if (info->calc.drawStart < 0)
		info->calc.drawStart = 0;
	info->calc.drawEnd = (info->height / 2) + (info->calc.lineHeight / 2);
	if (info->calc.drawEnd >= info->height)
		info->calc.drawEnd = info->height - 1;
}

void	get_wall_pos(t_info *info)
{
	if (info->worldMap[info->calc.mapX][info->calc.mapY] == '1')
		info->calc.color = 0xFF0000;
	if (info->worldMap[info->calc.mapX][info->calc.mapY] == '1')
		info->calc.texNum = 0;
	if (info->calc.side == 0)
	{
		info->calc.wallX = info->posY + info->calc.perpWallDist *
		info->calc.rayDirY;
	}
	else
	{
		info->calc.wallX = info->posX + info->calc.perpWallDist *
		info->calc.rayDirX;
	}
	info->calc.wallX -= floor((info->calc.wallX));
}
