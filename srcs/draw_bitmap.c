/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_bitmap.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kihkim <kihkim@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/20 00:24:22 by kihkim            #+#    #+#             */
/*   Updated: 2021/05/20 00:44:46 by kihkim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void			save_bmp(t_info *info)
{
	int				i;
	int				j;
	unsigned char	image[info->gnl_info.hei][info->gnl_info.wid][BP];

	i = 0;
	j = 0;
	set_bit_basic(info);
	while (i < info->gnl_info.hei)
	{
		j = 0;
		while (j < info->gnl_info.wid)
		{
			image[i][j][2] = (unsigned char)((info->buf
			[info->gnl_info.hei - i - 1][j] & info->bit_info.r) >> 16);
			image[i][j][1] = (unsigned char)((info->buf
			[info->gnl_info.hei - i - 1][j] & info->bit_info.g) >> 8);
			image[i][j][0] = (unsigned char)((info->buf
			[info->gnl_info.hei - i - 1][j] & info->bit_info.b) >> 0);
			j++;
		}
		i++;
	}
	generate_bitmap_image((unsigned char*)image, info);
	printf("Image generated!!\n");
}
