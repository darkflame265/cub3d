#include "../includes/cub3d.h"

void	check_map_size(char *line, int text_length, t_info *info)
{
	int		i = 0;
	int		fail_flag = 0;
	char	width_map[text_length];
	int		stack = 0;

	//맵 피싱 시작지점 기준을 못 찾음. 내일해. 0510에 해.
	while (line[i] != '\0')
	{
		if (line[i] != '0' && line[i] != '1' && line[i] != '2' && line[i] != ' '
		 && line[i] != 'W' && line[i] != 'E' && line[i] != 'S' && line[i] != 'N'
		 && line[i] != '\0')
		{
			fail_flag = 1;
		}
		i++;
	}
	while (line[i] != '\0')
	{
		if (line[i] == ' ')
			stack++;
		i++;
	}
	if (stack == i)
		fail_flag = 1;
	if (fail_flag == 0)
	{
		while (line[i] != '\0')
			i++;
		info->gnl_info.start_flag = 1;
		if (info->gnl_info.max_width < i)
			info->gnl_info.max_width = i;
	}
	if (fail_flag == 0)
	{
		i = 0;
		while (line[i] != '\0')
		{
			//width_map[i] = line[i];
			info->gnl_info.temp_map[info->gnl_info.max_height][i] = line[i];
			i++;
		}
		info->gnl_info.temp_map[info->gnl_info.max_height][i] = line[i];
		info->gnl_info.max_height++;
	}
}

int		check_map_is_safe(t_info *info)
{
	for (int i = 0; i < info->gnl_info.max_height; i++)
	{
		for (int j = 0; j < info->gnl_info.max_width; j++)
		{
			if (info->gnl_info.temp_map[i][j] != '1' && info->gnl_info.temp_map[i][j] != ' ' && info->gnl_info.temp_map[i][j] != 0)
			{
				//위를 검사.
				if ((info->gnl_info.temp_map[i - 1][j] == ' ' || info->gnl_info.temp_map[i - 1][j] == 0) ||
				(info->gnl_info.temp_map[i + 1][j] == ' ' || info->gnl_info.temp_map[i + 1][j] == 0) ||
				(info->gnl_info.temp_map[i][j + 1] == ' ' || info->gnl_info.temp_map[i][j + 1] == 0) ||
				(info->gnl_info.temp_map[i][j - 1] == ' ' || info->gnl_info.temp_map[i][j - 1] == 0))
				{
					info->gnl_info.error_x = i;
					info->gnl_info.error_y = j;
					return (0);
				}

			}
		}
	}
	int i = 2;
	int j = 5;
	// printf("info->gnl_info.temp_map[%d][%d]: %c\n", i, j, info->gnl_info.temp_map[i][j]);
	// printf("info->gnl_info.temp_map[%d][%d]: %d\n", i, j, info->gnl_info.temp_map[i][j]);

	return (1);
}
