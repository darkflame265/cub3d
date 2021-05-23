/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_press.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kihkim <kihkim@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/20 01:24:56 by kihkim            #+#    #+#             */
/*   Updated: 2021/05/23 22:39:54 by kihkim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int		button_down(int keycode, t_info *info)
{
	if (keycode >= 300 && keycode != K_ESC)
		return (-1);
	info->key_check[keycode] = 1;
	return (0);
}

int		button_release(int keycode, t_info *info)
{
	if (keycode >= 300 && keycode != K_ESC)
		return (-1);
	info->key_check[keycode] = 0;
	return (0);
}
