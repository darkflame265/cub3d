#include "./includes/cub3d.h"

int	main_loop(t_info *info)
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
	info->img.data = (int *)mlx_get_data_addr(info->img.img, &info->img.bpp, &info->img.size_l, &info->img.endian);

	mlx_loop_hook(info->mlx, &main_loop, info);
	mlx_hook(info->win, 2, (1L<<0), button_down, info);
	mlx_hook(info->win, 3, (1L<<1), button_release, info);
}

int	main(int argc, char **argv)
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

		char *line;
		int ret;
		int fd;

		fd = open(argv[1], O_RDONLY);
		while ((ret = get_next_line(fd, &line, &info)) > 0)
			free(line);

		if (check_file(&info) == 0)
			return (0);
		if (check_value(&info) == 0)
			return (0);

		init_buf(&info);
		init_map(&info);
		init_texture(&info);
		load_texture(&info);

		if (argc == 3)
		{
			if (ft_strncmp(argv[2], "--save", 7) == 0)
				info.save_flag = 1;
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
		create_window(&info);
		mlx_loop(info.mlx);
	}
	return (0);

}
