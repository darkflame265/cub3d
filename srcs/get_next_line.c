/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kihkim <kihkim@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/19 21:32:18 by kihkim            #+#    #+#             */
/*   Updated: 2021/05/24 00:33:30 by kihkim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

static char		*get_str(char *str)
{
	char			*rts;
	int				i;

	i = 0;
	if (!str)
		return (0);
	while (str[i] && str[i] != '\n')
		i++;
	if (!(rts = malloc(sizeof(char) * (i + 1))))
		return (0);
	i = 0;
	while (str[i] && str[i] != '\n')
	{
		rts[i] = str[i];
		i++;
	}
	rts[i] = '\0';
	return (rts);
}

static char		*get_str_next_str(char *str)
{
	char			*rts;
	int				i;
	int				j;

	i = 0;
	j = 0;
	if (!str)
		return (0);
	while (str[i] && str[i] != '\n')
		i++;
	if (!str[i])
	{
		free(str);
		return (0);
	}
	if (!(rts = malloc(sizeof(char) * ((ft_strlen(str) - i) + 1))))
		return (0);
	i++;
	while (str[i])
		rts[j++] = str[i++];
	rts[j] = '\0';
	free(str);
	return (rts);
}

int				super(int text_length, char **next_adrs, int fd, char *backup)
{
	backup[text_length] = '\0';
	if (*next_adrs == NULL)
		*next_adrs = (char*)ft_strdup(backup);
	else
		*next_adrs = (char*)ft_strjoin(*next_adrs, backup);
	if (check_str_has_n(*next_adrs) == 1 || text_length == 0)
		return (0);
	return (1);
}

int				get_next_line(int fd, char **line, t_info *info)
{
	char			*backup;
	static char		*next_adrs;
	int				text_length;

	text_length = 1;
	if (check_backup(fd, line, &backup) == -1)
		return (-1);
	while (check_str_has_n(next_adrs) == 0 &&
	(text_length = read(fd, backup, BUFFER_SIZE)) >= 0)
	{
		if (super(text_length, &next_adrs, fd, backup) == 0)
			break ;
	}
	free(backup);
	if (text_length == -1 || text_length == 0)
		return (text_length);
	*line = get_str(next_adrs);
	check_series(*line, info);
	next_adrs = get_str_next_str(next_adrs);
	return (1);
}
