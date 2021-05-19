/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kihkim <kihkim@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/19 22:17:29 by kihkim            #+#    #+#             */
/*   Updated: 2021/05/19 22:20:07 by kihkim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	set_north(t_info *info, int i, int j)
{
	if (info->worldMap[i][j] == 'n' || info->worldMap[i][j] == 'N')
	{
		info->posX = i + 0.5f;
		info->posY = j + 0.5f;
	}
}

void	set_east(t_info *info, int i, int j)
{
	int		z;
	double	old_dir_x;
	double	old_plane_x;
	double	cos_minus;
	double	sin_minus;

	cos_minus = cos(-info->rotSpeed);
	sin_minus = sin(-info->rotSpeed);
	z = 0;
	if (info->worldMap[i][j] == 'e' || info->worldMap[i][j] == 'E')
	{
		info->posX = i + 0.5f;
		info->posY = j + 0.5f;
		while (z < 30)
		{
			old_dir_x = info->dirX;
			old_plane_x = info->planeX;
			info->dirX = info->dirX * cos_minus - info->dirY * sin_minus;
			info->dirY = old_dir_x * sin_minus + info->dirY * cos_minus;
			info->planeX = info->planeX * cos_minus - info->planeY * sin_minus;
			info->planeY = old_plane_x * sin_minus + info->planeY * cos_minus;
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

	cos_plus = cos(info->rotSpeed);
	sin_plus = sin(info->rotSpeed);
	z = 0;
	if (info->worldMap[i][j] == 's' || info->worldMap[i][j] == 'S')
	{
		info->posX = i + 0.5f;
		info->posY = j + 0.5f;
		while (z < 60)
		{
			old_dir_x = info->dirX;
			old_plane_x = info->planeX;
			info->dirX = info->dirX * cos_plus - info->dirY * sin_plus;
			info->dirY = old_dir_x * sin_plus + info->dirY * cos_plus;
			info->planeX = info->planeX * cos_plus - info->planeY * sin_plus;
			info->planeY = old_plane_x * sin_plus + info->planeY * cos_plus;
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

	cos_plus = cos(info->rotSpeed);
	sin_plus = sin(info->rotSpeed);
	z = 0;
	if (info->worldMap[i][j] == 'w' || info->worldMap[i][j] == 'W')
	{
		info->posX = i + 0.5f;
		info->posY = j + 0.5f;
		while (z < 30)
		{
			old_dir_x = info->dirX;
			old_plane_x = info->planeX;
			info->dirX = info->dirX * cos_plus - info->dirY * sin_plus;
			info->dirY = old_dir_x * sin_plus + info->dirY * cos_plus;
			info->planeX = info->planeX * cos_plus - info->planeY * sin_plus;
			info->planeY = old_plane_x * sin_plus + info->planeY * cos_plus;
			z++;
		}
	}
}

void	set_sprite(t_info *info, int i, int j)
{
	if (info->worldMap[i][j] == '2')
	{
		sprite[info->sprite_stack].x = i + 0.5;
		sprite[info->sprite_stack].y = j + 0.5;
		sprite[info->sprite_stack].texture = 8;
		info->sprite_stack++;
	}
}
