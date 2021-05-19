/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memory_clean.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kihkim <kihkim@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/19 21:33:16 by kihkim            #+#    #+#             */
/*   Updated: 2021/05/19 22:28:20 by kihkim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	init_temp_map(t_info *info)
{
	int i;
	int j;

	i = 0;
	j = 0;
	while (i < 1000)
	{
		info->gnl_info.mw2[i] = 0;
		j = 0;
		while (j < 1000)
		{
			info->gnl_info.temp_map[i][j] = 0;
			j++;
		}
		i++;
	}
}

void	init_temp_key(t_info *info)
{
	int i;

	i = 0;
	while (i < 65536)
	{
		info->key_check[i] = 0;
		i++;
	}
}

void	init_temp_wid_hei(t_info *info)
{
	int i;

	i = 0;
	while (i < 50)
	{
		info->pas_info.wid[i] = 0;
		info->pas_info.hei[i] = 0;
		i++;
	}
}

void	init_temp_cf(t_info *info)
{
	int i;

	i = 0;
	while (i < 100)
	{
		info->pas_info.cc0[i] = 0;
		info->pas_info.cc1[i] = 0;
		info->pas_info.cc2[i] = 0;
		info->pas_info.ff0[i] = 0;
		info->pas_info.ff1[i] = 0;
		info->pas_info.ff2[i] = 0;
		i++;
	}
}

void	memory_clean(t_info *info)
{
	init_temp_cf(info);
	init_temp_wid_hei(info);
	init_temp_map(info);
	init_temp_key(info);
}
