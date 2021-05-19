/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars_ceil_floor.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kihkim <kihkim@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/20 01:16:03 by kihkim            #+#    #+#             */
/*   Updated: 2021/05/20 01:16:04 by kihkim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void		check_ceiling_color(char *line, t_info *info)
{
	info->pas_info.i = 0;
	info->pas_info.level = 0;
	info->pas_info.check = 0;
	info->pas_info.i0 = 0;
	info->pas_info.def = 0;
	check_def(line, info, 'C');
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

void		check_floor_color(char *line, t_info *info)
{
	info->pas_info.i = 0;
	info->pas_info.level = 0;
	info->pas_info.check = 0;
	info->pas_info.i0 = 0;
	info->pas_info.def = 0;
	check_def(line, info, 'F');
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
