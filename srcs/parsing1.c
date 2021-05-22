/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing1.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kihkim <kihkim@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/20 00:55:36 by kihkim            #+#    #+#             */
/*   Updated: 2021/05/23 01:43:17 by kihkim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void		check_r_def(char *line, t_info *info)
{
	while (line[info->pas_info.i] == ' ')
		info->pas_info.i++;
	if (line[info->pas_info.i] == 'R' && line[info->pas_info.i + 1] == ' ')
	{
		info->pas_info.level = 1;
		info->pas_info.i = info->pas_info.i + 2;
		info->pas_info.def = 'R';
	}
	while (line[info->pas_info.i] == ' ')
		info->pas_info.i++;
}

void		check_defi(char *line, t_info *info, char c1, char c2)
{
	while (line[info->pas_info.i] == ' ')
		info->pas_info.i++;
	if (line[info->pas_info.i] == c1 && line[info->pas_info.i + 1] == c2)
	{
		info->pas_info.level = 1;
		info->pas_info.i = info->pas_info.i + 2;
	}
	while (line[info->pas_info.i] == ' ')
		info->pas_info.i++;
}

// 해상도가 600 600 600 3개여도 정상작동 되는 버그.
void		check_r(char *line, t_info *info)
{
	char	wid[50];
	char	hei[50];

	info->pas_info.i = 0;
	info->pas_info.level = 0;
	info->pas_info.check = 0;
	info->pas_info.i0 = 0;
	info->pas_info.def = 0;
	check_r_def(line, info);
	while (info->pas_info.level == 1 && line[info->pas_info.i] != '\0')
	{
		if (check_valid_word(line, info->pas_info.i) == -1)
		{
			info->pas_info.check = -1;
			break ;
		}
		if (put_letter2(line, info) == 0)
			break ;
		info->pas_info.i++;
	}
	if (info->pas_info.level == 1)
		letter_to_info(info);
}
