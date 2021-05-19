/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_util2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kihkim <kihkim@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/20 01:34:11 by kihkim            #+#    #+#             */
/*   Updated: 2021/05/20 01:34:12 by kihkim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int		sep_c_f(char *line, t_info *info, int res)
{
	if (info->pas_info.def == 'C' || info->pas_info.def == 'F')
	{
		if (line[info->pas_info.i] == ',')
		{
			if (info->pas_info.i0 == 0)
			{
				info->pas_info.check = -1;
				res = 0;
			}
			info->pas_info.check++;
			info->pas_info.i0 = 0;
		}
	}
	return (res);
}

int		sep_r(char *line, t_info *info, int res)
{
	if (info->pas_info.def == 'R')
	{
		if (line[info->pas_info.i] == ' ')
		{
			info->pas_info.check = 1;
			info->pas_info.i0 = 0;
		}
		else if (line[info->pas_info.i] == ',')
		{
			info->pas_info.check = -1;
			res = 0;
		}
	}
	return (res);
}

int		put_letter2(char *line, t_info *info)
{
	int res;

	res = 1;
	if ((line[info->pas_info.i] >= 48 && line[info->pas_info.i] <= 57) == 1)
	{
		check_letter(info);
		put_letter(line, info);
	}
	res = sep_c_f(line, info, res);
	res = sep_r(line, info, res);
	return (res);
}

void	letter_to_info_cf(t_info *info)
{
	if (info->pas_info.def == 'C')
	{
		if (info->pas_info.check == 2 && info->pas_info.i0 != 0)
		{
			info->gnl_info.cc[0] = ft_atoi(info->pas_info.cc0);
			info->gnl_info.cc[1] = ft_atoi(info->pas_info.cc1);
			info->gnl_info.cc[2] = ft_atoi(info->pas_info.cc2);
		}
		else
			info->gnl_info.cc[0] = 777;
	}
	else if (info->pas_info.def == 'F')
	{
		if (info->pas_info.check == 2 && info->pas_info.i0 != 0)
		{
			info->gnl_info.ff[0] = ft_atoi(info->pas_info.ff0);
			info->gnl_info.ff[1] = ft_atoi(info->pas_info.ff1);
			info->gnl_info.ff[2] = ft_atoi(info->pas_info.ff2);
		}
		else
			info->gnl_info.ff[0] = 777;
	}
}

void	letter_to_info(t_info *info)
{
	letter_to_info_cf(info);
	if (info->pas_info.def == 'R')
	{
		if (info->pas_info.i0 != 0)
		{
			info->gnl_info.wid = ft_atoi(info->pas_info.wid);
			info->gnl_info.hei = ft_atoi(info->pas_info.hei);
		}
		else
			info->gnl_info.wid = 10000;
	}
}
