/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_variable.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kihkim <kihkim@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/19 22:43:15 by kihkim            #+#    #+#             */
/*   Updated: 2021/05/19 22:50:06 by kihkim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	init_basic(t_info *info)
{
	info->posX = 12;
	info->posY = 5;
	info->dirX = -1;
	info->dirY = 0;
	info->planeX = 0;
	info->planeY = 0.66;
	info->moveSpeed = 0.05;
	info->rotSpeed = 0.053;
	info->gnl_info.mw = 0;
	info->gnl_info.mh = 0;
	info->gnl_info.start_flag = 0;
	info->save_flag = 0;
	memory_clean(info);
}

void	init_buf(t_info *info)
{
	int i;
	int j;

	i = 0;
	info->width = info->gnl_info.wid;
	info->height = info->gnl_info.hei;
	info->buf = (int **)malloc(sizeof(int *) * info->height);
	while (i < info->height)
	{
		info->buf[i] = (int *)malloc(sizeof(int) * info->width);
		i++;
	}
	i = 0;
	j = 0;
	while (i < info->height)
	{
		j = 0;
		while (j < info->width)
		{
			info->buf[i][j] = 0;
			j++;
		}
		i++;
	}
	info->zBuffer = (double *)malloc(sizeof(double) * info->width);
}

void	init_texture(t_info *info)
{
	int i;
	int j;

	i = 0;
	info->texture = (int **)malloc(sizeof(int *) * 16);
	while (i < 16)
	{
		info->texture[i] = (int *)malloc(sizeof(int) * (texWidth * texHeight));
		i++;
	}
	i = 0;
	j = 0;
	while (i < 16)
	{
		j = 0;
		while (j < 16)
		{
			info->texture[i][j] = 0;
			j++;
		}
		i++;
	}
}
