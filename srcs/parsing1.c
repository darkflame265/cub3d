#include "../includes/cub3d.h"

void check_r_def(char *line, t_info *info)
{
	while (line[info->pas_info.i] == ' ')
		info->pas_info.i++;
	if (line[info->pas_info.i] == 'R' && line[info->pas_info.i+1] == ' ')
	{
		info->pas_info.level = 1;
		info->pas_info.i = info->pas_info.i + 2;
		info->pas_info.def = 'R';
	}
	while (line[info->pas_info.i] == ' ')
		info->pas_info.i++;
}

void		check_r(char *line, t_info *info)
{
	info->pas_info.i = 0;
	info->pas_info.level = 0;
	info->pas_info.check = 0;
	info->pas_info.i0 = 0;
	info->pas_info.def = 0;

	char	wid[50];
	char	hei[50];

	check_r_def(line, info);
	while (info->pas_info.level == 1 && line[info->pas_info.i] != '\0')
	{
		if (check_valid_word(line, info->pas_info.i) == -1)
		{
			info->pas_info.check = -1;
			break;
		}
		if (put_letter2(line, info) == 0)
			break;
		info->pas_info.i++;
	}
	if (info->pas_info.level == 1)
		letter_to_info(info);
}

void		check_no(char *line, t_info *info)
{
	int		level1 = 0;
	char	no[100];
	int		result_index = 0;
	int		i = 0;

	while (line[i] == ' ')
		i++;
	if (line[i] == 'N' && line[i+1] == 'O')
	{
		level1 = 1;
		i = i + 2;
	}
	while (line[i] == ' ')
		i++;
	if (level1 == 1 && line[i] != ' ')
	{
		while ((line[i] != '\0'))
			no[result_index++] = line[i++];
		no[result_index++] = '\0';
		info->gnl_info.path_no = malloc(sizeof(char) * result_index);
		for (int i = 0; i < result_index; i++)
			info->gnl_info.path_no[i] = no[i];
	}
}

void		check_so(char *line, t_info *info)
{
	int		level1 = 0;
	char	so[100];
	int		result_index = 0;
	int		i = 0;

	while (line[i] == ' ')
		i++;
	if (line[i] == 'S' && line[i+1] == 'O')
	{
		level1 = 1;
		i = i + 2;
	}
	while (line[i] == ' ')
		i++;
	if (level1 == 1 && line[i] != ' ')
	{
		while ((line[i] != '\0'))
			so[result_index++] = line[i++];
		so[result_index++] = '\0';
		info->gnl_info.path_so = malloc(sizeof(char) * result_index);
		for (int i = 0; i < result_index; i++)
			info->gnl_info.path_so[i] = so[i];
	}
}

void		check_we(char *line, t_info *info)
{
	int		level1 = 0;
	char	we[100];
	int		result_index = 0;
	int		i = 0;

	while (line[i] == ' ')
		i++;
	if (line[i] == 'W' && line[i+1] == 'E')
	{
		level1 = 1;
		i = i + 2;
	}
	while (line[i] == ' ')
		i++;
	if (level1 == 1 && line[i] != ' ')
	{
		while ((line[i] != '\0'))
			we[result_index++] = line[i++];
		we[result_index++] = '\0';
		info->gnl_info.path_we = malloc(sizeof(char) * result_index);
		for (int i = 0; i < result_index; i++)
			info->gnl_info.path_we[i] = we[i];
	}
}

void		check_ea(char *line, t_info *info)
{
	int		level1 = 0;
	char	ea[100];
	int		result_index = 0;
	int		i = 0;

	while (line[i] == ' ')
		i++;
	if (line[i] == 'E' && line[i+1] == 'A')
	{
		level1 = 1;
		i = i + 2;
	}
	while (line[i] == ' ')
		i++;
	if (level1 == 1 && line[i] != ' ')
	{
		while ((line[i] != '\0'))
			ea[result_index++] = line[i++];
		ea[result_index++] = '\0';
		info->gnl_info.path_ea = malloc(sizeof(char) * result_index);
		for (int i = 0; i < result_index; i++)
			info->gnl_info.path_ea[i] = ea[i];
	}
}

void		check_sprite(char *line, t_info *info)
{
	int		level1 = 0;
	char	sprite[100];
	int		result_index = 0;
	int		i = 0;

	while (line[i] == ' ')
		i++;
	if (line[i] == 'S' && line[i+1] == ' ')
	{
		level1 = 1;
		i = i + 2;
	}
	while (line[i] == ' ')
		i++;
	if (level1 == 1 && line[i] != ' ')
	{
		while ((line[i] != '\0'))
			sprite[result_index++] = line[i++];
		sprite[result_index++] = '\0';
		info->gnl_info.path_sprite = malloc(sizeof(char) * result_index);
		for (int i = 0; i < result_index; i++)
			info->gnl_info.path_sprite[i] = sprite[i];
	}
}
