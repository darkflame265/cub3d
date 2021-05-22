/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting3.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kihkim <kihkim@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/23 00:41:41 by kihkim            #+#    #+#             */
/*   Updated: 2021/05/23 00:42:13 by kihkim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void		set_sp_info(t_info *info, int i)
{
	info->sp_info.spriteX = sprite[spriteOrder[i]].x - info->posX;
	info->sp_info.spriteY = sprite[spriteOrder[i]].y - info->posY;
	info->sp_info.invDet = 1.0 / (info->planeX *
	info->dirY - info->dirX * info->planeY);
	info->sp_info.transformX = info->sp_info.invDet *
	(info->dirY * info->sp_info.spriteX - info->dirX * info->sp_info.spriteY);
	info->sp_info.transformY = info->sp_info.invDet *
	(-info->planeY * info->sp_info.spriteX + info->planeX *
	info->sp_info.spriteY);
	info->sp_info.spriteScreenX = (int)((info->width / 2) *
	(1 + info->sp_info.transformX / info->sp_info.transformY));
	info->sp_info.vMoveScreen = (int)(vMove / info->sp_info.transformY);
	info->sp_info.spriteHeight = (int)fabs((info->height /
	info->sp_info.transformY) / vDiv);
	info->sp_info.drawStartY = -info->sp_info.spriteHeight /
	2 + info->height / 2 + info->sp_info.vMoveScreen;
}

void		check_sp_pos(t_info *info)
{
	if (info->sp_info.drawStartY < 0)
		info->sp_info.drawStartY = 0;
	info->sp_info.drawEndY = info->sp_info.spriteHeight /
	2 + info->height / 2 + info->sp_info.vMoveScreen;
	if (info->sp_info.drawEndY >= info->height)
		info->sp_info.drawEndY = info->height - 1;
	info->sp_info.spriteWidth = (int)fabs((info->height /
	info->sp_info.transformY) / uDiv);
	info->sp_info.drawStartX = -info->sp_info.spriteWidth /
	2 + info->sp_info.spriteScreenX;
	if (info->sp_info.drawStartX < 0)
		info->sp_info.drawStartX = 0;
	info->sp_info.drawEndX = info->sp_info.spriteWidth /
	2 + info->sp_info.spriteScreenX;
	if (info->sp_info.drawEndX >= info->width)
		info->sp_info.drawEndX = info->width - 1;
}

void		put_sp_pixel(t_info *info, int x, int y, int i)
{
	info->sp_info.d = (y - info->sp_info.vMoveScreen) * 256 - info->height *
	128 + info->sp_info.spriteHeight * 128;
	info->sp_info.tex_y = ((info->sp_info.d
	* info->tex[sprite[spriteOrder[i]].texture].tex_height) /
	info->sp_info.spriteHeight) / 256;
	info->sp_info.color = info->texture[sprite[spriteOrder[i]].texture][info->
	tex[sprite[spriteOrder[i]].texture].tex_width
	* info->sp_info.tex_y + info->sp_info.tex_x];
	if ((info->sp_info.color & 0x00FFFFFF) != 0)
		info->buf[y][x] = info->sp_info.color;
}

void		draw_sprite(t_info *info, int i)
{
	int x;
	int y;

	x = info->sp_info.drawStartX;
	while (x < info->sp_info.drawEndX)
	{
		y = info->sp_info.drawStartY;
		info->sp_info.tex_x = (int)((256 * (x - (-info->sp_info.spriteWidth
		/ 2 + info->sp_info.spriteScreenX)) * info->
		tex[sprite[spriteOrder[i]].texture].tex_width
		/ info->sp_info.spriteWidth) / 256);
		if (info->sp_info.transformY > 0 && x > 0 && x < info->width && info->
		sp_info.transformY < info->zBuffer[x])
		{
			while (y < info->sp_info.drawEndY)
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
		spriteOrder[i] = i;
		spriteDistance[i] = dist(info->posX,
		info->posY, sprite[i].x, sprite[i].y);
		i++;
	}
	sort_sprites(spriteOrder, spriteDistance, info->sprite_stack);
	i = 0;
	while (i < info->sprite_stack)
	{
		set_sp_info(info, i);
		check_sp_pos(info);
		draw_sprite(info, i);
		i++;
	}
}
