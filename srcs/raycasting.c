/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kihkim <kihkim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/23 00:02:05 by kihkim            #+#    #+#             */
/*   Updated: 2021/05/25 15:50:10 by kihkim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	draw_ceil_floor(t_info *info, int x)
{
	int	z;

	info->calc.color = (info->gnl_info.cc[0] << 16) |
	(info->gnl_info.cc[1] << 8) | (info->gnl_info.cc[2]);
	z = 0;
	while (z <= info->calc.draw_start)
	{
		info->buf[z][x] = info->calc.color;
		z++;
	}
	info->calc.color = (info->gnl_info.ff[0] << 16) |
	(info->gnl_info.ff[1] << 8) | (info->gnl_info.ff[2]);
	z = info->calc.draw_end;
	while (z <= info->height - 1)
	{
		info->buf[z][x] = info->calc.color;
		z++;
	}
}

void	init_calc_info(t_info *info, int x)
{
	info->calc.cam_x = 2 * x / (double)info->width - 1;
	info->calc.raydir_x = info->dir_x + info->plane_x * info->calc.cam_x;
	info->calc.raydir_y = info->dir_y + info->plane_y * info->calc.cam_x;
	info->calc.map_x = (int)info->pos_x;
	info->calc.map_y = (int)info->pos_y;
	info->calc.dt_dist_x = fabs(1 / info->calc.raydir_x);
	info->calc.dt_dist_y = fabs(1 / info->calc.raydir_y);
	info->calc.final_dist = 0;
	info->calc.step_x = 0;
	info->calc.step_y = 0;
	info->calc.hit = 0;
	info->calc.side = 0;
}

void	get_texture(t_info *info)
{
	info->calc.tex_x = (int)(info->calc.wall_x * (double)TEXWIDTH);
	if (info->calc.side == 0 && info->calc.raydir_x > 0)
	{
		info->calc.tex_x = TEXWIDTH - info->calc.tex_x - 1;
		info->calc.tex_num++;
	}
	if (info->calc.side == 1 && info->calc.raydir_y < 0)
	{
		info->calc.tex_x = TEXWIDTH - info->calc.tex_x - 1;
		info->calc.tex_num += 3;
	}
	if (info->calc.side == 1 && info->calc.raydir_y > 0)
	{
		info->calc.tex_num += 2;
	}
}

void	draw_wall(t_info *info, int x)
{
	int		tex_y;
	int		y;
	double	step;
	double	tex_pos;

	step = 1.0 * TEXHEIGHT / info->calc.line_hei;
	tex_pos = (info->calc.draw_start - info->height /
	2 + info->calc.line_hei / 2) * step;
	y = info->calc.draw_start;
	while (y < info->calc.draw_end)
	{
		tex_y = (int)tex_pos & (TEXHEIGHT - 1);
		tex_pos += step;
		info->calc.color = info->texture[info->
		calc.tex_num][TEXHEIGHT * tex_y + info->calc.tex_x];
		info->buf[y][x] = info->calc.color;
		y++;
	}
}

void	calc(t_info *info)
{
	int	x;

	x = 0;
	while (x < info->gnl_info.wid)
	{
		init_calc_info(info, x);
		next_step(info);
		check_hit_wall(info);
		get_clean_dist(info);
		get_pixel_destination(info);
		get_wall_pos(info);
		get_texture(info);
		draw_wall(info, x);
		info->z_buffer[x] = info->calc.final_dist;
		draw_ceil_floor(info, x);
		x++;
	}
	sprite_part(info);
}
