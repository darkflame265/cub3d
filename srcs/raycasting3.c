/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting3.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kihkim <kihkim@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/23 00:41:41 by kihkim            #+#    #+#             */
/*   Updated: 2021/05/24 00:35:37 by kihkim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void		set_sp_info(t_info *info, int i)
{
	info->sp_info.sp_x = info->sprites[info->sp_order[i]].x - info->pos_x;
	info->sp_info.sp_y = info->sprites[info->sp_order[i]].y - info->pos_y;
	info->sp_info.inv_det = 1.0 / (info->plane_x *
	info->dir_y - info->dir_x * info->plane_y);
	info->sp_info.form_x = info->sp_info.inv_det *
	(info->dir_y * info->sp_info.sp_x - info->dir_x * info->sp_info.sp_y);
	info->sp_info.form_y = info->sp_info.inv_det *
	(-info->plane_y * info->sp_info.sp_x + info->plane_x *
	info->sp_info.sp_y);
	info->sp_info.sp_screen_x = (int)((info->width / 2) *
	(1 + info->sp_info.form_x / info->sp_info.form_y));
	info->sp_info.vm_screen = (int)(VMOVE / info->sp_info.form_y);
	info->sp_info.sp_height = (int)fabs((info->height /
	info->sp_info.form_y) / VDIV);
	info->sp_info.draw_start_y = -info->sp_info.sp_height /
	2 + info->height / 2 + info->sp_info.vm_screen;
}

void		check_sp_pos(t_info *info)
{
	if (info->sp_info.draw_start_y < 0)
		info->sp_info.draw_start_y = 0;
	info->sp_info.draw_end_y = info->sp_info.sp_height /
	2 + info->height / 2 + info->sp_info.vm_screen;
	if (info->sp_info.draw_end_y >= info->height)
		info->sp_info.draw_end_y = info->height - 1;
	info->sp_info.sp_width = (int)fabs((info->height /
	info->sp_info.form_y) / UDIV);
	info->sp_info.draw_start_x = -info->sp_info.sp_width /
	2 + info->sp_info.sp_screen_x;
	if (info->sp_info.draw_start_x < 0)
		info->sp_info.draw_start_x = 0;
	info->sp_info.draw_end_x = info->sp_info.sp_width /
	2 + info->sp_info.sp_screen_x;
	if (info->sp_info.draw_end_x >= info->width)
		info->sp_info.draw_end_x = info->width - 1;
}

void		put_sp_pixel(t_info *info, int x, int y, int i)
{
	info->sp_info.d = (y - info->sp_info.vm_screen) * 256 - info->height *
	128 + info->sp_info.sp_height * 128;
	info->sp_info.tex_y = ((info->sp_info.d
	* info->tex[info->sprites[info->sp_order[i]].texture].tex_height) /
	info->sp_info.sp_height) / 256;
	info->sp_info.color = info->texture[info->sprites[info->
	sp_order[i]].texture][info->tex[info->sprites[info->
	sp_order[i]].texture].tex_width
	* info->sp_info.tex_y + info->sp_info.tex_x];
	if ((info->sp_info.color & 0x00FFFFFF) != 0)
		info->buf[y][x] = info->sp_info.color;
}

void		draw_sprite(t_info *info, int i)
{
	int x;
	int y;

	x = info->sp_info.draw_start_x;
	while (x < info->sp_info.draw_end_x)
	{
		y = info->sp_info.draw_start_y;
		info->sp_info.tex_x = (int)((256 * (x - (-info->sp_info.sp_width
		/ 2 + info->sp_info.sp_screen_x)) * info->
		tex[info->sprites[info->sp_order[i]].texture].tex_width
		/ info->sp_info.sp_width) / 256);
		if (info->sp_info.form_y > 0 && x > 0 && x < info->width && info->
		sp_info.form_y < info->z_buffer[x])
		{
			while (y < info->sp_info.draw_end_y)
			{
				put_sp_pixel(info, x, y, i);
				y++;
			}
		}
		x++;
	}
}

void		sprite_part(t_info *info)
{
	int i;

	i = 0;
	while (i < info->sprite_stack)
	{
		info->sp_order[i] = i;
		info->sp_dist[i] = dist(info->pos_x,
		info->pos_y, info->sprites[i].x, info->sprites[i].y);
		i++;
	}
	sort_sprites(info->sp_order, info->sp_dist, info->sprite_stack);
	i = 0;
	while (i < info->sprite_stack)
	{
		set_sp_info(info, i);
		check_sp_pos(info);
		draw_sprite(info, i);
		i++;
	}
}
