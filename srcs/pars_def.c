/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars_def.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kihkim <kihkim@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/20 01:14:56 by kihkim            #+#    #+#             */
/*   Updated: 2021/05/20 01:14:56 by kihkim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	def_cf(t_info *info)
{
	if (info->pas_info.check == 0)
	{
		if (info->pas_info.def == 'C')
			info->pas_info.letter = info->pas_info.cc0;
		else if (info->pas_info.def == 'F')
			info->pas_info.letter = info->pas_info.ff0;
	}
	else if (info->pas_info.check == 1)
	{
		if (info->pas_info.def == 'C')
			info->pas_info.letter = info->pas_info.cc1;
		else if (info->pas_info.def == 'F')
			info->pas_info.letter = info->pas_info.ff1;
	}
	else if (info->pas_info.check == 2)
	{
		if (info->pas_info.def == 'C')
			info->pas_info.letter = info->pas_info.cc2;
		else if (info->pas_info.def == 'F')
			info->pas_info.letter = info->pas_info.ff2;
	}
}

void	def_r(t_info *info)
{
	if (info->pas_info.def == 'R')
	{
		if (info->pas_info.check == 0)
			info->pas_info.letter = info->pas_info.wid;
		if (info->pas_info.check == 1)
			info->pas_info.letter = info->pas_info.hei;
	}
}
