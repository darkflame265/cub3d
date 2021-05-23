/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_util.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kihkim <kihkim@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/20 01:15:32 by kihkim            #+#    #+#             */
/*   Updated: 2021/05/23 23:15:10 by kihkim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int		check_valid_word(char *line, int i)
{
	if (line[i] != ' ')
	{
		if (line[i] != ',')
		{
			if (line[i] < 48 || line[i] > 57)
			{
				return (-1);
			}
		}
	}
	return (0);
}

void	check_def(char *line, t_info *info, char c)
{
	while (line[info->pas_info.i] == ' ')
		info->pas_info.i++;
	if (line[info->pas_info.i] == c && line[info->pas_info.i + 1] == ' ')
	{
		info->pas_info.level = 1;
		info->pas_info.i = info->pas_info.i + 2;
		info->pas_info.def = c;
	}
	else if (line[info->pas_info.i] == c && line[info->pas_info.i + 1] == '\0')
	{
		if (c == 'C')
			info->gnl_info.cc[0] = 777;
		if (c == 'F')
			info->gnl_info.ff[0] = 777;
	}
}

void	check_letter(t_info *info)
{
	def_cf(info);
	def_r(info);
}

void	put_letter(char *line, t_info *info)
{
	info->pas_info.letter[info->pas_info.i0] = line[info->pas_info.i];
	info->pas_info.i0++;
	if ((line[info->pas_info.i] >= 48 && line[info->pas_info.i] <= 57) == 0)
	{
		info->pas_info.letter[info->pas_info.i0] = '\0';
	}
}
