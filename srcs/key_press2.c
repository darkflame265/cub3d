/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_press2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kihkim <kihkim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/20 01:29:17 by kihkim            #+#    #+#             */
/*   Updated: 2021/05/25 15:49:17 by kihkim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	key_w_s(t_info *info)
{
	if (info->key_check[K_W] == 1)
	{
		if (info->world_map[(int)(info->pos_x +
		info->dir_x * info->move_speed)][(int)(info->pos_y)] != '1')
			info->pos_x += info->dir_x * info->move_speed;
		if (info->world_map[(int)(info->pos_x)][(int)(info->pos_y +
		info->dir_y * info->move_speed)] != '1')
			info->pos_y += info->dir_y * info->move_speed;
	}
	if (info->key_check[K_S] == 1)
	{
		if (info->world_map[(int)(info->pos_x -
		info->dir_x * info->move_speed)][(int)(info->pos_y)] != '1')
			info->pos_x -= info->dir_x * info->move_speed;
		if (info->world_map[(int)(info->pos_x)][(int)(info->pos_y -
		info->dir_y * info->move_speed)] != '1')
			info->pos_y -= info->dir_y * info->move_speed;
	}
}

void	key_d(t_info *info)
{
	double old_dir_x;
	double old_plane_x;

	old_dir_x = info->dir_x;
	old_plane_x = info->plane_x;
	if (info->key_check[K_D] == 1)
	{
		info->dir_x = info->dir_x * cos(-info->rot_speed) -
		info->dir_y * sin(-info->rot_speed);
		info->dir_y = old_dir_x * sin(-info->rot_speed) +
		info->dir_y * cos(-info->rot_speed);
		info->plane_x = info->plane_x * cos(-info->rot_speed) -
		info->plane_y * sin(-info->rot_speed);
		info->plane_y = old_plane_x * sin(-info->rot_speed) +
		info->plane_y * cos(-info->rot_speed);
	}
}

void	key_a(t_info *info)
{
	double old_dir_x;
	double old_plane_x;

	old_dir_x = info->dir_x;
	old_plane_x = info->plane_x;
	if (info->key_check[K_A] == 1)
	{
		info->dir_x = info->dir_x * cos(info->rot_speed) -
		info->dir_y * sin(info->rot_speed);
		info->dir_y = old_dir_x * sin(info->rot_speed) +
		info->dir_y * cos(info->rot_speed);
		info->plane_x = info->plane_x * cos(info->rot_speed) -
		info->plane_y * sin(info->rot_speed);
		info->plane_y = old_plane_x * sin(info->rot_speed) +
		info->plane_y * cos(info->rot_speed);
	}
}

int		press_exit_button(t_info *info)
{
	exit(0);
	return (0);
}

int		key_press(t_info *info)
{
	key_w_s(info);
	key_d(info);
	key_a(info);
	key_arrow(info);
	key_arrow2(info);
	if (info->key_check[K_ESC] == 1)
		exit(0);
	return (0);
}
