#include "./includes/cub3d.h"

int	main_loop(t_info *info)
{
	key_press(info);

	double current_time = 0; //time of current frame
	double oldTime = 0; //time of previous frame
	oldTime = clock();

	calc(info);
	if (info->save_flag == 1)
	{
		save_bmp(info);
		exit(0);
	}
	draw(info);

    current_time = clock();
    double frameTime = (current_time - oldTime) / 1000.0; //frameTime is the time this frame has taken, in seconds

	//printf("frameTime(0.001) : %f\n", frameTime);
	//fps(frame per second를 구해서 이동속도에 적용한다.
	//fps를 적용하면 레이캐스팅 시간이 오래걸려도 사용자의 체감시간은 똑같아짐.
	//원래 해상도를 높이면 느려지고, 낮추면 속도가 빨라지는데, fps하면 일정해진다.
	//[추가] fpst 적용하니까 더 이상해짐. 걍 쓰지마.

	// info->moveSpeed = 0.025 * frameTime;
	// info->rotSpeed = 0.01 * frameTime;

	return (0);
}

void	create_window(t_info *info)
{
	info->win = mlx_new_window(info->mlx, info->width, info->height, "mlx");
	info->img.img = mlx_new_image(info->mlx, info->width, info->height);
	info->img.data = (int *)mlx_get_data_addr(info->img.img, &info->img.bpp, &info->img.size_l, &info->img.endian);

	mlx_loop_hook(info->mlx, &main_loop, info);
	mlx_hook(info->win, 2, (1L<<0), Button_down, info);
	mlx_hook(info->win, 3, (1L<<1), Button_release, info);
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
		read_file(argv, &info);

		if (check_file(&info) == 0)
			return (0);
		if (check_value(&info) == 0)
			return (0);

		init_buf(&info);
		init_map(&info);
		init_texture(&info);
		load_texture(&info);

		// if (check_map_is_safe(&info) == 0)
		// {
		// 	printf("MAP IS FAIL. (Error Map in [%d][%d])\n", info.gnl_info.error_x, info.gnl_info.error_y);
		// 	return (0);
		// }
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
