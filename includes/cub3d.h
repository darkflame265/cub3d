/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kihkim <kihkim@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/23 23:21:16 by kihkim            #+#    #+#             */
/*   Updated: 2021/05/24 21:40:52 by kihkim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "../minilibx-linux/mlx.h"
# include "X11/X.h"
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <math.h>
# include <time.h>
# include <fcntl.h>

# define BUFFER_SIZE 64
# define K_W 119
# define K_A 97
# define K_S 115
# define K_D 100
# define K_ESC 65307

# define KEY_UP_ARROW 65362
# define KEY_LEFT_ARROW 65361
# define KEY_DOWN_ARROW 65364
# define KEY_RIGHT_ARROW 65363

# define TEXWIDTH 64
# define TEXHEIGHT 64

# define BP 3
# define FILE_HEADER_SIZE 14
# define INFO_HEADER_SIZE 40

# define UDIV 1
# define VDIV 1
# define VMOVE 0.0

typedef struct		s_sp_info
{
	double	sp_x;
	double	sp_y;
	double	inv_det;
	double	form_x;
	double	form_y;
	int		sp_screen_x;
	int		vm_screen;
	int		sp_height;
	int		sp_width;
	int		draw_start_x;
	int		draw_start_y;
	int		draw_end_x;
	int		draw_end_y;
	int		tex_x;
	int		tex_y;
	int		color;
	int		d;
}					t_sp_info;

typedef struct		s_bit_info
{
	int				width_in_bytes;
	int				padding_size;
	int				stride;
	int				r;
	int				g;
	int				b;
	char			*image_file_name;
	FILE			*image_file;
	unsigned char	padding[3];
	unsigned char	*file_header;
	unsigned char	*info_header;

}					t_bit_info;

typedef struct		s_pas_info
{
	int		i;
	int		i0;
	int		level;
	int		check;
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
}					t_pas_info;

typedef struct		s_gnl_info
{
	int		wid;
	int		hei;
	char	*path_no;
	char	*path_so;
	char	*path_ea;
	char	*path_we;
	char	*path_sp;
	int		ff[3];
	int		cc[3];
	int		map_x;
	int		map_y;
	char	**map;
	char	temp_map[1000][1000];
	int		mh;
	int		mw;
	int		start_flag;
	int		fail_flag;
	int		error_x;
	int		error_y;
	int		mw2[1000];
}					t_gnl_info;

typedef struct		s_img
{
	void	*img;
	int		*data;

	int		size_l;
	int		bpp;
	int		endian;

	int		img_width;
	int		img_height;
}					t_img;

typedef struct		s_tex
{
	int		tex_width;
	int		tex_height;
}					t_tex;

typedef struct		s_calc
{
	int		draw_start;
	int		draw_end;
	int		map_x;
	int		map_y;
	int		hit;
	int		side;
	int		line_hei;
	int		color;
	int		tex_num;
	int		tex_x;
	double	cam_x;
	double	raydir_x;
	double	raydir_y;
	double	sd_dist_x;
	double	sd_dist_y;
	double	step_x;
	double	step_y;
	double	dt_dist_x;
	double	dt_dist_y;
	double	final_dist;
	double	wall_x;
}					t_calc;

typedef struct		s_sprite
{
	double	x;
	double	y;
	int		texture;
}					t_sprite;

typedef struct		s_info
{
	int			key_check[65536];
	int			width;
	int			height;
	int			**buf;
	int			**texture;
	int			sprite_stack;
	int			save_flag;
	int			i;
	int			j;
	int			error_flag;
	double		pos_x;
	double		pos_y;
	double		dir_x;
	double		dir_y;
	double		plane_x;
	double		plane_y;
	double		move_speed;
	double		rot_speed;
	double		*z_buffer;
	void		*mlx;
	void		*win;
	char		**world_map;
	t_img		img;
	t_tex		tex[100];
	t_gnl_info	gnl_info;
	t_pas_info	pas_info;
	t_bit_info	bit_info;
	t_sp_info	sp_info;
	t_calc		calc;
	t_sprite	sprites[22];
	int			sp_order[19];
	double		sp_dist[19];
}					t_info;

typedef struct		s_pair
{
	double	first;
	int		second;
}					t_pair;

int					button_down(int keycode, t_info *info);
int					button_release(int keycode, t_info *info);
int					press_exit_button(t_info *info);
int					key_press(t_info *info);
void				key_arrow(t_info *info);
void				draw(t_info *info);
void				save_bmp(t_info *info);
void				set_bit_info(t_info *info);
void				set_bit_basic(t_info *info);
void				set_bit_info(t_info *info);
unsigned char		*create_bitmapfile_header(int height, int stride);
unsigned char		*create_bitmapinfo_header(int height, int width);
void				generate_bitmap_image(unsigned char *image, t_info *info);
void				get_texture(t_info *info);
void				draw_wall(t_info *info, int x);
void				calc(t_info *info);
void				next_step(t_info *info);
void				check_hit_wall(t_info *info);
void				get_clean_dist(t_info *info);
void				get_pixel_destination(t_info *info);
void				get_wall_pos(t_info *info);
void				sprite_part(t_info *info);
float				dist(float ax, float ay, float bx, float by);
void				sort_order(t_pair *orders, int amount);
void				sort_sprites(int *order, double *dist, int amount);
void				init_basic(t_info *info);
void				init_buf(t_info *info);
void				init_texture(t_info *info);
void				init_buf_texture(t_info *info);
void				load_texture(t_info *info);
void				set_north(t_info *info, int i, int j);
void				set_south(t_info *info, int i, int j);
void				set_west(t_info *info, int i, int j);
void				set_east(t_info *info, int i, int j);
void				set_sprite(t_info *info, int i, int j);
void				set_map_size(t_info *info);
void				init_map(t_info *info);
int					get_next_line(int fd, char **line, t_info *info);
void				check_series(char *line, t_info *info);
int					check_backup(int fd, char **line, char **backup);
int					check_str_has_n(char *str);
size_t				ft_strlen(const char *str);
char				*ft_strdup(const char *s1);
char				*ft_strjoin(char const *s1, char const *s2);
int					ft_atoi(const char *str);
int					ft_strncmp(char *s1, char *s2, unsigned int n);
void				check_defi(char *line, t_info *info, char c1, char c2);
void				check_r(char *line, t_info *info);
void				check_no(char *line, t_info *info);
void				check_so(char *line, t_info *info);
void				check_we(char *line, t_info *info);
void				check_ea(char *line, t_info *info);
void				check_sprite(char *line, t_info *info);
void				check_ceiling_color(char *line, t_info *info);
void				check_floor_color(char *line, t_info *info);
void				def_cf(t_info *info);
void				def_r(t_info *info);
void				check_map_size(char *line, t_info *info);
int					check_map_is_safe(t_info *info);
void				read_file(char **argv, t_info *info);
void				error_pt(t_info *info, char *path, char *message);
int					check_file(t_info *info, char *path);
int					check_src_file(t_info *info);
int					check_value(t_info *info);
void				put_letter(char *line, t_info *info);
int					check_valid_word(char *line, int i);
void				check_def(char *line, t_info *info, char c);
void				check_letter(t_info *info);
int					sep_c_f(char *line, t_info *info, int res);
int					sep_r(char *line, t_info *info, int res);
int					put_letter2(char *line, t_info *info);
void				letter_to_info_cf(t_info *info);
void				letter_to_info(t_info *info);
void				init_temp_map(t_info *info);
void				init_temp_key(t_info *info);
void				init_temp_cf(t_info *info);
void				memory_clean(t_info *info);
void				memory_clean(t_info *info);

#endif
