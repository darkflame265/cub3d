/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kihkim <kihkim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/23 00:07:14 by kihkim            #+#    #+#             */
/*   Updated: 2021/05/25 14:23:35 by kihkim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	next_step(t_info *info)
{
	if (info->calc.raydir_x < 0)
	{
		info->calc.step_x = -1;
		info->calc.sd_dist_x = (info->pos_x - info->calc.map_x)
		* info->calc.dt_dist_x;
	}
	else
	{
		info->calc.step_x = 1;
		info->calc.sd_dist_x = (info->calc.map_x + 1.0 - info->pos_x)
		* info->calc.dt_dist_x;
	}
	if (info->calc.raydir_y < 0)
	{
		info->calc.step_y = -1;
		info->calc.sd_dist_y = (info->pos_y - info->calc.map_y)
		* info->calc.dt_dist_y;
	}
	else
	{
		info->calc.step_y = 1;
		info->calc.sd_dist_y = (info->calc.map_y + 1.0 - info->pos_y)
		* info->calc.dt_dist_y;
	}
}

void	check_hit_wall(t_info *info)
{
	while (info->calc.hit == 0)
	{
		if (info->calc.sd_dist_x < info->calc.sd_dist_y)
		{
			info->calc.sd_dist_x += info->calc.dt_dist_x;
			info->calc.map_x += info->calc.step_x;
			info->calc.side = 0;
		}
		else
		{
			info->calc.sd_dist_y += info->calc.dt_dist_y;
			info->calc.map_y += info->calc.step_y;
			info->calc.side = 1;
		}
		if (info->world_map[info->calc.map_x][info->calc.map_y] == '1')
			info->calc.hit = 1;
	}
}

void	get_clean_dist(t_info *info)
{
	if (info->calc.side == 0)
		info->calc.final_dist = (info->calc.map_x - info->pos_x
		+ (1 - info->calc.step_x) / 2) / info->calc.raydir_x;
	else
		info->calc.final_dist = (info->calc.map_y - info->pos_y
		+ (1 - info->calc.step_y) / 2) / info->calc.raydir_y;
}

void	get_pixel_destination(t_info *info)
{
	info->calc.line_hei = (int)(info->height / info->calc.final_dist);
	info->calc.draw_start = (info->height / 2) - (info->calc.line_hei / 2);
	if (info->calc.draw_start < 0)
		info->calc.draw_start = 0;
	info->calc.draw_end = (info->height / 2) + (info->calc.line_hei / 2);
	if (info->calc.draw_end >= info->height)
		info->calc.draw_end = info->height - 1;
}

void	get_wall_pos(t_info *info)
{
	if (info->world_map[info->calc.map_x][info->calc.map_y] == '1')
		info->calc.color = 0xFF0000;
	if (info->world_map[info->calc.map_x][info->calc.map_y] == '1')
		info->calc.tex_num = 0;
	if (info->calc.side == 0)
	{
		info->calc.wall_x = info->pos_y + info->calc.final_dist *
		info->calc.raydir_y;
	}
	else
	{
		info->calc.wall_x = info->pos_x + info->calc.final_dist *
		info->calc.raydir_x;
	}
	info->calc.wall_x -= floor((info->calc.wall_x));
}
