/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_bitmap_util.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kihkim <kihkim@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/20 00:42:44 by kihkim            #+#    #+#             */
/*   Updated: 2021/05/23 00:58:41 by kihkim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

unsigned char	*create_bitmapfile_header(int height, int stride)
{
	int						file_size;
	static unsigned char	file_header[] = {
		0, 0, 0, 0,
		0, 0, 0, 0,
		0, 0, 0, 0,
		0, 0
		};

	file_size = FILE_HEADER_SIZE + INFO_HEADER_SIZE + (stride * height);
	file_header[0] = (unsigned char)('B');
	file_header[1] = (unsigned char)('M');
	file_header[2] = (unsigned char)(file_size);
	file_header[3] = (unsigned char)(file_size >> 8);
	file_header[4] = (unsigned char)(file_size >> 16);
	file_header[5] = (unsigned char)(file_size >> 24);
	file_header[10] = (unsigned char)(FILE_HEADER_SIZE + INFO_HEADER_SIZE);
	return (file_header);
}

unsigned char	*create_bitmapinfo_header(int height, int width)
{
	static unsigned char info_header[] = {
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
		};

	info_header[0] = (unsigned char)(INFO_HEADER_SIZE);
	info_header[4] = (unsigned char)(width);
	info_header[5] = (unsigned char)(width >> 8);
	info_header[6] = (unsigned char)(width >> 16);
	info_header[7] = (unsigned char)(width >> 24);
	info_header[8] = (unsigned char)(height);
	info_header[9] = (unsigned char)(height >> 8);
	info_header[10] = (unsigned char)(height >> 16);
	info_header[11] = (unsigned char)(height >> 24);
	info_header[12] = (unsigned char)(1);
	info_header[14] = (unsigned char)(BP * 8);
	return (info_header);
}

void			set_bit_info(t_info *info)
{
	int i;

	i = 0;
	info->bit_info.width_in_bytes = info->gnl_info.wid * BP;
	info->bit_info.padding_size = (4 - (info->bit_info.width_in_bytes) % 4) % 4;
	info->bit_info.stride = (info->bit_info.width_in_bytes)
	+ info->bit_info.padding_size;
	info->bit_info.image_file = fopen(info->bit_info.image_file_name, "wb");
	info->bit_info.file_header = create_bitmapfile_header(
		info->gnl_info.hei, info->bit_info.stride);
	info->bit_info.info_header = create_bitmapinfo_header(
		info->gnl_info.hei, info->gnl_info.wid);
	fwrite(info->bit_info.file_header, 1, FILE_HEADER_SIZE,
		info->bit_info.image_file);
	fwrite(info->bit_info.info_header, 1, INFO_HEADER_SIZE,
		info->bit_info.image_file);
}

void			generate_bitmap_image(unsigned char *image, t_info *info)
{
	int				i;

	i = 0;
	set_bit_info(info);
	while (i < info->gnl_info.hei)
	{
		fwrite(image + (i * info->bit_info.width_in_bytes),
		BP, info->gnl_info.wid, info->bit_info.image_file);
		fwrite(info->bit_info.padding, 1,
		info->bit_info.padding_size, info->bit_info.image_file);
		i++;
	}
	fclose(info->bit_info.image_file);
}

void			set_bit_basic(t_info *info)
{
	info->bit_info.r = 0xff0000;
	info->bit_info.g = 0x00ff00;
	info->bit_info.b = 0x0000ff;
	info->bit_info.image_file_name = (char*)"bitmapImage.bmp";
}
