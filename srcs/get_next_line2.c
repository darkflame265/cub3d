/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kihkim <kihkim@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/19 21:29:06 by kihkim            #+#    #+#             */
/*   Updated: 2021/05/24 00:31:35 by kihkim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void		check_series(char *line, t_info *info)
{
	check_r(line, info);
	check_no(line, info);
	check_so(line, info);
	check_we(line, info);
	check_ea(line, info);
	check_sprite(line, info);
	check_ceiling_color(line, info);
	check_floor_color(line, info);
	check_map_size(line, info);
}

int			check_backup(int fd, char **line, char **backup)
{
	if (fd < 0 || !line || BUFFER_SIZE <= 0)
		return (-1);
	if (!(*backup = (char*)malloc(sizeof(char) * (BUFFER_SIZE + 1))))
		return (-1);
	return (0);
}
