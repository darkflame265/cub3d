/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kihkim <kihkim@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/23 00:02:05 by kihkim            #+#    #+#             */
/*   Updated: 2021/05/23 00:51:22 by kihkim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	draw_ceil_floor(t_info *info, int x)
{
	int	z;

	z = 0;
	info->calc.color = (255 << 24);
	info->calc.color = info->calc.color | (info->gnl_info.cc[0] << 16);
	info->calc.color = info->calc.color | (info->gnl_info.cc[1] << 8);
	info->calc.color = info->calc.color | (info->gnl_info.cc[2] << 0);
	while (z <= info->calc.drawStart)
	{
		info->buf[z][x] = info->calc.color;
		z++;
	}
	info->calc.color = (255 << 24);
	info->calc.color = info->calc.color | (info->gnl_info.ff[0] << 16);
	info->calc.color = info->calc.color | (info->gnl_info.ff[1] << 8);
	info->calc.color = info->calc.color | (info->gnl_info.ff[2] << 0);
	z = info->calc.drawEnd;
	while (z <= info->height - 1)
	{
		info->buf[z][x] = info->calc.color;
		z++;
	}
}

void	init_calc_info(t_info *info, int x)
{
	info->calc.cameraX = 2 * x / (double)info->width - 1;
	info->calc.rayDirX = info->dirX + info->planeX * info->calc.cameraX;
	info->calc.rayDirY = info->dirY + info->planeY * info->calc.cameraX;
	info->calc.mapX = (int)info->posX;
	info->calc.mapY = (int)info->posY;
	info->calc.deltaDistX = fabs(1 / info->calc.rayDirX);
	info->calc.deltaDistY = fabs(1 / info->calc.rayDirY);
	info->calc.perpWallDist = 0;
	info->calc.stepX = 0;
	info->calc.stepY = 0;
	info->calc.hit = 0;
	info->calc.side = 0;
}

void	get_texture(t_info *info)
{
	info->calc.tex_x = (int)(info->calc.wallX * (double)texWidth);
	if (info->calc.side == 0 && info->calc.rayDirX > 0)
	{
		info->calc.tex_x = texWidth - info->calc.tex_x - 1;
		info->calc.texNum++;
	}
	if (info->calc.side == 1 && info->calc.rayDirY < 0)
	{
		info->calc.tex_x = texWidth - info->calc.tex_x - 1;
		info->calc.texNum += 3;
	}
	if (info->calc.side == 1 && info->calc.rayDirY > 0)
	{
		info->calc.texNum += 2;
	}
}

void	draw_wall(t_info *info, int x)
{
	int		tex_y;
	int		y;
	double	step;
	double	tex_pos;

	step = 1.0 * texHeight / info->calc.lineHeight;
	tex_pos = (info->calc.drawStart - info->height /
	2 + info->calc.lineHeight / 2) * step;
	y = info->calc.drawStart;
	while (y < info->calc.drawEnd)
	{
		tex_y = (int)tex_pos & (texHeight - 1);
		tex_pos += step;
		info->calc.color = info->texture[info->
		calc.texNum][texHeight * tex_y + info->calc.tex_x];
		info->buf[y][x] = info->calc.color;
		y++;
	}
}

void	calc(t_info *info)
{
	int	x;

	x = 0;
	while (x < info->width)
	{
		init_calc_info(info, x);
		next_step(info);
		check_hit_wall(info);
		get_clean_dist(info);
		get_pixel_destination(info);
		get_wall_pos(info);
		get_texture(info);
		draw_wall(info, x);
		info->zBuffer[x] = info->calc.perpWallDist;
		draw_ceil_floor(info, x);
		x++;
	}
	sprite_part(info);
}
