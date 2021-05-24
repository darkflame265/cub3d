/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_press.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kihkim <kihkim@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/20 01:24:56 by kihkim            #+#    #+#             */
/*   Updated: 2021/05/24 21:40:09 by kihkim           ###   ########.fr       */
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
	if (info->key_check[KEY_LEFT_ARROW] == 1)
	{
		if (info->world_map[(int)(info->pos_x +
		info->dir_x * info->move_speed)][(int)(info->pos_y)] != '1')
			info->pos_x -= info->dir_y * info->move_speed;
		if (info->world_map[(int)(info->pos_x)][(int)(info->pos_y +
		info->dir_y * info->move_speed)] != '1')
			info->pos_y -= info->dir_x * info->move_speed;
	}
	if (info->key_check[KEY_RIGHT_ARROW] == 1)
	{
		if (info->world_map[(int)(info->pos_x -
		info->dir_x * info->move_speed)][(int)(info->pos_y)] != '1')
			info->pos_x += info->dir_y * info->move_speed;
		if (info->world_map[(int)(info->pos_x)][(int)(info->pos_y -
		info->dir_y * info->move_speed)] != '1')
			info->pos_y += info->dir_x * info->move_speed;
	}
}
