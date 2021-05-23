/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kihkim <kihkim@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/23 01:49:39 by kihkim            #+#    #+#             */
/*   Updated: 2021/05/23 22:40:03 by kihkim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/cub3d.h"

int		main_loop(t_info *info)
{
	key_press(info);
	calc(info);
	if (info->save_flag == 1)
	{
		save_bmp(info);
		exit(0);
	}
	draw(info);
	return (0);
}

void	create_window(t_info *info)
{
	info->win = mlx_new_window(info->mlx, info->width, info->height, "mlx");
	info->img.img = mlx_new_image(info->mlx, info->width, info->height);
	info->img.data = (int *)mlx_get_data_addr(info->img.img,
	&info->img.bpp, &info->img.size_l, &info->img.endian);
	mlx_loop_hook(info->mlx, &main_loop, info);
	mlx_hook(info->win, 2, (1L << 0), button_down, info);
	mlx_hook(info->win, 3, (1L << 1), button_release, info);
	mlx_hook(info->win, 33, (1L << 3), press_exit_button, info);
}

int		check_opt(t_info *info, int argc, char **argv)
{
	if (argc == 3)
	{
		if (ft_strncmp(argv[2], "--save", 7) == 0)
			info->save_flag = 1;
		else
		{
			printf("[ERROR] unavalid Option.\n");
			return (0);
		}
	}
	else if (argc > 3)
	{
		printf("Too Many argument.\n");
		return (0);
	}
	return (1);
}

int		read_and_check(t_info *info, int argc, char **argv)
{
	char	*line;
	int		ret;
	int		fd;

	error_pt(info, argv[1], "[ERROR] Can't find cub file.");
	if (info->error_flag == 1)
		return (0);
	fd = open(argv[1], O_RDONLY);
	while ((ret = get_next_line(fd, &line, info)) > 0)
		free(line);
	if (check_src_file(info) == 0 || check_value(info) == 0 ||
	check_opt(info, argc, argv) == 0)
		return (0);
	return (1);
}

int		main(int argc, char **argv)
{
	t_info info;

	info.mlx = mlx_init();
	if (!info.mlx)
	{
		printf("[ERROR] mlx creation failed.\n");
		return (0);
	}
	if (argc == 1)
	{
		printf("[ERROR] Can't find a map. Please enter a map.\n");
		return (0);
	}
	else
	{
		init_basic(&info);
		if (read_and_check(&info, argc, argv) == 0)
			return (0);
		init_buf_texture(&info);
		init_map(&info);
		load_texture(&info);
		create_window(&info);
		mlx_loop(info.mlx);
	}
	return (0);
}
