#include "minilibx-linux/mlx.h"
#include "X11/X.h"
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define KEY_W			119
#define KEY_A			97
#define KEY_S			115
#define KEY_D			100
#define KEY_ESC 		65307

#define PI 3.1415926535
#define P2 PI/2
#define P3 3*P2
#define DR 0.0174533 //one degree in radians = PI/180

#define texWidth 64
#define texHeight 64

#define WIDTH 1024
#define HEIGHT 724

float pdx, pdy, pa;

// int All_Textures[]=
// {
// 	0,0,0,0,0,1,0,0, 0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,
// 	0,0,0,0,0,1,0,0, 0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,
// 	0,0,0,0,0,1,0,0, 0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,
// 	0,0,0,0,0,1,0,0, 0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,

// 	0,0,0,0,0,1,0,0, 0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,
// 	0,0,0,0,0,1,0,0, 0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,
// 	0,0,0,0,0,1,0,0, 0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,
// 	0,0,0,0,0,1,0,0, 0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,

// 	0,0,0,0,0,0,0,0, 0,0,1,0,0,0,0,0, 0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,
// 	0,0,0,0,0,0,0,0, 0,0,1,0,0,0,0,0, 0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,
// 	0,0,0,0,0,0,0,0, 0,0,1,0,0,0,0,0, 0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,
// 	0,0,0,0,0,0,0,0, 0,0,1,0,0,0,0,0, 0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,

// 	0,0,0,0,0,0,0,0, 0,0,1,0,0,0,0,0, 0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,
// 	0,0,0,0,0,0,0,0, 0,0,1,0,0,0,0,0, 0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,
// 	0,0,0,0,0,0,0,0, 0,0,1,0,0,0,0,0, 0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,
// 	0,0,0,0,0,0,0,0, 0,0,1,0,0,0,0,0, 0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,
// };

// 32X16
// int All_Textures[]=
// {
// 	0,0,0,0,0,0,0,0, 1,1,1,1,1,1,1,1, 0,0,0,0,0,0,0,0, 1,1,1,1,1,1,1,1,
// 	0,0,0,0,0,0,0,0, 1,1,1,1,1,1,1,1, 0,0,0,0,0,0,0,0, 1,1,1,1,1,1,1,1,
// 	0,0,0,0,0,0,0,0, 1,1,1,1,1,1,1,1, 0,0,0,0,0,0,0,0, 1,1,1,1,1,1,1,1,
// 	0,0,0,0,0,0,0,0, 1,1,1,1,1,1,1,1, 0,0,0,0,0,0,0,0, 1,1,1,1,1,1,1,1,

// 	1,1,1,1,1,1,1,1, 0,0,0,0,0,0,0,0, 1,1,1,1,1,1,1,1, 0,0,0,0,0,0,0,0,
// 	1,1,1,1,1,1,1,1, 0,0,0,0,0,0,0,0, 1,1,1,1,1,1,1,1, 0,0,0,0,0,0,0,0,
// 	1,1,1,1,1,1,1,1, 0,0,0,0,0,0,0,0, 1,1,1,1,1,1,1,1, 0,0,0,0,0,0,0,0,
// 	1,1,1,1,1,1,1,1, 0,0,0,0,0,0,0,0, 1,1,1,1,1,1,1,1, 0,0,0,0,0,0,0,0,

// 	0,0,0,0,0,0,0,0, 1,1,1,1,1,1,1,1, 0,0,0,0,0,0,0,0, 1,1,1,1,1,1,1,1,
// 	0,0,0,0,0,0,0,0, 1,1,1,1,1,1,1,1, 0,0,0,0,0,0,0,0, 1,1,1,1,1,1,1,1,
// 	0,0,0,0,0,0,0,0, 1,1,1,1,1,1,1,1, 0,0,0,0,0,0,0,0, 1,1,1,1,1,1,1,1,
// 	0,0,0,0,0,0,0,0, 1,1,1,1,1,1,1,1, 0,0,0,0,0,0,0,0, 1,1,1,1,1,1,1,1,

// 	1,1,1,1,1,1,1,1, 0,0,0,0,0,0,0,0, 1,1,1,1,1,1,1,1, 0,0,0,0,0,0,0,0,
// 	1,1,1,1,1,1,1,1, 0,0,0,0,0,0,0,0, 1,1,1,1,1,1,1,1, 0,1,1,1,1,1,0,0,
// 	1,1,1,1,1,1,1,1, 0,0,0,0,0,0,0,0, 1,1,1,1,1,1,1,1, 0,1,1,1,0,0,0,0,
// 	1,1,1,1,1,1,1,1, 0,0,0,0,0,0,0,0, 1,1,1,1,1,1,1,1, 0,0,0,0,0,0,0,0,
// };

//32X32
// int All_Textures[]=
// {
// 	1,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,1,
// 	1,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,1,
// 	1,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,1,
// 	1,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,1,

// 	1,1,1,1,1,1,1,1, 0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0, 1,1,1,1,1,1,1,1,
// 	1,1,1,1,1,1,1,1, 0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0, 1,1,1,1,1,1,1,1,
// 	1,1,1,1,1,1,1,1, 0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0, 1,1,1,1,1,1,1,1,
// 	1,1,1,1,1,1,1,1, 0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0, 1,1,1,1,1,1,1,1,

// 	1,1,1,1,1,1,1,1, 0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0, 1,1,1,1,1,1,1,1,
// 	1,1,1,1,1,1,1,1, 0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0, 1,1,1,1,1,1,1,1,
// 	1,1,1,1,1,1,1,1, 0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0, 1,1,1,1,1,1,1,1,
// 	1,1,1,1,1,1,1,1, 0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0, 1,1,1,1,1,1,1,1,

// 	1,1,1,1,1,1,1,1, 0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0, 1,1,1,1,1,1,1,1,
// 	1,1,1,1,1,1,1,1, 0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0, 1,1,1,1,1,1,1,1,
// 	1,1,1,1,1,1,1,1, 0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0, 1,1,1,1,1,1,1,1,
// 	1,1,1,1,1,1,1,1, 0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0, 1,1,1,1,1,1,1,1,

// 	0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,
// 	0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,
// 	0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,
// 	0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,

// 	1,1,1,1,1,1,1,1, 0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0, 1,1,1,1,1,1,1,1,
// 	1,1,1,1,1,1,1,1, 0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0, 1,1,1,1,1,1,1,1,
// 	1,1,1,1,1,1,1,1, 0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0, 1,1,1,1,1,1,1,1,
// 	1,1,1,1,1,1,1,1, 0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0, 1,1,1,1,1,1,1,1,

// 	1,1,1,1,1,1,1,1, 0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0, 1,1,1,1,1,1,1,1,
// 	1,1,1,1,1,1,1,1, 0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0, 1,1,1,1,1,1,1,1,
// 	1,1,1,1,1,1,1,1, 0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0, 1,1,1,1,1,1,1,1,
// 	1,1,1,1,1,1,1,1, 0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0, 1,1,1,1,1,1,1,1,

// 	1,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,1,
// 	1,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,1,
// 	1,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,1,
// 	1,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,1,
// };

//64X64
int All_Textures[]=
{
	1,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,1,
	1,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,1,
	1,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,1,
	1,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,1,

	1,1,1,1,1,1,1,1, 0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0, 1,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,1,
	1,1,1,1,1,1,1,1, 0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0, 1,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,1,
	1,1,1,1,1,1,1,1, 0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0, 1,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,1,
	1,1,1,1,1,1,1,1, 0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0, 1,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,1,

	1,1,1,1,1,1,1,1, 0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0, 1,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,1,
	1,1,1,1,1,1,1,1, 0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0, 1,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,1,
	1,1,1,1,1,1,1,1, 0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0, 1,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,1,
	1,1,1,1,1,1,1,1, 0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0, 1,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,1,

	1,1,1,1,1,1,1,1, 0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0, 1,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,1,
	1,1,1,1,1,1,1,1, 0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0, 1,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,1,
	1,1,1,1,1,1,1,1, 0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0, 1,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,1,
	1,1,1,1,1,1,1,1, 0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0, 1,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,1,

	1,1,1,1,1,1,1,1, 0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0, 1,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,1,
	1,1,1,1,1,1,1,1, 0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0, 1,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,1,
	1,1,1,1,1,1,1,1, 0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0, 1,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,1,
	1,1,1,1,1,1,1,1, 0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0, 1,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,1,

	1,1,1,1,1,1,1,1, 0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0, 1,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,1,
	1,1,1,1,1,1,1,1, 0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0, 1,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,1,
	1,1,1,1,1,1,1,1, 0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0, 1,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,1,
	1,1,1,1,1,1,1,1, 0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0, 1,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,1,

	1,1,1,1,1,1,1,1, 0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0, 1,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,1,
	1,1,1,1,1,1,1,1, 0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0, 1,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,1,
	1,1,1,1,1,1,1,1, 0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0, 1,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,1,
	1,1,1,1,1,1,1,1, 0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0, 1,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,1,

	1,1,1,1,1,1,1,1, 0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0, 1,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,1,
	1,1,1,1,1,1,1,1, 0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0, 1,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,1,
	1,1,1,1,1,1,1,1, 0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0, 1,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,1,
	1,1,1,1,1,1,1,1, 0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0, 1,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,1,

	1,1,1,1,1,1,1,1, 0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0, 1,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,1,
	1,1,1,1,1,1,1,1, 0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0, 1,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,1,
	1,1,1,1,1,1,1,1, 0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0, 1,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,1,
	1,1,1,1,1,1,1,1, 0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0, 1,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,1,

	1,1,1,1,1,1,1,1, 0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0, 1,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,1,
	1,1,1,1,1,1,1,1, 0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0, 1,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,1,
	1,1,1,1,1,1,1,1, 0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0, 1,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,1,
	1,1,1,1,1,1,1,1, 0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0, 1,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,1,

	1,1,1,1,1,1,1,1, 0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0, 1,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,1,
	1,1,1,1,1,1,1,1, 0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0, 1,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,1,
	1,1,1,1,1,1,1,1, 0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0, 1,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,1,
	1,1,1,1,1,1,1,1, 0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0, 1,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,1,

	1,1,1,1,1,1,1,1, 0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0, 1,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,1,
	1,1,1,1,1,1,1,1, 0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0, 1,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,1,
	1,1,1,1,1,1,1,1, 0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0, 1,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,1,
	1,1,1,1,1,1,1,1, 0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0, 1,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,1,

	1,1,1,1,1,1,1,1, 0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0, 1,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,1,
	1,1,1,1,1,1,1,1, 0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0, 1,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,1,
	1,1,1,1,1,1,1,1, 0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0, 1,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,1,
	1,1,1,1,1,1,1,1, 0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0, 1,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,1,

	1,1,1,1,1,1,1,1, 0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0, 1,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,1,
	1,1,1,1,1,1,1,1, 0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0, 1,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,1,
	1,1,1,1,1,1,1,1, 0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0, 1,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,1,
	1,1,1,1,1,1,1,1, 0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0, 1,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,1,

	1,1,1,1,1,1,1,1, 0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0, 1,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,1,
	1,1,1,1,1,1,1,1, 0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0, 1,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,1,
	1,1,1,1,1,1,1,1, 0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0, 1,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,1,
	1,1,1,1,1,1,1,1, 0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0, 1,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,1,

	1,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,1,
	1,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,1,
	1,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,1,
	1,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,1,
};

typedef struct	s_info
{
	void	*mlx;
	void	*win;
	float	player_x;
	float	player_y;
	int		pixel_size;
	int		window_x;
	int		window_y;
	int		key_check[65536];

	int			*data;

	void        *img;
	int			img_width;
	int			img_height;
    char        *addr;

    int         bits_per_pixel;
    int         size_l;
    int         endian;

	int			**texture;
	double 		ZBuffer[WIDTH];
	double 		SBuffer[WIDTH];
}				t_info;

typedef struct	s_pos
{
	float x;
	float y;
}				t_pos;

typedef struct	s_sprite
{
	float	distance;
	float	pos_x;
	float	pos_y;
	int		index;
	float	angle;
}				t_sprite;

// int mapX=8, mapY=8, mapSize=64;
// int map[]=
// {
// 	1, 1, 1, 1, 1, 1, 1, 1,
// 	1, 0, 0, 0, 0, 0, 0, 1,
// 	1, 0, 0, 0, 0, 0, 0, 1,
// 	1, 0, 0, 0, 0, 0, 0, 1,
// 	1, 0, 0, 0, 1, 0, 0, 1,
// 	1, 0, 0, 0, 0, 0, 0, 2,
// 	1, 0, 0, 0, 0, 0, 0, 2,
// 	1, 1, 1, 1, 1, 1, 1, 1,
// };


//0 =공간, 1 = 벽, 2 = ?.
//3 = 동쪽, 4 = 서쪽, 5 = 남쪽, 6= 북쪽.
int mapX=10, mapY=10, mapSize=64;
int map[]=
{
	1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
	1, 0, 0, 0, 0, 0, 0, 0, 0, 1,
	1, 3, 0, 8, 0, 0, 1, 1, 1, 1,
	1, 0, 0, 0, 0, 0, 0, 0, 0, 1,
	1, 0, 0, 0, 1, 0, 0, 0, 0, 1,
	1, 0, 0, 0, 0, 0, 0, 0, 0, 1,
	1, 0, 0, 0, 0, 0, 0, 0, 0, 1,
	1, 0, 0, 0, 0, 0, 0, 0, 0, 1,
	1, 0, 0, 0, 0, 0, 0, 0, 0, 1,
	1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
};



void            my_mlx_pixel_put(t_info *info, int x, int y, int color)
{
    char   *dst;

    dst = info->addr + (y * info->size_l + x * (info->bits_per_pixel / 8));
    *(unsigned int*)dst = color;
}

void	bresenham(t_info *info, int startX, int startY, int finishX, int finishY, int color, int width)
{
	int x = startX;
	int y = startY;
	int Xfactor = finishX < startX ? -1 : 1;
	int Yfactor = finishY < startY ? -1 : 1;

	int w = abs(finishX - startX); // -300
	int h = abs(finishY - startY); // -200

	int f;

	for (int i = 0; i < width; i++)
	{
	if (w > h)
	{
		f = (2 * h) - w;
		for (x = startX; x != finishX; x += Xfactor)
		{
			if (f < 0)
			{
				f += 2 * h;
			}
			else
			{
				y += Yfactor;
				f += 2 * (h - w);
			}
			if (x >= 0 && x < info->window_x)
				my_mlx_pixel_put(info, x + i, y, color);
		}
	}
	else
	{
		f = (2 * w) - h;
		for (y = startY; y != finishY; y += Yfactor)
		{
			if (f < 0)
			{
				f += 2 * w;
			}
			else
			{
				x += Xfactor;
				f += 2 * (w - h);
			}
			if (y >= 0 && y < info->window_y)
				my_mlx_pixel_put(info, x + i, y, color);
		}
	}
	}
}

void	drawMap2D(t_info *info)
{
	int	x, y, xo, yo, color;
	for(y = 0; y < mapY; y++) //0, 1, 2, 3, 4, 5, 6, 7, 8, 9
	{
		for (x = 0; x < mapX; x++) //0, 1, 2, 3, 4, 5, 6, 7, 8, 9
		{
			if (map[y*mapX + x] == 1)
				color = 0x00FFFFFF;
			else
				color = 0x00000000;
			xo = x * mapSize; //0, 64 ,128 ,192, 256, 320
			yo = y * mapSize; //0, 64 ,128 ,192, 256, 320

			for (int i = 0; i < mapSize; i++)
			{
				for (int j = 0; j < mapSize; j++)
				{
					my_mlx_pixel_put(info, xo + i, yo + j, color);
				}
			}
		}
	}
}

void	drawPlayer(t_info *info)
{
	for(int x = 0; x < info->pixel_size; x++)
	{
		for(int y = 0; y < info->pixel_size; y++)
			my_mlx_pixel_put(info, info->player_x + x, info->player_y + y, 0x00FFFF00); //플레이어 생성
	}

	int finX = info->player_x + pdx * 5;
	int finY = info->player_y + pdy * 5;
	bresenham(info, info->player_x, info->player_y, finX, finY, 0x00FFFF00, 1);
}

int Button_down(int keycode, t_info *info)
{
	if (keycode >= 300 && keycode != KEY_ESC)
		return (-1);
	info->key_check[keycode] = 1;
	return (0);
}

int Button_release(int keycode, t_info *info)
{
	if (keycode >= 300 && keycode != KEY_ESC)
		return (-1);
	info->key_check[keycode] = 0;
	return (0);
}

void	init_map_black(t_info *info)
{
	for(int x = 0; x < info->window_x; x++)
	{
		for(int y = 0; y < info->window_y; y++)
		{
			my_mlx_pixel_put(info, x, y, 0x00000000); //맵 전체를 검은색으로 초기화
		}
	}
}

void 	draw_lines(t_info *info)
{
	int		i;
	int		j;
	int		color;

	color = 0x00454545;

	i = 0;
	while (i < mapX)
	{
		bresenham(info, i * mapSize, 0, i * mapSize, (mapX * mapSize), color, 1);
		i++;
	}
	j = 0;
	while (j < mapY)
	{
		bresenham(info, 0, j * mapSize, (mapY * mapSize), j * mapSize, color, 1);
		j++;
	}
}

float dist(float ax, float ay, float bx, float by)
{
	return ( sqrt ((bx - ax) * (bx - ax) + (by - ay) * (by - ay)));
}

float degToRad(float a) { return a *M_PI/180.0;}
float FixAng(float a) { if (a>359) { a -= 360;} if (a<0) { a+= 360;} return a;}

void	drawRays3D(t_info *info)
{
	int		r, mx, my, mp, dof;
	float	rx,ry, ra, xo, yo, disT;
	int		color;
	color = 0x00FF0000;

	//pa : 플레이어가 바라보는 각도 (0 ~ 6)
	//rx, ry : 2D 맵에서 광선이 벽에 닿을 때의 위치.
	//pa를 ra로 변환.

	ra=pa - DR * 30;

	if (ra < 0) { ra+= 2* PI; }
	if(ra > 2*PI) { ra-= 2 * PI; }

	for(r = 0; r < 60; r++)
	{
		// 수평선(horizontal)
		dof = 0;
		float disH = 1000000, hx = info->player_x, hy=info->player_y;
		float aTan = -1/tan(ra);
		if (ra > PI)
		{
			ry = (((int)info->player_y >> 6)<<6) - 0.0001;
			rx = (info->player_y - ry) * aTan + info->player_x;
			yo = -64;
			xo = -yo * aTan;
		}
		if (ra < PI)
		{
			ry = (((int)info->player_y >> 6) << 6) + 64;
			rx = (info->player_y - ry) * aTan + info->player_x;
			yo = 64;
			xo = -yo * aTan;
		}
		while (dof < 8)
		{
			//printf("rx: %f\n", rx);
			//printf("mx: %d\n", mx);
			mx = (int)(rx) >> 6;
			my = (int) (ry)>>6;
			mp = my * mapX + mx;
			if (mp > 0 && mp < mapX * mapY && map[mp] == 1) // 벽일 때만 레이에 부딪친다.
			{
				hx = rx;
				hy = ry;
				disH = dist(info->player_x, info->player_y, hx, hy);
				dof = 8;
			}
			else
			{
				rx += xo;
				ry += yo;
				dof += 1;
			}

		}

		//수직선(Vertical) 체크.
		dof = 0;
		float disV = 1000000, vx = info->player_x, vy=info->player_y;
		float nTan = -tan(ra);
		if (ra > P2 && ra < P3)
		{
			rx = (((int)info->player_x >> 6)<<6) - 0.0001;
			ry = (info->player_x - rx) * nTan + info->player_y;
			xo = -64;
			yo = -xo * nTan;
		}
		if (ra < P2 || ra > P3)
		{
			rx = (((int)info->player_x >> 6) << 6) + 64;
			ry = (info->player_x - rx) * nTan + info->player_y;
			xo = 64;
			yo = -xo * nTan;
		}
		if (ra == 0 || ra == PI) { rx = info->player_x; ry = info->player_y; dof = 8;}
		while (dof < 8)
		{
			mx = (int)(rx) >> 6;
			my = (int) (ry)>>6;
			mp = my * mapX + mx;
			if (mp > 0 && mp < mapX * mapY && map[mp] == 1)
			{
				vx = rx;
				vy = ry;
				disV = dist(info->player_x, info->player_y, vx, vy);
				dof = 8;
			}
			else
			{
				rx += xo;
				ry += yo;
				dof += 1;
			}

		}

		int rayHitVertical = 0;
		//vertical wall hit
		if (disV < disH) { rx = vx; ry = vy; disT = disV; color = 0x00FFAA00; rayHitVertical = 1; }

		//horizontal wall hit
		if (disH < disV) { rx = hx; ry = hy; disT = disH; color = 0x00FFCC00;}

		//bresenham(info, info->player_x, info->player_y, rx, ry, color, 1);

		//----3D 그리기-----
		float ca = pa - ra;
		if (ca < 0) { ca+= 2* PI; }
		if (ca > 2*PI) { ca-= 2 * PI; }
		disT = disT * cos(ca);

		//printf("disT: %f\n", disT);

		float lineH = (mapSize * 640)/disT;
		if (lineH > 640) { lineH = 640; }
		float lineO = 320 - lineH/2;

		float ty_step = 64.0 / (float)lineH;  //원래 32, 지금은 64X64라 64.0으로 변경
		float ty_off=0;

		if (lineH >= 640)
		{
			ty_off=(lineH-640)/2.0;
			lineH = 640;
		}

		float ty = ty_off*ty_step;
		//printf("ty: %f\n", ty);

		float tx;

		if (disV > disH) { tx=(int)(rx / 1.0) % 64;} //32X16: (4, 16), 32X32:(2, 32) 64X64:(1, 64)
		else 			 { tx=(int)(ry / 1.0) % 64;}

		// if (ra > 0.5 && ra < 4.5 ) { tx= 63-tx; }
		//서쪽과, 남쪽은 제외 해야함.
		//조건: info->player_x < rx (서)
		//조건 : info->player_y > ry (남)
		// if (ra > 1.0 && ra < 4.5 )
		// {
			//printf("ra: %f\n", ra);
			//printf("rayHitVertical: %d\n", rayHitVertical);
			if (rayHitVertical == 1) //동서
			{
				if (info->player_x > rx) //동
					tx= 63-tx;
			}
			else
				if (info->player_y < ry) //북
					tx= 63-tx;
		//}
		//tx= 63-tx;
		//printf("ra: %f\n", ra);

		//if ((disV < disH)) { tx= 63-tx; }



		//lineO += 90;

		int texNum;
		//벽 (텍스쳐 적용)
		for (int y = 0; y < lineH; y++)
		{
			// int c;
			// if ((int)ty * 64 + (int)tx < 4096) // (32, 512), (32, 1024), (64, 4096)
			// 	c = All_Textures[(int)ty * 64 + (int)tx]; //(int)ty * 32 + (int)tx , (int)ty + (int)tx * 32

			//ty += ty_step;
			// if (rayHitVertical == 1) //동서
			// {
			// 	if (c == 0) //텍스쳐 배열의 0
			// 	{
			// 		if (info->player_x > rx) //동쪽
			// 			color = 0x000000000; //검정
			// 		else //서쪽
			// 			color = 0x000FFFF00; //노랑
			// 	}
			// 	else if (c == 1)//텍스쳐 배열의 1
			// 	{
			// 		if (info->player_x > rx) //동쪽
			// 			color = 0x000FFFFFF; //하양
			// 		else
			// 			color = 0x000FFFFFF; //하양
			// 	}
			// }
			// else //남북
			// {
			// 	if (c == 0)
			// 	{
			// 		if (info->player_y > ry) //남쪽
			// 			color = 0x00066ff33;//연두
			// 		else //북쪽
			// 			color = 0x00000FFFF;//하늘색
			// 	}
			// 	else if (c == 1)
			// 	{
			// 		color = 0x000ff99ff; //밝은 보라
			// 	}
			// }
			//rx, vx, xo, mx

			if (rayHitVertical == 1) //동서
			{
				if (info->player_x < rx)
					texNum = 0;  //동
				else
					texNum = 1;  //서
			}
			else
			{
				if (info->player_y < ry)
					texNum = 2; //남
				else
					texNum = 3; //북
			}


			//printf("texNum:%d\n", texNum);

			color = info->texture[texNum][(int)ty * texWidth + (int)tx];
			ty += ty_step;

			//printf("ty: %f\n", ty);

			for(int aa = 0; aa < 16; aa++)
			{
				//텍스쳐상의 좌표는 아까 구한 벽상의
				//좌표에 TEX_SIZE / wall_height 만큼
				//곱해주면 된다.

				//풀 해상도 벽  조건도 16으로 바꿈(원래 8)
				my_mlx_pixel_put(info, r * 16 + aa , y * (info->window_x / info->window_y) +lineO, color);

				//기본 버전 벽.
				//my_mlx_pixel_put(info, r * 8 + aa + 530 , y+lineO, color);

			}
		}

		// 벽
		//bresenham(info, (r * 8+530), lineO, (r * 8+530), lineH + lineO, color, 8);



		//풀 화면 천장, 바닥
		bresenham(info, (r * 16), 0, (r * 16), lineO, 0x0040E0D0, 16);
		bresenham(info, (r * 16), lineH + lineO, (r * 16), info->window_y, 0x00FF0000, 16);


		//천장
		//bresenham(info, (r * 8+530), 0, (r * 8+530), lineO, 0x0040E0D0, 8);

		// 바닥
		//bresenham(info, (r * 8+530), lineH + lineO, (r * 8+530), 320, 0x00FF0000, 8);

		ra += DR; if (ra < 0) { ra+= 2* PI; } if(ra > 2*PI) { ra-= 2 * PI; }
	}
}

t_pos	bresen(t_info *info, float startX, float startY, float pdx, float pdy)
{
	t_pos pos;

	float x = startX;
	float y = startY;
	float finishX = startX + pdx * 100;
	float finishY = startY + pdy * 100;
	float Xfactor = finishX < startX ? -0.1f : 0.1f;
	float Yfactor = finishY < startY ? -0.1f : 0.1f;

	float w = abs(finishX - startX); // -300
	float h = abs(finishY - startY); // -200

	float f;

	if (w > h)
	{
		f = (2 * h) - w;
		for (x = startX; x != finishX; x += Xfactor)
		{
			if (f < 0)
			{
				f += 2 * h;
			}
			else
			{
				y += Yfactor;
				f += 2 * (h - w);
			}
			if (map[((int)y / mapSize)*mapX + ((int)x / mapSize)] == 1)
			{
				pos.x = x;
				pos.y = y;
				return (pos);
			}
		}
	}
	else
	{
		f = (2 * w) - h;
		for (y = startY; y != finishY; y += Yfactor)
		{
			if (f < 0)
			{
				f += 2 * w;
			}
			else
			{
				x += Xfactor;
				f += 2 * (w - h);
			}
			if (map[((int)y / mapSize)*mapX + ((int)x / mapSize)] == 1)
			{
				pos.x = x;
				pos.y = y;
				return (pos);
			}
		}
	}
}

t_pos	bresen2(t_info *info, float startX, float startY, float pdx, float pdy)
{
	t_pos pos;

	float x = startX;
	float y = startY;
	float finishX = startX + pdx * 100;
	float finishY = startY + pdy * 100;
	float Xfactor = finishX < startX ? -0.1f : 0.1f;
	float Yfactor = finishY < startY ? -0.1f : 0.1f;

	float w = abs(finishX - startX); // -300
	float h = abs(finishY - startY); // -200

	float f;

	if (w > h)
	{
		f = (2 * h) - w;
		for (x = startX; x != finishX; x += Xfactor)
		{
			if (f < 0)
			{
				f += 2 * h;
			}
			else
			{
				y += Yfactor;
				f += 2 * (h - w);
			}
			if ((x >= (mapX * mapSize) || y >= (mapY * mapSize)) || (x <= 0 || y <= 0))
			{
				pos.x = 0;
				pos.y = 0;
				return (pos);
			}
			if (map[((int)y / mapSize)*mapX + ((int)x / mapSize)] == 8)
			{
				pos.x = x;
				pos.y = y;
				return (pos);
			}
		}
	}
	else
	{
		f = (2 * w) - h;
		for (y = startY; y != finishY; y += Yfactor)
		{
			if (f < 0)
			{
				f += 2 * w;
			}
			else
			{
				x += Xfactor;
				f += 2 * (w - h);
			}
			if ((x >= (mapX * mapSize) || y >= (mapY * mapSize)) || (x <= 0 || y <= 0))
			{
				pos.x = 0;
				pos.y = 0;
				return (pos);
			}
			if (map[((int)y / mapSize)*mapX + ((int)x / mapSize)] == 8)
			{
				pos.x = x;
				pos.y = y;
				return (pos);
			}
		}
	}
}

//bresen3 = 플레이어와 스프라이트 충돌 지점이 멀어지면, 각도가 이상해짐, 그래서 거리를 줄여서 계산해야하는데, 그 위치를 구해줌.(거리 = 128)
t_pos	bresen3(t_info *info, float startX, float startY, float finishX, float finishY)
{
	t_pos pos;

	float x = startX;
	float y = startY;
	float Xfactor = finishX < startX ? -0.1f : 0.1f;
	float Yfactor = finishY < startY ? -0.1f : 0.1f;

	float w = abs(finishX - startX); // -300
	float h = abs(finishY - startY); // -200

	float f;

	if (w > h)
	{
		f = (2 * h) - w;
		for (x = startX; x != finishX; x += Xfactor)
		{
			if (f < 0)
			{
				f += 2 * h;
			}
			else
			{
				y += Yfactor;
				f += 2 * (h - w);
			}
			if ((x >= (mapX * mapSize) || y >= (mapY * mapSize)) || (x <= 0 || y <= 0))
			{
				pos.x = 0;
				pos.y = 0;
				return (pos);
			}
			if ((int)dist(x, y, finishX, finishY) == 160 || (int)dist(x, y, finishX, finishY) == 161)
			{
				pos.x = x;
				pos.y = y;
				return (pos);
			}
		}
	}
	else
	{
		f = (2 * w) - h;
		for (y = startY; y != finishY; y += Yfactor)
		{
			if (f < 0)
			{
				f += 2 * w;
			}
			else
			{
				x += Xfactor;
				f += 2 * (w - h);
			}
			if ((x >= (mapX * mapSize) || y >= (mapY * mapSize)) || (x <= 0 || y <= 0))
			{
				pos.x = 0;
				pos.y = 0;
				return (pos);
			}
			if ((int)dist(x, y, finishX, finishY) == 160 || (int)dist(x, y, finishX, finishY) == 161)
			{
				pos.x = x;
				pos.y = y;
				return (pos);
			}
		}
	}
}

t_pos	bresen4(t_info *info, float sx, float sy, float fx, float fy)
{
	//스프라이트 중앙에서 플레이어까지 선을 잇고, 그 뒤로 길이 160이 될때까지 선을 긋는다.
	//(sx, sy, px, py);
	t_pos pos;

	float x = sx;
	float y = sy;
	float pdx = fx - sx;
	float pdy = fy - sy;
	float finishX = sx + pdx * 100;
	float finishY = sy + pdy * 100;
	float Xfactor = finishX < sx ? -0.1f : 0.1f;
	float Yfactor = finishY < sy ? -0.1f : 0.1f;

	float w = abs(finishX - sx); // -300
	float h = abs(finishY - sy); // -200

	float f;

	if (w > h)
	{
		f = (2 * h) - w;
		for (x = sx; x != finishX; x += Xfactor)
		{
			if (f < 0)
			{
				f += 2 * h;
			}
			else
			{
				y += Yfactor;
				f += 2 * (h - w);
			}
			if ((x >= (mapX * mapSize) || y >= (mapY * mapSize)) || (x <= 0 || y <= 0))
			{
				pos.x = 0;
				pos.y = 0;
				return (pos);
			}
			if ((int)dist(x, y, sx, sy) == 160 || (int)dist(x, y, sx, sy) == 161)
			{

				pos.x = x;
				pos.y = y;
				return (pos);
			}
		}
	}
	else
	{
		f = (2 * w) - h;
		for (y = sy; y != finishY; y += Yfactor)
		{
			if (f < 0)
			{
				f += 2 * w;
			}
			else
			{
				x += Xfactor;
				f += 2 * (w - h);
			}
			if ((x >= (mapX * mapSize) || y >= (mapY * mapSize)) || (x <= 0 || y <= 0))
			{
				pos.x = 0;
				pos.y = 0;
				return (pos);
			}
			if ((int)dist(x, y, sx, sy) == 160 || (int)dist(x, y, sx, sy) == 161)
			{
				pos.x = x;
				pos.y = y;
				return (pos);
			}
		}
	}
}

void	sort_wall(t_info *info)
{
	double first;
	double second;
	for (int i = 0; i < 240; i++)
	{
		for (int j = 0; j < 240 - 1; j++)
		{
			if (info->ZBuffer[j] > info->ZBuffer[j + 1])
			{
				first = info->ZBuffer[j];
				second = info->ZBuffer[j + 1];
				info->ZBuffer[j] = second;
				info->ZBuffer[j + 1] = first;
			}
		}
	}
	//return (info->ZBuffer[0]);
}

void	sort_sprite(t_info *info, int sStack)
{
	double first;
	double second;
	for (int j = 0; j < sStack - 1; j++)
	{
		if (info->SBuffer[j] > info->SBuffer[j + 1])
		{
			first = info->SBuffer[j];
			second = info->SBuffer[j + 1];
			info->SBuffer[j] = second;
			info->SBuffer[j + 1] = first;
		}
	}
}

float worldx = 0;
float worldy = 0;

void	drawRays2D(t_info *info)
{
	float	ra = pa;
	int		color, color2, color3;
	color = 0x00FF0000;
	color2 = 0x00FFFF00;
	color3 = 0x00FFFFFF;


	t_pos pos; //광선이 벽에 충돌한 위치
	t_pos pos2; //광선이 스프라이트에 충돌한 위치

	float disV = 0;
	float disH = 0;

	float disSpriteV = 0;
	float disSpriteH = 0;

	int flagVer = 0;
	int spriteFlagVer = 0;

	int sStack = 0;

	int sTemp = 0;

	float tempx = 0;
	float tempy = 0;

	//1D Zbuffer (플레이어와 스프라이트의 길이를 모아놓은 배열) => 모으고 정렬한다. -> 그러면 거리가 제일가까운 길이를 알수 있다.

	//시야가 60이니까, 반시계 방향으로 30각도 만큼만 빼서 START!
	ra -= 30 * DR;
	for (int i = 0; i < info->window_x/2; i++)
	{
		//px, py : 지도상에서 플레이어의 위치.
		//pdx pdy : 플레이어 앵글의 각 x, y 증가값. (증가 위치는 임시로 +5라고 했음. (딱히 상관 없다.))

		//이거 초기화 해야함.
		float pdx_a = cos(ra) * 5;
		float pdy_a = sin(ra) * 5;

		pos = bresen(info, info->player_x, info->player_y, pdx_a, pdy_a); //맵에서 벽을 구별해서 충돌. (충돌위치를 전달)
		pos2 = bresen2(info, info->player_x, info->player_y, pdx_a, pdy_a); //맵에서 스프라이트만 구별해서 충돌

		//printf("pdx[%d]: %f, pos2.y: %f\n", i, pdx_a, pos2.y);

		//오차 맞추기. (오차 +- 1)
		if (pos.y < info->player_y) //벽의 y위치가 플레이어보다 높이 있을 시.
			pos.y += 1;
		if (pos.x < info->player_x)
			pos.x += 1;

		if (pos2.y < info->player_y) //벽의 y위치가 플레이어보다 높이 있을 시.
			pos2.y += 1;
		if (pos2.x < info->player_x)
			pos2.x += 1;


		if ((int)pos.x % mapSize == 0) //수직선 hit!
		{
			bresenham(info, info->player_x, info->player_y, pos.x, pos.y, color, 1);
			disV = dist(info->player_x, info->player_y, pos.x, pos.y);
			disH = 0;
		}
		else if ((int)pos.y % mapSize == 0) //수평선 hit!
		{
			bresenham(info, info->player_x, info->player_y, pos.x, pos.y, color2, 1);
			disH = dist(info->player_x, info->player_y, pos.x, pos.y);
			disV = 0;
		}

		// color = 회색, color2 = 노란색, color3 = 하얀색
		//가끔 두 조건을 충족하는 경우 때문에 에러 발생.
		// 이전 반복문이 수평선 충돌인지, 수직선 충돌인지 확인하는 변수를 조건으로 추가.
		// 바로 flagVer(이게 1이면 이전 반복문은 수직선 충돌, 0이면 수평선 충돌)
		color3 = 0x00FF0000;
		if ((int)pos.x % mapSize == 0 && (int)pos.y % mapSize == 0)
		{
			if (flagVer == 1)
			{
				bresenham(info, info->player_x, info->player_y, pos.x, pos.y, color3, 1);
				disV = dist(info->player_x, info->player_y, pos.x, pos.y);
				disH = 0;
			}
			else if(flagVer == 0)
			{
				bresenham(info, info->player_x, info->player_y, pos.x, pos.y, color3, 1);
				disH = dist(info->player_x, info->player_y, pos.x, pos.y);
				disV = 0;
			}
		}

		if (disH == 0) {	flagVer = 1; }
		else if (disV == 0) { flagVer = 0; }


		int itsSprite = 0;

		//스프라이트 담당.
		if ((int)pos2.x % mapSize == 0) //수직선 hit!
		{
			bresenham(info, info->player_x, info->player_y, pos2.x, pos2.y, color2, 1);
			disSpriteV = dist(info->player_x, info->player_y, pos2.x, pos2.y);
			disSpriteH = 0;
			itsSprite = 1;
		}
		else if ((int)pos2.y % mapSize == 0) //수직선 hit!
		{
			bresenham(info, info->player_x, info->player_y, pos2.x, pos2.y, color3, 1); //색이 더 어두워짐.
			disSpriteH = dist(info->player_x, info->player_y, pos2.x, pos2.y);
			disSpriteV = 0;
			itsSprite = 1;
		}

		int errorflag = 0 ;
		if ((int)pos2.x % mapSize == 0 && (int)pos2.y % mapSize == 0)
		{
			errorflag = 1;
			if (spriteFlagVer == 1)
			{
				disSpriteV = dist(info->player_x, info->player_y, pos2.x, pos2.y);
				disSpriteH = 0;
			}
			else if(spriteFlagVer == 0)
			{
				disSpriteH = dist(info->player_x, info->player_y, pos2.x, pos2.y);
				disSpriteV = 0;
			}
		}

		if (disSpriteH == 0) {	spriteFlagVer = 1; }
		else if (disSpriteV == 0) { spriteFlagVer = 0; }


		//3D 구현.
		//위에서 구한 광선이 벽에 닿은 위치(pos.x, pos.y)를 이용해 3D 벽을 구현.

		//광선이 벽의 수직선(Vertical) 수평선(Horizontal)에 맞았는지 구분해야 한다.
		//disV, disH 중에 더 큰 것이 [진짜 거리]이므로 disT(distanceTrue)에 값을 입력.
		int		rayHitVertical = 0;
		float disT = 0;
		if (disV > disH)
		{
			disT = disV;
			rayHitVertical = 1;
		}
		else if (disH > disV)
		{
			disT = disH;
		}

		// 벽의 뭉툭함을 없애줌.
		// pa = (플레이어 시아의 중앙선의 각도)
		// ra = 현재 반복문에서 진행중인 광선의 각도
		// ca = pa와 ra 광선 사이의 끼인각.
		// 어안렌즈 효과.
		// 카메라가 카메라 평면을 향하는 벡터와 광선 벡터의 끼인 각을 베타로 두고 광선을 발사해 얻은 거리에 cos(베타) 값을 곱하면 된다.
		// 내가 구현한 방식은 카메라 평면을 향하는 벡터에 단위벡터를 구해 광선벡터를 구하는 것이므로 두 벡터의 크기를 구해서 cos(베타) 값을 구할 수 있다.
		float ca = pa - ra;
		if (ca < 0) { ca+= 2* PI; }
		if (ca > 2*PI) { ca-= 2 * PI; }
		disT = disT * cos(ca);

		//벽의 높이, 오프셋 계산.
		float lineH = (mapSize * info->window_y)/disT;  //원래 640, 지금은 window_y

		//동서남북 구분하고 그에 따른 텍스트 넘버 부여.
		int texNum = 0;
		if (rayHitVertical == 1)
		{
			if (info->player_x < pos.x)
				texNum = 0;  //동
			else
				texNum = 1;  //서
		}
		else
		{
			if (info->player_y < pos.y)
				texNum = 2; //남
			else
				texNum = 3; //북
		}

		float tx, ty;
		float ty_off = 0;
		float ty_step = 64.0 / (float)lineH;

		//구현해야 할 벽의 크기가 윈도우 화면보다 클 시.
		//즉, 플레이어가 벽에 딱 붙었을 시.
		//너무 가까이 붙으면 벽의 윗부분과 아래는 시야에 보이지 않는다.
		//즉 텍스쳐 배열의 y의 시작값(ty_off)을 다음으로 옳긴다.
		if (lineH >= info->window_y)
		{
			//lineH - info->window_y로 불필요한 벽의 윗부분을 버린다.
			//이후 2로 나눠서 불필요한 벽의 아래부분 마저 버린다.
			//결과적으로 필요한 벽의 중앙 부분만 남음.
			ty_off=(lineH-info->window_y) / 2;

			//구현해야 할 벽의 높이가 윈도우 화면보다 크면 안되므로 고정해준다.
			lineH = info->window_y;
		}
		float lineO = (info->window_y / 2) - lineH / 2;

		//ty는 텍스쳐 배열에서 y배열을 얼만큼 아래로 옳길지 결정.
		ty = ty_off*ty_step;

		//tx는 텍스쳐 배열에서 x배열을 얼만큼 아래로 옳길지 결정.
		if (rayHitVertical == 0) //광선이 수평선(Horizontal) 벽에 맞았으니, x좌표가 필요.
			tx = (int)pos.x % mapSize; //벽
		else //광선이 수평선(Vertical) 벽에 맞았으니, y좌표가 필요.
			tx = (int)pos.y % mapSize;

		//printf("xx: %d\n", xx);
		for (int aa = 0; aa < lineH; aa++)
		{
			//color = info->texture[texNum][(int)ty * texWidth + (int)tx];
			color = info->texture[texNum][(int)ty * texWidth + (int)tx];
				//최소화 벽 그리기.
				//my_mlx_pixel_put(info, i + 530 + bb , lineO + aa, color);

				//풀해상도 벽 그리기.
				//my_mlx_pixel_put(info, i * xx + bb , lineO + aa, color);

				my_mlx_pixel_put(info, i+ 512, lineO + aa, color);
			ty += ty_step; //텍스쳐 배열 한칸 아래로 이동.
		}

		info->ZBuffer[i] = disT; //Z버퍼에 벽과 플레이어의 거리를 담는다.
		//printf("[%d]: %f\n", i, info->ZBuffer[i]);
		if (i == 239)
		{
			sort_wall(info);
			for(int z = 0; z < 240; z++)
			{
				//printf("[%d]: %f\n", z, info->ZBuffer[z]);
			}
			//벽과 제일 가까운 거리: info->ZBuffer[0];
		}

		//천장과 바닥 1024광선
		bresenham(info, i + 512, 0, i + 512, lineO, 0x0040E0D0, 1); //천장
		bresenham(info, i + 512, lineH + lineO, i + 512, info->window_y, 0x00FF0000, 1); //바닥


		//천장과 바닥(풀해상도)
		// bresenham(info, i, 0, i, lineO, 0x0040E0D0, 8);
		// bresenham(info, i, lineH + lineO, i, info->window_y, 0x00FF0000, 8);

		//이 아래부터는 스프라이트(Sprite) 담당.
		if (itsSprite == 1)
		{
			rayHitVertical = 0;
			disT = 0;
			if (disSpriteV > disSpriteH)
			{
				disT = disSpriteV;
				rayHitVertical = 1;
			}
			else if (disSpriteH > disSpriteV)
			{
				disT = disSpriteH;
			}

			disT = disT * cos(ca);
			// lineH = (mapSize * info->window_y)/disT;

			//스프라이트의 중앙 뿐만 아니라, 다른 곳에 광선이 닿아도.
			//스프라이트의 중앙과의 거리를 알 수 있어야 한다.
			//맵을 이용하자.
			sort_sprite(info, sStack);
			info->SBuffer[sStack] = disT; //S버퍼에 스프라이트와 플레이어의 거리를 담는다.
			sStack++;

			float sx = pos2.x;
			float sy = pos2.y;

			if ((int)pos2.x % mapSize != 0)
			{
				float min = (int)pos2.x % mapSize;
				sx = pos2.x - min;
			}
			else if ((int)pos2.y % mapSize != 0)
			{
				float min = (int)pos2.y % mapSize;
				sy = pos2.y - min;
			}

			// printf("[%d]: %f\n", i, info->SBuffer[0]);
			//플레이어와 스프라이트 거리의 최소값 = info->SBuffer[0]
			//플레이어와 스프라이트 거리의 중앙값 = info->SBuffer[sStack / 2]
			//플레이어와 스프라이트 거리의 최대값 = info->SBuffer[sStack]

			texNum = 0;
			if (rayHitVertical == 1 && errorflag == 0)
			{
				if (info->player_x < pos2.x)
				{
					texNum = 0;  //동
					sx+=32;
					sy+=32;
				}
				else
				{
					texNum = 1;  //서
					sx-=32;
					sy+=32;
				}
			}
			else if (rayHitVertical == 0 && errorflag == 0)
			{
				if (info->player_y < pos2.y)
				{
					texNum = 2; //남
					sy+=32;
					sx+=32;
				}
				else
				{
					texNum = 3; //북
					sy-=32;
					sx+=32;
				}
			}
			if (errorflag == 1)
			{
				if (info->player_x < pos2.x && info->player_y > pos2.y) //남서쪽
				{
					sy-=32;
					sx+=32;
				}
				else if (info->player_x < pos2.x && info->player_y < pos2.y) //북서쪽
				{
					sy+=32;
					sx+=32;
				}
				else if (info->player_x > pos2.x && info->player_y < pos2.y) //북동쪽
				{
					sy+=32;
					sx-=32;
				}
				else if (info->player_x > pos2.x && info->player_y > pos2.y) //남동쪽
				{
					sy-=32;
					sx-=32;
				}
				//printf("sx: %f, sy: %f\n", sx, sy);
			}

			disT = dist(info->player_x, info->player_y, sx, sy);

			float lineH = (mapSize * info->window_y)/disT;

			//끼인각 구하기(https://sukhwan.tistory.com/49), (https://www.notion.so/Ray-casting-7-The-Sprite-f7e4cd28a6024d5fa7b0b6bc2089788d)

			float gx;
			float gy;
			// if (info->player_x > sx)
			// 	gx = info->player_x - sx;
			// else
			// 	gx = sx - info->player_x;

			// if (info->player_y > sy)
			// 	gy = info->player_y - sy;
			// else
			// 	gy = sy - info->player_y;

			t_pos new_pos;
			//bresen3: 플레이어에서 스프라이트 중앙까지 선을 긋는다. 그 과정에서 거리가 160이 되면, 그 위치를 반환.
			//bresen4: 스프라이트 중앙에서 플레이어가 있는 방향으로 선을 긋는다.
            //이 선은 플레이어를 지나쳐, 거리 160이 되면, 그 위치를 반환한다.
			if (disT >= 160) //거리가 멀어지면 각도가 더 벌어짐.
				new_pos = bresen3(info, info->player_x, info->player_y, sx, sy);
			else
				new_pos = bresen4(info, sx, sy, info->player_x, info->player_y);
			//알파: 플레이어와 스프라이트의 중앙을 잇는 선의 각도. (x축이 기준)
			gx = sx - new_pos.x;
			gy = sy - new_pos.y;
			// gx = sx - info->player_x;
			// gy = sy - info->player_y;

			double alpha = atan2(gy, gx);
			if (alpha < 0)
				alpha = 360 * (PI/180) + alpha;
			//베타: 플레이어와 레이캐스트 충돌 지점을 잇는 선의 각도. (x축이 기준)
			gx = pos2.x -  new_pos.x;
			gy = pos2.y -  new_pos.y;
			// gx = pos2.x -  info->player_x;
			// gy = pos2.y -  info->player_y;
			double beta = atan2(gy, gx);
			if (beta < 0)
				beta = 360 * (PI/180) + beta;

			//세타: 스프라이트 중앙과 레이캐스트 충돌 지점을 잇는 선의 각도. (x축이 기준)
			gx = pos2.x -  sx;
			gy = pos2.y -  sy;
			double ceta = atan2(gy, gx);
			if (ceta < 0)
				ceta = 360 * (PI/180) + ceta;

			//x4 = 끼인각.
			double x4 = 0;
			x4 = beta - alpha;

			//printf("[%d]: %f\n", i, tan(x4));
			//이건 뭘까?
			//printf("[%d]: %f\n", i, x4);

			if (x4 < -180 * (PI/180))
				x4 += 360 * (PI/180);
			if (x4 > 180 * (PI/180))
				x4 =  x4 - (360 * (PI/180));


			//스프라이트 중심에서 충돌지점 까지의 거리.
			float cc = dist(sx, sy, pos2.x, pos2.y);

			//라디안 -> 디그리 = 각도 * (180/PI);

			tx = 0; ty = 0;
			ty_off = 0;

			if (lineH >= info->window_y)
			{
				ty_off=(lineH-info->window_y) / 2;
				lineH = info->window_y;
			}

			lineO = (info->window_y / 2) - lineH / 2;

			ty_step = 120 / lineH;

			ty = ty_off*ty_step;

			// tx = x4 / (DR / 4);
			// tx = tx + 60;

			//printf("[%d]: x4: %f\n", i, x4 * (180/PI));


			//문제점.
			//거리가 가까워지면 tx값도 더 커짐.

			//printf("[%d]: %f\n", i, x4);
			tx = x4 / (DR / 8.53f);

			//거리 160기준. tx = -130 ~ 130이 나온다.
			//즉, 벽의 가로 길이는 260
			tx = tx * (120.0/ 240.0);
			//if (i == 1)
				printf("tx: %f\n", tx);

			tx = tx + 60;
			// 벽의 길이와, 스프라이트 텍스쳐의 길이 비율대로 수치 조정.
			//tx = tx * (120.0/ 240.0);
			//printf("x4[%d]: %f, tx: %f\n", i, x4, tx);
			//tx = tx * 0.5f;

			// tx = tx * (mapSize/ 120.0);
			// tx = tx + 60;
			// tx = (int)tx % (120);

			//printf("dist %f도.\n", disT);

			for (int aa = 0; aa < lineH; aa++)
			{
				texNum = 4; //스프라이트 텍스쳐 번호가 4.

				//텍스쳐팩 스프라이트 높이 너비 가져오기.
				color = info->texture[texNum][(int)ty * 120 + (int)tx];

				for (int bb = 0; bb < 1; bb++) //왜 인지 이 반복문을 안 하면, 색깔처리 안 됨.
				{
					if( (color & 0x00ffffff) == 0) continue;

					if (tx >= 0 && tx <= 120)
						my_mlx_pixel_put(info, i + 512, lineO + aa, color);
				}

				ty += ty_step;
			}
		}

		//ra += DR / 4; //현재 Radians(파이각)이 6.28이므로 파이/360의 값인 DR을 1도로 가정하고 계산. DR = 0.017
		ra += DR / 8.53f;
		//ra += DR / 17.06f;
		if (ra < 0) { ra+= 2* PI; } if(ra > 2*PI) { ra-= 2 * PI; }
	}
}

void    load_image(t_info *info, int *texture, char *path)
{
    info->img = mlx_xpm_file_to_image(info->mlx, path, &info->img_width, &info->img_height);
	info->data = (int *)mlx_get_data_addr(info->img, &info->bits_per_pixel, &info->size_l, &info->endian);
	for (int y = 0; y < info->img_height; y++)
    {
        for (int x = 0; x < info->img_width; x++)
        {
			//printf("[%d]: %d\n", info->img_width * x + y, info->data[info->img_width * x + y]);

			texture[info->img_width * y + x] = info->data[info->img_width * y + x];

        }
    }
    mlx_destroy_image(info->mlx, info->img);
}

void    load_texture(t_info *info)
{
    //load_image(info, info->texture[0], "textures/grass.xpm");
	load_image(info, info->texture[0], "textures/east.xpm");
    load_image(info, info->texture[1], "textures/west.xpm");
    load_image(info, info->texture[2], "textures/south.xpm");
    load_image(info, info->texture[3], "textures/north.xpm");

	// load_image(info, info->texture[0], "textures/wall_e.xpm");
    // load_image(info, info->texture[1], "textures/wall_w.xpm");
    // load_image(info, info->texture[2], "textures/wall_s.xpm");
    // load_image(info, info->texture[3], "textures/wall_n.xpm");

	//스프라이트
	//load_image(info, info->texture[4], "textures/health.xpm");
	load_image(info, info->texture[4], "textures/enemy.xpm");
}

void   ft_screen_check(t_info *info)
{
	int flag = 0;
	int max_x;
	int max_y;
	mlx_get_screen_size(info->mlx, &max_x, &max_y);
	if (max_x < info->window_x)
	{
		info->window_x = max_x;
		flag = 1;
	}
	if (max_y < info->window_y)
	{
		info->window_y = max_y;
		flag = 1;
	}
	if (flag == 1)
		mlx_new_window(info->mlx, info->window_x, info->window_y, "cub3D");
}

//---------------PLAYER------------------

int		main_loop(t_info *info)
{
	if (info->key_check[KEY_A] == 1)
	{
		pa -= 0.1;
		if (pa < 0)
			pa += 2 * PI;
		pdx = cos(pa) * 5;
		pdy = sin(pa) * 5;
	}
	if (info->key_check[KEY_D] == 1)
	{
		pa += 0.1;
		if (pa > 2 * PI)
			pa -= 2 * PI;
		pdx = cos(pa) * 5;
		pdy = sin(pa) * 5;
	}
	//pdx, pdy = x, y기울기
	int xo=0;	if (pdx<0) { xo=-20; } else { xo=20;}
	int yo=0;	if (pdy<0) { yo=-20; } else { yo=20;}

	//ipx와 ipy, add, sub 변수 생성.
	// int ipx=info->player_x/64.0, ipx_add_xo=(info->player_x+xo)/64.0, ipx_sub_xo=(info->player_x-xo)/64.0;
	// int ipy=info->player_y/64.0, ipy_add_yo=(info->player_y+yo)/64.0, ipy_sub_yo=(info->player_y-yo)/64.0;

	int ipx=info->player_x/mapSize, ipx_add_xo=(info->player_x+xo)/mapSize, ipx_sub_xo=(info->player_x-xo)/mapSize;
	int ipy=info->player_y/mapSize, ipy_add_yo=(info->player_y+yo)/mapSize, ipy_sub_yo=(info->player_y-yo)/mapSize;

	if (info->key_check[KEY_W] == 1)
	{
		if (map[ipy*mapX + ipx_add_xo] != 1) {info->player_x += pdx;}
		if (map[ipy_add_yo*mapX + ipx] != 1) {info->player_y += pdy;}
	}
	if (info->key_check[KEY_S] == 1)
	{
		if (map[ipy*mapX + ipx_sub_xo] != 1) {info->player_x -= pdx;}
		if (map[ipy_sub_yo*mapX + ipx] != 1) {info->player_y -= pdy;}
	}
	// printf("info->key_check[KEY_S]: %d\n", info->key_check[KEY_S]);

	// printf("info->key_check[KEY_ESC]: %d\n", info->key_check[KEY_ESC]);
	if (info->key_check[KEY_ESC] == 1)
	{
		printf("Exit!!!!!!!\n");
		exit(0);
	}

	//화면 크기가 윈도우 모니터 크기보다 높을시 발동.
	ft_screen_check(info);

	init_map_black(info);

	drawMap2D(info);
	draw_lines(info);
	drawPlayer(info);

	drawRays2D(info);

	//drawRays3D(info);


	mlx_put_image_to_window(info->mlx, info->win, info->img, 0, 0);
}

void	player_init(t_info *info)
{
	int x;
	int y;

	for (int i = 0; i < (mapX * mapY); i++)
	{
		if (map[i] == 3 || map[i] == 4 ||  map[i] == 5 ||  map[i] == 6)
		{
			//맵 기준 x, y 구하기.
			x = i % mapX;
			y = i / mapX;
			info->player_x = x * 64 + (mapSize / 2);
			info->player_y = y * 64 + (mapSize / 2);
			if (map[i] == 3) //동
				pa = 0;
			else if (map[i] == 4) //서
				pa = 3;
			else if (map[i] == 5) //남
				pa = 1.5;
			else if (map[i] == 6) //북
				pa = 4.5;
			break;
		}
	}
}

int	main(void)
{
	t_info info;

	info.mlx = mlx_init();

	// info.player_x = 300;
	// info.player_y = 300;

	info.pixel_size = 8;

	info.window_x = WIDTH;
	info.window_y = HEIGHT;
	// info.window_x = 1024;
	// info.window_y = 724;

	player_init(&info);

	//텍스쳐 초기화.
	if (!(info.texture = (int **)malloc(sizeof(int *) * 8)))
        return (-1);
    for (int i = 0; i < 8; i++)
        if (!(info.texture[i] = (int *)malloc(sizeof(int) * (texHeight * texWidth))))
			return (-1);
    for (int i = 0; i < 8; i++)
        for (int j = 0; j < texHeight * texWidth; j++)
            info.texture[i][j] = 0;

	info.key_check[KEY_ESC] = 0;
	//텍스쳐 초기화시 keycode가 멋대로 지정되는 오류가 있어서 넣음.

	load_texture(&info);

	info.win = mlx_new_window(info.mlx, info.window_x, info.window_y, "Hello world!");
    info.img = mlx_new_image(info.mlx, info.window_x, info.window_y);
    info.addr = mlx_get_data_addr(info.img, &info.bits_per_pixel, &info.size_l,
                                  &info.endian);


	mlx_loop_hook(info.mlx, &main_loop, &info);
	// mlx_hook(info.win, KeyPress, KeyPressMask, Button_down, &info);
	// mlx_hook(info.win, KeyRelease, KeyReleaseMask, Button_release, &info);

	mlx_hook(info.win, 2, (1L<<0), Button_down, &info);
	mlx_hook(info.win, 3, (1L<<1), Button_release, &info);

	mlx_loop(info.mlx);
}
