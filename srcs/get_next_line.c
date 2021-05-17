/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kihkim <kihkim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/15 18:03:38 by kihkim            #+#    #+#             */
/*   Updated: 2020/11/16 17:38:03 by kihkim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

static char		*get_str(char *str)
{
	char	*rts;
	int		i;

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
	char	*rts;
	int		i;
	int		j;

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

int			get_next_line(int fd, char **line, t_info *info)
{
	char		*backup;
	static char	*next_adrs;
	int			text_length;

	text_length = 1;
	if (fd < 0 || !line || BUFFER_SIZE <= 0)
		return (-1);
	if (!(backup = malloc(sizeof(char) * (BUFFER_SIZE + 1))))
		return (-1);
	while (check_str_has_n(next_adrs) == 0 &&
	(text_length = read(fd, backup, BUFFER_SIZE)) >= 0)
	{
		backup[text_length] = '\0';
		if (next_adrs == NULL)
			next_adrs = ft_strdup(backup);
		else
			next_adrs = ft_strjoin(next_adrs, backup);
		if (check_str_has_n(next_adrs) == 1 || text_length == 0)
			break;
	}
	free(backup);
	if (text_length == -1)
		return (-1);
	*line = get_str(next_adrs);

	check_r(*line, info);
	check_no(*line, info);
	check_so(*line, info);
	check_we(*line, info);
	check_ea(*line, info);
	check_sprite(*line, info);

	check_ceiling_color(*line, info);
	check_floor_color(*line, info);

	check_map_size(*line, text_length, info);




	next_adrs = get_str_next_str(next_adrs);
	if (text_length == 0)
		return (0);
	return (1);
	//return (output(next_adrs, line, text_length));
}
