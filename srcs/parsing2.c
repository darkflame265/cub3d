/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kihkim <kihkim@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/20 01:14:10 by kihkim            #+#    #+#             */
/*   Updated: 2021/05/20 01:14:33 by kihkim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void		check_no(char *line, t_info *info)
{
	char	no[100];
	int		result_index;

	info->pas_info.i = 0;
	result_index = 0;
	info->pas_info.level = 0;
	check_defi(line, info, 'N', 'O');
	if (info->pas_info.level == 1 && line[info->pas_info.i] != ' ')
	{
		while ((line[info->pas_info.i] != '\0'))
			no[result_index++] = line[info->pas_info.i++];
		no[result_index++] = '\0';
		info->gnl_info.path_no = malloc(sizeof(char) * result_index);
		info->pas_info.i = 0;
		while (info->pas_info.i < result_index)
		{
			info->gnl_info.path_no[info->pas_info.i] = no[info->pas_info.i];
			info->pas_info.i++;
		}
	}
}

void		check_so(char *line, t_info *info)
{
	char	so[100];
	int		result_index;

	result_index = 0;
	info->pas_info.i = 0;
	info->pas_info.level = 0;
	check_defi(line, info, 'S', 'O');
	if (info->pas_info.level == 1 && line[info->pas_info.i] != ' ')
	{
		while ((line[info->pas_info.i] != '\0'))
			so[result_index++] = line[info->pas_info.i++];
		so[result_index++] = '\0';
		info->gnl_info.path_so = malloc(sizeof(char) * result_index);
		info->pas_info.i = 0;
		while (info->pas_info.i < result_index)
		{
			info->gnl_info.path_so[info->pas_info.i] = so[info->pas_info.i];
			info->pas_info.i++;
		}
	}
}

void		check_we(char *line, t_info *info)
{
	char	we[100];
	int		result_index;

	info->pas_info.level = 0;
	result_index = 0;
	info->pas_info.i = 0;
	check_defi(line, info, 'W', 'E');
	if (info->pas_info.level == 1 && line[info->pas_info.i] != ' ')
	{
		while ((line[info->pas_info.i] != '\0'))
			we[result_index++] = line[info->pas_info.i++];
		we[result_index++] = '\0';
		info->gnl_info.path_we = malloc(sizeof(char) * result_index);
		info->pas_info.i = 0;
		while (info->pas_info.i < result_index)
		{
			info->gnl_info.path_we[info->pas_info.i] = we[info->pas_info.i];
			info->pas_info.i++;
		}
	}
}

void		check_ea(char *line, t_info *info)
{
	char	ea[100];
	int		result_index;

	result_index = 0;
	info->pas_info.i = 0;
	info->pas_info.level = 0;
	check_defi(line, info, 'E', 'A');
	if (info->pas_info.level == 1 && line[info->pas_info.i] != ' ')
	{
		while ((line[info->pas_info.i] != '\0'))
			ea[result_index++] = line[info->pas_info.i++];
		ea[result_index++] = '\0';
		info->gnl_info.path_ea = malloc(sizeof(char) * result_index);
		info->pas_info.i = 0;
		while (info->pas_info.i < result_index)
		{
			info->gnl_info.path_ea[info->pas_info.i] = ea[info->pas_info.i];
			info->pas_info.i++;
		}
	}
}

void		check_sprite(char *line, t_info *info)
{
	char	sprite[100];
	int		result_index;

	info->pas_info.level = 0;
	result_index = 0;
	info->pas_info.i = 0;
	check_defi(line, info, 'S', ' ');
	if (info->pas_info.level == 1 && line[info->pas_info.i] != ' ')
	{
		while ((line[info->pas_info.i] != '\0'))
			sprite[result_index++] = line[info->pas_info.i++];
		sprite[result_index++] = '\0';
		info->gnl_info.path_sprite = malloc(sizeof(char) * result_index);
		info->pas_info.i = 0;
		while (info->pas_info.i < result_index)
		{
			info->gnl_info.path_sprite[info->pas_info.i] =
			sprite[info->pas_info.i];
			info->pas_info.i++;
		}
	}
}
