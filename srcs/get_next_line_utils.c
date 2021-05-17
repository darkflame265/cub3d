/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kihkim <kihkim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/15 19:23:10 by kihkim            #+#    #+#             */
/*   Updated: 2020/10/19 18:05:59 by kihkim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

size_t		ft_strlen(const char *str)
{
	int		count;

	count = 0;
	if (!str)
		return (0);
	while (str[count] != '\0')
		count++;
	return (count);
}

void		*ft_memmove(void *dest, const void *src, size_t count)
{
	void	*original_dest;

	if (dest == src || count == 0)
		return (dest);
	original_dest = dest;
	if (dest < src)
	{
		while (count--)
			*(unsigned char*)dest++ = *(unsigned char*)src++;
	}
	else
	{
		dest += count;
		src += count;
		while (count--)
			*(unsigned char*)--dest = *(unsigned char*)--src;
	}
	return (original_dest);
}

char		*ft_strdup(const char *s1)
{
	char	*result;
	int		i;

	i = ft_strlen(s1);
	result = (char *)malloc(sizeof(char) * (i + 1));
	if (!result)
		return (0);
	i = 0;
	while (s1[i])
	{
		result[i] = s1[i];
		i++;
	}
	result[i] = '\0';
	return (result);
}

char		*ft_strjoin(char const *s1, char const *s2)
{
	char	*str;
	size_t	i;
	size_t	j;

	if (!s1 && !s2)
		return (0);
	// if (!(s1) || !(s2))
	// 	return ((s1) < (s2) ? ft_strdup(s2) : ft_strdup(s1));
	if (!(str = malloc(sizeof(*s1) * (ft_strlen(s1) + ft_strlen(s2) + 1))))
		return (0);
	i = 0;
	j = 0;
	while (s1[i])
		str[j++] = s1[i++];
	i = 0;
	while (s2[i])
		str[j++] = s2[i++];
	str[j] = '\0';
	free((char *)s1);
	return (str);
}

int			check_str_has_n(char *str)
{
	int i;

	i = 0;
	if (!str)
		return (0);
	while (str[i])
	{
		if (str[i] == '\n')
			return (1);
		i++;
	}
	return (0);
}
