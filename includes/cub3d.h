#ifndef CUB3D_H
# define CUB3D_H

#include "../minilibx-linux/mlx.h"
#include "X11/X.h"
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <time.h>

#include <fcntl.h>
#define BUFFER_SIZE 64


#define K_W			119
#define K_A			97
#define K_S			115
#define K_D			100
#define K_ESC 		65307

#define texWidth 64
#define texHeight 64

#define BP 3
#define FILE_HEADER_SIZE 14
#define INFO_HEADER_SIZE 40

#define uDiv 1
#define vDiv 1
#define vMove 0.0

typedef struct	s_bit_info
{
	char			*image_file_name;

	int				width_in_bytes;
	unsigned char	padding[3];
	int				padding_size;
	int				stride;
	FILE			*image_file;
	unsigned char	*file_header;
	unsigned char	*info_header;
	int				r;
	int				g;
	int				b;
}				t_bit_info;

typedef struct s_pas_info
{
	int i;
	int	i0;
	int level;
	int check;
	char	def;

	char	cc0[100];
	char	cc1[100];
	char	cc2[100];

	char	ff0[100];
	char	ff1[100];
	char	ff2[100];

	char	wid[50];
	char	hei[50];

	char	*letter;

}				t_pas_info;

typedef struct s_gnl_info
{
	int		wid;
	int		hei;
	char	*path_no;
	char	*path_so;
	char	*path_ea;
	char	*path_we;
	char	*path_sprite;
	int		ff[3];
	int		cc[3];
	int		mapX;
	int		mapY;
	char	**map;
	char	temp_map[1000][1000];

	int		mh;
	int		mw;
	int		start_flag;

	int		fail_flag;

	int		error_x;
	int		error_y;

	int		mw2[1000];
	//맵의 가로길이는 맵의 모든 행을 피싱하고, 비교.
	//이후 제일 긴것을 가로 길이로 삼는다.
	//세로 또한 마찬가지.
}				t_gnl_info;

typedef struct	s_img
{
	void	*img;
	int		*data;

	int		size_l;
	int		bpp;
	int		endian;

	int		img_width;
	int		img_height;
}				t_img;

typedef struct	s_tex
{
	int		tex_width;
	int		tex_height;
}				t_tex;

typedef struct	s_info
{
	int		key_check[65536];
	double posX;
	double posY;
	double dirX;
	double dirY;
	double planeX;
	double planeY;
	void	*mlx;
	void	*win;
	double	moveSpeed;
	double	rotSpeed;

	int		width;
	int		height;

	t_img	img;
	int		**buf;

	//int		**worldMap;
	char	**worldMap;
	int		**texture;
	t_tex	tex[100];

	double	*zBuffer;
	//double	zBuffer[640];
	int		sprite_stack;

	t_gnl_info	gnl_info;
	t_pas_info	pas_info;
	t_bit_info	bit_info;

	int		save_flag;
	int		i;
	int		j;
}				t_info;

#define numSprites 19

struct Sprite
{
  double x;
  double y;
  int texture;
};

struct Sprite sprite[22];



typedef struct		s_pair
{
	double	first;
	int		second;
}					t_pair;

int spriteOrder[numSprites];
double spriteDistance[numSprites];

//function used to sort the sprites
void sortSprites(int* order, double* dist, int amount);

//srcs/key_press.c
int button_down(int keycode, t_info *info);
int button_release(int keycode, t_info *info);

//srcs/key_press2.c
int	key_press(t_info *info);

//srcs/draw.c
void	verLine(t_info *info, int x, int y1, int y2, int color);
void	draw(t_info *info);

//srcs/draw_bitmap.c
void	save_bmp(t_info *info);

void			set_bit_info(t_info *info);

//srcs/draw_bitmap_util.c
void			set_bit_basic(t_info *info);
void			set_bit_info(t_info *info);
unsigned char	*create_bitmapfile_header(int height, int stride);
unsigned char	*create_bitmapinfo_header(int height, int width);
void			generate_bitmap_image(unsigned char *image, t_info *info);

//srcs/raycasting.c
void	calc(t_info *info);

//srcs/raycasting_util.c
float dist(float ax, float ay, float bx, float by);
void	sort_order(t_pair *orders, int amount);
void	sort_sprites(int *order, double *dist, int amount);

//srcs/init_variable
void	init_basic(t_info *info);
void	init_buf(t_info *info);
void	init_texture(t_info *info);
void	load_image(t_info *info, char *path, t_img *img, int tex_num);
void    load_texture(t_info *info);

//srcs/init_map.c
void	set_north(t_info *info, int i, int j);
void	set_south(t_info *info, int i, int j);
void	set_west(t_info *info, int i, int j);
void	set_east(t_info *info, int i, int j);
void	set_sprite(t_info *info, int i, int j);

//srcs/init_map2.c
void	set_map_size(t_info *info);
void	init_map(t_info *info);

//srcs/get_next_line
int					get_next_line(int fd, char **line, t_info *info);

//srcs/get_next_line2.c
void		check_series(char *line, t_info *info);
int			check_backup(int fd, char **line, char **backup);
int			super(int text_length, char **next_adrs, int fd, char *backup);

//srcs/get_next_line_utils.c

int					check_str_has_n(char *str);
size_t				ft_strlen(const char *str);
char				*ft_strdup(const char *s1);
char				*ft_strjoin(char const *s1, char const *s2);

//srcs/utils
int	ft_atoi(const char *str);
int	ft_strncmp(char *s1, char *s2, unsigned int n);

//srcs/parsing1.c
int			check_file(t_info *info);
void		check_defi(char *line, t_info *info, char c1, char c2);
void		check_r(char *line, t_info *info);

//srcs/parsing2.c
void		check_no(char *line, t_info *info);
void		check_so(char *line, t_info *info);
void		check_we(char *line, t_info *info);
void		check_ea(char *line, t_info *info);
void		check_sprite(char *line, t_info *info);

//srcs/pars_ceil_floor.c
void		check_ceiling_color(char *line, t_info *info);
void		check_floor_color(char *line, t_info *info);

//srcs/pars_def.c
void	def_cf(t_info *info);
void	def_r(t_info *info);

//srcs/check_map.c
void		check_map_size(char *line, t_info *info);
int			check_map_is_safe(t_info *info);

//srcs/check_file.c
void	read_file(char **argv, t_info *info);
int		check_file(t_info *info);
int		check_value(t_info *info);

//srcs/parsing_util.c
void	put_letter(char *line, t_info *info);
int		check_valid_word(char *line, int i);
void	check_def(char *line, t_info *info, char c);
void	check_letter(t_info *info);


//srcs/parsing_util2.c
int		sep_c_f(char *line, t_info *info, int res);
int		sep_r(char *line, t_info *info, int res);
int		put_letter2(char *line, t_info *info);
void	letter_to_info_cf(t_info *info);
void	letter_to_info(t_info *info);

//srcs/memory_clean.c
void	init_temp_map(t_info *info);
void	init_temp_key(t_info *info);
void	init_temp_cf(t_info *info);
void	memory_clean(t_info *info);
void	memory_clean(t_info *info);

#endif
