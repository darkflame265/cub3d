/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kihkim <kihkim@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/19 22:17:29 by kihkim            #+#    #+#             */
/*   Updated: 2021/05/24 00:34:43 by kihkim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	set_north(t_info *info, int i, int j)
{
	if (info->world_map[i][j] == 'n' || info->world_map[i][j] == 'N')
	{
		info->pos_x = i + 0.5f;
		info->pos_y = j + 0.5f;
	}
}

void	set_east(t_info *info, int i, int j)
{
	int		z;
	double	old_dir_x;
	double	old_plane_x;
	double	cos_min;
	double	sin_min;

	cos_min = cos(-info->rot_speed);
	sin_min = sin(-info->rot_speed);
	z = 0;
	if (info->world_map[i][j] == 'e' || info->world_map[i][j] == 'E')
	{
		info->pos_x = i + 0.5f;
		info->pos_y = j + 0.5f;
		while (z < 30)
		{
			old_dir_x = info->dir_x;
			old_plane_x = info->plane_x;
			info->dir_x = info->dir_x * cos_min - info->dir_y * sin_min;
			info->dir_y = old_dir_x * sin_min + info->dir_y * cos_min;
			info->plane_x = info->plane_x * cos_min - info->plane_y * sin_min;
			info->plane_y = old_plane_x * sin_min + info->plane_y * cos_min;
			z++;
		}
	}
}

void	set_south(t_info *info, int i, int j)
{
	int		z;
	double	old_dir_x;
	double	old_plane_x;
	double	cos_plus;
	double	sin_plus;

	cos_plus = cos(info->rot_speed);
	sin_plus = sin(info->rot_speed);
	z = 0;
	if (info->world_map[i][j] == 's' || info->world_map[i][j] == 'S')
	{
		info->pos_x = i + 0.5f;
		info->pos_y = j + 0.5f;
		while (z < 60)
		{
			old_dir_x = info->dir_x;
			old_plane_x = info->plane_x;
			info->dir_x = info->dir_x * cos_plus - info->dir_y * sin_plus;
			info->dir_y = old_dir_x * sin_plus + info->dir_y * cos_plus;
			info->plane_x = info->plane_x * cos_plus - info->plane_y * sin_plus;
			info->plane_y = old_plane_x * sin_plus + info->plane_y * cos_plus;
			z++;
		}
	}
}

void	set_west(t_info *info, int i, int j)
{
	int		z;
	double	old_dir_x;
	double	old_plane_x;
	double	cos_plus;
	double	sin_plus;

	cos_plus = cos(info->rot_speed);
	sin_plus = sin(info->rot_speed);
	z = 0;
	if (info->world_map[i][j] == 'w' || info->world_map[i][j] == 'W')
	{
		info->pos_x = i + 0.5f;
		info->pos_y = j + 0.5f;
		while (z < 30)
		{
			old_dir_x = info->dir_x;
			old_plane_x = info->plane_x;
			info->dir_x = info->dir_x * cos_plus - info->dir_y * sin_plus;
			info->dir_y = old_dir_x * sin_plus + info->dir_y * cos_plus;
			info->plane_x = info->plane_x * cos_plus - info->plane_y * sin_plus;
			info->plane_y = old_plane_x * sin_plus + info->plane_y * cos_plus;
			z++;
		}
	}
}

void	set_sprite(t_info *info, int i, int j)
{
	if (info->world_map[i][j] == '2')
	{
		info->sprites[info->sprite_stack].x = i + 0.5;
		info->sprites[info->sprite_stack].y = j + 0.5;
		info->sprites[info->sprite_stack].texture = 8;
		info->sprite_stack++;
	}
}
