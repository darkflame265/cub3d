/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_image.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kihkim <kihkim@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/19 22:50:34 by kihkim            #+#    #+#             */
/*   Updated: 2021/05/23 02:01:09 by kihkim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	input_image_data(t_info *info, char *path, t_img *img)
{
	img->img = mlx_xpm_file_to_image(info->mlx, path,
	&img->img_width, &img->img_height);
	img->data = (int *)mlx_get_data_addr(img->img, &img->bpp,
	&img->size_l, &img->endian);
}

void	load_image(t_info *info, char *path, t_img *img, int tex_num)
{
	int y;
	int x;

	y = 0;
	x = 0;
	input_image_data(info, path, img);
	info->tex[tex_num].tex_width = img->img_width;
	info->tex[tex_num].tex_height = img->img_height;
	if (img->img_width != texWidth || img->img_height != texHeight)
	{
		info->texture[tex_num] = realloc(info->texture[tex_num],
		(sizeof(int) * (img->img_width * img->img_height)));
	}
	while (y < img->img_height)
	{
		x = 0;
		while (x < img->img_width)
		{
			info->texture[tex_num][img->img_width * y + x] =
			img->data[img->img_width * y + x];
			x++;
		}
		y++;
	}
	mlx_destroy_image(info->mlx, img->img);
}

void	load_texture(t_info *info)
{
	t_img	img;

	load_image(info, info->gnl_info.path_no, &img, 0);
	load_image(info, info->gnl_info.path_so, &img, 1);
	load_image(info, info->gnl_info.path_ea, &img, 2);
	load_image(info, info->gnl_info.path_we, &img, 3);
	load_image(info, info->gnl_info.path_sp, &img, 8);
	load_image(info, "pics/enemy.xpm", &img, 9);
	load_image(info, "pics/barrel.xpm", &img, 10);
}
