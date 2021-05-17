#include "../includes/cub3d.h"

void		read_file(char **argv, t_info *info)
{
	char *line = 0;
	int ret;
	int fd;

	fd = open(argv[1], O_RDONLY);
	//fd = open("test_map.cub", O_RDONLY);
	while ((ret = get_next_line(fd, &line, info)) > 0)
	{
		//printf("%s\n", line);
		free(line);
	}
	//printf("%s\n", line);
	free(line);
}

int			check_file(t_info *info)
{
	int	error_flag = 0;
	//non-Exist == -1, Exist == 0
	if (access(info->gnl_info.path_no, 0) < 0)
	{
		printf("[ERROR] Can't find NO file. please check the file path.\n");
		error_flag = 1;
	}
	if (access(info->gnl_info.path_so, 0) < 0)
	{
		printf("[ERROR] Can't find SO file. please check the file path.\n");
		error_flag = 1;
	}
	if (access(info->gnl_info.path_we, 0) < 0)
	{
		printf("[ERROR] Can't find WE file. please check the file path.\n");
		error_flag = 1;
	}
	if (access(info->gnl_info.path_ea, 0) < 0)
	{
		printf("[ERROR] Can't find EA file. please check the file path.\n");
		error_flag = 1;
	}
	if (access(info->gnl_info.path_sprite, 0) < 0)
	{
		printf("[ERROR] Can't find SPRITE file. please check the file path.\n");
		error_flag = 1;
	}
	if (error_flag == 1)
		return (0);
	else
		return (1);
}

int			check_value(t_info *info)
{
	int max_x;
	int max_y;
	int	error_flag = 0;

	mlx_get_screen_size(info->mlx, &max_x, &max_y);
	printf("wid: %d, hei: %d\n", info->gnl_info.wid, info->gnl_info.hei);
	if (info->gnl_info.wid == 0 || info->gnl_info.hei == 0)
	{
		printf("[ERROR] Resolution Value is 0 or blank.\n");
		return (0);
	}
	if (info->gnl_info.wid > max_x || info->gnl_info.hei > max_y)
	{
		printf("[ERROR] Set Resolution is too big. (user: %d, %d) (COM: %d, %d)\n", info->gnl_info.wid, info->gnl_info.hei, max_x, max_y);
		return (0);
	}
	// 255, 만 입력 받으면, 255, 255,255 로 인식되는 버그.
	for (int i = 0; i < 3; i++)
	{
		printf("info->gnl_info.ff[i]: %d\n", info->gnl_info.ff[i]);
		//printf("info->gnl_info.ff[i]: %d\n", info->gnl_info.ff[i]);
		if (info->gnl_info.cc[i] < 0 || info->gnl_info.cc[i] > 255)
		{

			printf("[ERROR] Ceiling Color Value is uncorrect.\n");
			return (0);
		}
		if (info->gnl_info.ff[i] < 0 || info->gnl_info.ff[i] > 255)
		{

			printf("[ERROR] Floor Color Value is uncorrect.\n");
			return (0);
		}
	}
	if (check_map_is_safe(info) == 0)
	{
		printf("MAP IS FAIL. (Error Map in [%d][%d])\n", info->gnl_info.error_x, info->gnl_info.error_y);
		return (0);
	}
	return (1);
}
