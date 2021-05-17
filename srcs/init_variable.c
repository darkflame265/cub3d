#include "../includes/cub3d.h"

void	init_basic(t_info *info)
{
	//플레이어 초기 위치 벡터.
	info->posX = 12;
	info->posY = 5;

	//플레이어 초기 방향 벡터.
	info->dirX = -1;
	info->dirY = 0;

	//플레이어의 카메라평면
	info->planeX = 0;
	info->planeY = 0.66;

	// "카메라평면의 길이 : 방향벡터 길이" 의 비율로 FOV 가 결정
	//현재시야각(FOV) = 2 * atan(0.66/1.0)=66.8°

	info->moveSpeed = 0.05;
	info->rotSpeed = 0.053;

	// info->width = 640;
	// info->height = 480;

	info->gnl_info.max_width = 0;
	info->gnl_info.max_height = 0;
	info->gnl_info.start_flag = 0;

	info->save_flag = 0;
}

void	init_buf(t_info *info)
{
	info->width = info->gnl_info.wid;
	info->height = info->gnl_info.hei;
	info->buf = (int **)malloc(sizeof(int *) * info->height);
	for (int i = 0; i < info->height; i++)
	{
		info->buf[i] = (int *)malloc(sizeof(int) * info->width);
	}

	for (int i = 0; i < info->height; i++)
	{
		for (int j = 0; j < info->width; j++)
		{
			info->buf[i][j] = 0;
		}
	}

	info->zBuffer = (double *)malloc(sizeof(double) * info->width);
}

	char worldMap2 [24][24] = {
							{'1','1','1','1','1','1','1','1','1','1','1','1','1','1','1','1','1','1','1','1','1','1','1','1'},
							{'1','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','1'},
							{'1','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','1'},
							{'1','0','0','1','1','1','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','1'},
							{'1','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','1'},
							{'1','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','1'},
							{'1','0','0','0','0','0','0','0','0','0','0','0','1','0','0','0','0','0','0','0','0','0','0','1'},
							{'1','0','0','0','0','0','0','0','0','0','0','0','1','0','0','0','0','0','0','0','0','0','0','1'},
							{'1','0','0','0','0','0','0','0','0','0','0','0','1','0','0','0','0','0','0','0','0','0','0','1'},
							{'1','0','0','0','0','0','0','0','0','0','0','0','1','0','3','0','0','0','0','0','0','0','0','1'},
							{'1','0','0','0','0','0','0','0','0','0','0','0','1','0','0','3','0','0','0','0','0','0','0','1'},
							{'1','0','0','0','0','0','0','0','0','0','2','2','1','0','0','0','3','0','0','0','0','0','0','1'},
							{'1','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','1'},
							{'1','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','4','4','0','0','0','1'},
							{'1','0','0','0','0','0','0','0','1','0','0','0','n','0','0','0','1','0','4','4','0','0','0','1'},
							{'1','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','1'},
							{'1','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','1'},
							{'1','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','1'},
							{'1','0','0','0','0','0','0','0','0','0','0','0','1','0','0','0','0','0','0','0','0','0','0','1'},
							{'1','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','1'},
							{'1','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','1'},
							{'1','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','1'},
							{'1','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','1'},
							{'1','1','1','1','1','1','1','1','1','1','1','1','1','1','1','1','1','1','1','1','1','1','1','1'},
						};


void	init_map(t_info *info)
{
	// info->worldMap = (char **)malloc(sizeof(char *) * 24);
	// for (int i = 0; i < 24; i++)
	// {
	// 	info->worldMap[i] = (char *)malloc(sizeof(char) * 24);
	// }
	info->worldMap = (char **)malloc(sizeof(char *) * info->gnl_info.max_height);
	for (int i = 0; i < info->gnl_info.max_height; i++)
	{
		info->worldMap[i] = (char *)malloc(sizeof(char) * info->gnl_info.max_width);
	}

	info->sprite_stack = 0;
	for (int i = 0; i < info->gnl_info.max_height; i++)
	{
		for (int j = 0; j < info->gnl_info.max_width; j++)
		{
			//printf("info->gnl_info.temp_map[%d][%d]: %c\n", i, j, info->gnl_info.temp_map[i][j]);
			if (info->gnl_info.temp_map[i][j] == '\0')
				break;
			info->worldMap[i][j] = info->gnl_info.temp_map[i][j];
			//info->worldMap[i][j] = worldMap2[i][j];
			//기본은 북쪽.
			if (info->worldMap[i][j] == 'n' || info->worldMap[i][j] == 'N')
			{
				info->posX = i + 0.5f;
				info->posY = j + 0.5f;
			}
			if (info->worldMap[i][j] == 'e' || info->worldMap[i][j] == 'E') //동쪽
			{
				info->posX = i + 0.5f;
				info->posY = j + 0.5f;

				for (int i = 0; i < 30; i++)
				{
					double oldDirX = info->dirX;
					info->dirX = info->dirX * cos(-info->rotSpeed) - info->dirY * sin(-info->rotSpeed);
					info->dirY = oldDirX * sin(-info->rotSpeed) + info->dirY * cos(-info->rotSpeed);
					double oldPlaneX = info->planeX;
					info->planeX = info->planeX * cos(-info->rotSpeed) - info->planeY * sin(-info->rotSpeed);
					info->planeY = oldPlaneX * sin(-info->rotSpeed) + info->planeY * cos(-info->rotSpeed);
				}
			}
			if (info->worldMap[i][j] == 'w' || info->worldMap[i][j] == 'W') //서쪽
			{
				info->posX = i + 0.5f;
				info->posY = j + 0.5f;

				for (int i = 0; i < 30; i++)
				{
					double oldDirX = info->dirX;
					info->dirX = info->dirX * cos(info->rotSpeed) - info->dirY * sin(info->rotSpeed);
					info->dirY = oldDirX * sin(info->rotSpeed) + info->dirY * cos(info->rotSpeed);
					double oldPlaneX = info->planeX;
					info->planeX = info->planeX * cos(info->rotSpeed) - info->planeY * sin(info->rotSpeed);
					info->planeY = oldPlaneX * sin(info->rotSpeed) + info->planeY * cos(info->rotSpeed);
				}
			}
			if (info->worldMap[i][j] == 's' || info->worldMap[i][j] == 'S') //남쪽
			{
				info->posX = i + 0.5f;
				info->posY = j + 0.5f;

				for (int i = 0; i < 60; i++)
				{
					double oldDirX = info->dirX;
					info->dirX = info->dirX * cos(info->rotSpeed) - info->dirY * sin(info->rotSpeed);
					info->dirY = oldDirX * sin(info->rotSpeed) + info->dirY * cos(info->rotSpeed);
					double oldPlaneX = info->planeX;
					info->planeX = info->planeX * cos(info->rotSpeed) - info->planeY * sin(info->rotSpeed);
					info->planeY = oldPlaneX * sin(info->rotSpeed) + info->planeY * cos(info->rotSpeed);
				}
			}
			else if (info->worldMap[i][j] == '2')
			{
				sprite[info->sprite_stack].x = i + 0.5;
				sprite[info->sprite_stack].y = j + 0.5;
				sprite[info->sprite_stack].texture = 8;
				info->sprite_stack++;
			}
			else if (info->worldMap[i][j] == '3')
			{
				sprite[info->sprite_stack].x = i + 0.5;
				sprite[info->sprite_stack].y = j + 0.5;
				sprite[info->sprite_stack].texture = 9;
				info->sprite_stack++;
			}
			else if (info->worldMap[i][j] == '4')
			{
				sprite[info->sprite_stack].x = i + 0.5;
				sprite[info->sprite_stack].y = j + 0.5;
				sprite[info->sprite_stack].texture = 10;
				info->sprite_stack++;
			}
		}
	}
}

void	init_texture(t_info *info)
{
	info->texture = (int **)malloc(sizeof(int *) * 16); //8개의 텍스쳐가 들어갈 1단계 공간 생성.

	//각각의 텍스쳐(8개)는 (texWidth * texHeight)개의 공간을 가진다.
	for (int i = 0; i < 16; i++)
	{
		info->texture[i] = (int *)malloc(sizeof(int) * (texWidth * texHeight));
	}
	//(texWidth * texHeight)개의 공간을 0으로 초기화.
	for (int i = 0; i < 16; i++)
	{
		for (int j = 0; j < texHeight * texWidth; j++)
		{
			info->texture[i][j] = 0;
		}
	}

	//이게 히틀러 텍스쳐도 64X64크기로 배정해서 문제.
}

void	load_image(t_info *info, char *path, t_img *img, int tex_num)
{
	img->img = mlx_xpm_file_to_image(info->mlx, path, &img->img_width, &img->img_height);
	img->data = (int *)mlx_get_data_addr(img->img, &img->bpp, &img->size_l, &img->endian);
	info->tex[tex_num].tex_width = img->img_width;
	info->tex[tex_num].tex_height = img->img_height;
	if (img->img_width != texWidth || img->img_height != texHeight) //enemy처럼 120X120이 나오면 메모리 재할당.
	{
		info->texture[tex_num] = realloc(info->texture[tex_num], (sizeof(int) * (img->img_width * img->img_height)));
		// free(info->texture[tex_num]);
		// info->texture[tex_num] = malloc((sizeof(int) * (img->img_width * img->img_height)));
	}
	for (int y = 0; y < img->img_height; y++)
	{
		for (int x = 0; x < img->img_width; x++)
		{
			info->texture[tex_num][img->img_width * y + x] = img->data[img->img_width * y + x];
		}
	}
	mlx_destroy_image(info->mlx, img->img);
}

void	load_texture(t_info *info)
{
	t_img	img;

	//wall texture
	// load_image(info, info->texture[0], "pics/eagle.xpm", &img);
	// load_image(info, info->texture[1], "pics/redbrick.xpm", &img);
	// load_image(info, info->texture[2], "pics/purplestone.xpm", &img);
	// load_image(info, info->texture[3], "pics/greystone.xpm", &img);
	// load_image(info, info->texture[4], "pics/bluestone.xpm", &img);
	// load_image(info, info->texture[5], "pics/mossy.xpm", &img);
	// load_image(info, info->texture[6], "pics/wood.xpm", &img);
	// load_image(info, info->texture[7], "pics/colorstone.xpm", &img);

	//스폰지밥 친구들.
	// load_image(info, info->texture[0], "pics/east.xpm", &img, 0);
    // load_image(info, info->texture[1], "pics/west.xpm", &img, 1);
    // load_image(info, info->texture[2], "pics/south.xpm", &img, 2);
    // load_image(info, info->texture[3], "pics/north.xpm", &img, 3);

	//글자 친구들

	// if (file_exists(info->gnl_info.path_no) == 1);
	// 	printf("sibal\n");


	load_image(info, info->gnl_info.path_no, &img, 0);
	load_image(info, info->gnl_info.path_so, &img, 1);
	load_image(info, info->gnl_info.path_ea, &img, 2);
	load_image(info, info->gnl_info.path_we, &img, 3);

	//load_image(info, "textures/wall_n.xpm", &img, 0);
	//load_image(info, "textures/wall_s.xpm", &img, 1);
    // load_image(info, "textures/wall_e.xpm", &img, 2);
    // load_image(info, "textures/wall_w.xpm", &img, 3);

	load_image(info, info->gnl_info.path_sprite, &img, 8);

	//load_image(info, "pics/sprite.xpm", &img, 8);
	load_image(info, "pics/enemy.xpm", &img, 9);
	//load_image(info, "pics/greenlight.xpm", &img, 10);
	load_image(info, "pics/barrel.xpm", &img, 10);
}
