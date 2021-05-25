/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_press.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kihkim <kihkim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/20 01:24:56 by kihkim            #+#    #+#             */
/*   Updated: 2021/05/25 15:49:39 by kihkim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int		button_down(int keycode, t_info *info)
{
	if (keycode < 65536)
		info->key_check[keycode] = 1;
	return (0);
}

int		button_release(int keycode, t_info *info)
{
	if (keycode < 65536)
		info->key_check[keycode] = 0;
	return (0);
}

void	key_arrow(t_info *info)
{
	double old_dir_x;
	double old_plane_x;

	old_dir_x = info->dir_x;
	old_plane_x = info->plane_x;
	if (info->key_check[KEY_LEFT_ARROW] == 1)
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

void	key_arrow2(t_info *info)
{
	double old_dir_x;
	double old_plane_x;

	old_dir_x = info->dir_x;
	old_plane_x = info->plane_x;
	if (info->key_check[KEY_RIGHT_ARROW] == 1)
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
