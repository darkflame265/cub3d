/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_file.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kihkim <kihkim@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/17 19:15:30 by kihkim            #+#    #+#             */
/*   Updated: 2021/05/24 21:25:36 by kihkim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	error_pt(t_info *info, char *path, char *message)
{
	if (access(path, 0) < 0)
	{
		printf("%s\n", message);
		info->error_flag = 1;
	}
}

int		check_src_file(t_info *info)
{
	info->error_flag = 0;
	error_pt(info, info->gnl_info.path_no, "[ERROR] Can't find NO file.");
	error_pt(info, info->gnl_info.path_so, "[ERROR] Can't find SO file.");
	error_pt(info, info->gnl_info.path_we, "[ERROR] Can't find WE file.");
	error_pt(info, info->gnl_info.path_ea, "[ERROR] Can't find EA file.");
	error_pt(info, info->gnl_info.path_sp, "[ERROR] Can't find SP file.");
	if (info->error_flag == 1)
		return (0);
	else
		return (1);
}

int		check_r_value(t_info *info)
{
	int max_x;
	int max_y;

	mlx_get_screen_size(info->mlx, &max_x, &max_y);
	if (info->gnl_info.wid == 0 || info->gnl_info.hei == 0)
	{
		printf("[ERROR] Resolution Value is 0 or blank.\n");
		return (0);
	}
	if (info->gnl_info.wid > max_x || info->gnl_info.hei > max_y)
	{
		printf("[WARNING] Set Resolution is too big.\n");
		info->gnl_info.wid = max_x;
		info->gnl_info.hei = max_y;
		return (1);
	}
	return (1);
}

int		check_cf_value(t_info *info)
{
	int i;

	i = 0;
	while (i < 3)
	{
		if (info->gnl_info.cc[i] < 0 || info->gnl_info.cc[i] > 255)
		{
			printf("[ERROR] Ceiling Color Value is uncorrect.\n");
			return (0);
		}
		if (info->gnl_info.ff[i] < 0 || info->gnl_info.ff[i] > 255)
		{
			printf("[ERROR] Floor Color Value is uncorrect.\n");
			return (0);
		}
		i++;
	}
	return (1);
}

int		check_value(t_info *info)
{
	int x;
	int y;

	if (check_r_value(info) == 0)
		return (0);
	else if (check_cf_value(info) == 0)
		return (0);
	else if (check_map_is_safe(info) == 0)
	{
		x = info->gnl_info.error_x;
		y = info->gnl_info.error_y;
		printf("[ERROR]MAP IS FAIL.[%d][%d]\n", x, y);
		return (0);
	}
	return (1);
}
