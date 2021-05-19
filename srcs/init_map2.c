/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_map2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kihkim <kihkim@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/19 22:10:11 by kihkim            #+#    #+#             */
/*   Updated: 2021/05/19 22:41:21 by kihkim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	set_map_size(t_info *info)
{
	int i;

	i = 0;
	info->worldMap = (char **)malloc(sizeof(char *) * info->gnl_info.mh);
	while (i < info->gnl_info.mh)
	{
		info->worldMap[i] = (char *)malloc(sizeof(char) * info->gnl_info.mw);
		i++;
	}
}

void	init_map(t_info *info)
{
	int i;
	int j;

	info->sprite_stack = 0;
	i = 0;
	j = 0;
	set_map_size(info);
	while (i < info->gnl_info.mh)
	{
		j = 0;
		while (j < info->gnl_info.mw)
		{
			if (info->gnl_info.temp_map[i][j] == '\0')
				break ;
			info->worldMap[i][j] = info->gnl_info.temp_map[i][j];
			set_east(info, i, j);
			set_north(info, i, j);
			set_south(info, i, j);
			set_west(info, i, j);
			set_sprite(info, i, j);
			j++;
		}
		i++;
	}
}
