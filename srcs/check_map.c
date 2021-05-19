/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kihkim <kihkim@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/17 21:09:33 by kihkim            #+#    #+#             */
/*   Updated: 2021/05/19 22:42:46 by kihkim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	check_map_line(char *line, t_info *info)
{
	int stack;

	stack = 0;
	info->i = 0;
	while (line[info->i] != '\0')
	{
		if (line[info->i] != '0' && line[info->i] != '1' && line[info->i] != '2'
		&& line[info->i] != ' ' && line[info->i] != 'W' && line[info->i] != 'E'
		&& line[info->i] != 'S' && line[info->i] != 'N' &&
		line[info->i] != '\0' && line[info->i] != 'z')
		{
			info->gnl_info.fail_flag = 1;
		}
		info->i++;
	}
	info->i = 0;
	while (line[info->i] != '\0')
	{
		if (line[info->i] == ' ')
			stack++;
		info->i++;
	}
	if (stack == info->i)
		info->gnl_info.fail_flag = 1;
}

void	check_map_size(char *line, t_info *info)
{
	info->i = 0;
	info->gnl_info.fail_flag = 0;
	check_map_line(line, info);
	if (info->gnl_info.fail_flag == 0)
	{
		while (line[info->i] != '\0')
			info->i++;
		info->gnl_info.start_flag = 1;
		if (info->gnl_info.mw < info->i)
			info->gnl_info.mw = info->i;
	}
	if (info->gnl_info.fail_flag == 0)
	{
		info->i = 0;
		while (line[info->i] != '\0')
		{
			info->gnl_info.temp_map[info->gnl_info.mh][info->i] = line[info->i];
			info->gnl_info.mw2[info->gnl_info.mh]++;
			info->i++;
		}
		info->gnl_info.temp_map[info->gnl_info.mh][info->i] = line[info->i];
		info->gnl_info.mh++;
	}
}

int		check_aroung_algo(t_info *info, int i, int j)
{
	if ((info->gnl_info.temp_map[i - 1][j] == ' ' ||
	info->gnl_info.temp_map[i - 1][j] == 0) ||
	(info->gnl_info.temp_map[i + 1][j] == ' ' ||
	info->gnl_info.temp_map[i + 1][j] == 0) ||
	(info->gnl_info.temp_map[i][j + 1] == ' ' ||
	info->gnl_info.temp_map[i][j + 1] == 0) ||
	(info->gnl_info.temp_map[i][j - 1] == ' ' ||
	info->gnl_info.temp_map[i][j - 1] == 0))
	{
		info->gnl_info.error_x = i;
		info->gnl_info.error_y = j;
		return (0);
	}
	return (1);
}

int		check_map_is_safe(t_info *info)
{
	int i;
	int j;

	i = 0;
	j = 0;
	while (i < info->gnl_info.mh)
	{
		j = 0;
		while (j < info->gnl_info.mw2[i])
		{
			if (info->gnl_info.temp_map[i][j] != '1' &&
			info->gnl_info.temp_map[i][j] != ' ' &&
			info->gnl_info.temp_map[i][j] != 0)
			{
				if (check_aroung_algo(info, i, j) == 0)
					return (0);
			}
			j++;
		}
		i++;
	}
	return (1);
}
