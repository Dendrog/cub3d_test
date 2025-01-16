# include "./mlx/mlx.h"
# include "./mlx/mlx_int.h"
# include "./libft/libft.h"
# include <math.h>
# include <stdio.h>

#define y_center 340

typedef struct	s_data {
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}				t_data;

void	my_mlx_pixel_line(t_data *data, int x, int color, int cm)
{
	char	*dst;
	int		i;

	i = y_center - cm / 2;
	while (i <= y_center + cm / 2)
	{
		dst = data->addr + (i * data->line_length + x * (data->bits_per_pixel / 8));
		*(unsigned int*)dst = color;
		i++;
	}
}

int	main(void)
{
	char map[10][10] = {{1,1,1,1,1,1,1,1,1,1},
						{1,0,0,0,0,0,0,0,0,1},
						{1,0,1,0,0,0,1,0,0,1},
						{1,0,0,0,0,0,0,1,0,1},
						{1,0,0,'s',0,0,0,0,1,1},
						{1,0,0,0,0,0,0,0,0,1},
						{1,0,0,0,0,0,0,0,0,1},
						{1,0,1,0,0,0,0,1,0,1},
						{1,0,0,0,0,0,0,0,0,1},
						{1,1,1,1,1,1,1,1,1,1}}; // 50*50 (0,0 ~ 50,0 ~ 0,50 ~ 50,50)
	void	*mlx;
	void	*mlx_win;
	t_data	img;
	int i;

	i = 100;
	mlx = mlx_init();
	mlx_win = mlx_new_window(mlx, 1000, 500, "cub3d");
	img.img = mlx_new_image(mlx, 1080, 680);
	img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.line_length,
								&img.endian);
	//map[4][3] = s
	
	double playerPosX = 3.5;
	double playerPosY = 4.5;
	double mapPosX = 3;
	double mapPosY = 4;
	double raydirX = 1;
	double raydirY;
	double planeX = 0, planeY = 0.66;
	const double PI = 3.1415926;
	double deltaDistX;
	double deltaDistY;
	double sideDistY, sideDistX;
	double siteX, siteY;
	int count = 0;
	double set = 180;

	while(1)
	{
		if (set<=90)
			break;
		raydirY = tan(set * PI / 180);

		deltaDistY = sqrt(pow(raydirX / raydirY, 2) + 1);
		if (raydirY >= 0)
			sideDistY = (mapPosY + 1 - playerPosY) * deltaDistY;
		else
			sideDistY = (playerPosY - mapPosY) * deltaDistY;
		
		deltaDistX = sqrt(pow(raydirY / raydirX, 2) + 1);
		if (raydirX >= 0)
			sideDistX = (mapPosX + 1 - playerPosX) * deltaDistX;
		else
			sideDistX = (playerPosX - mapPosX) * deltaDistX;
		siteX = playerPosX + sideDistX;
		siteY = playerPosY + sideDistY;
		//printf("%d",(int)sqrt(pow(siteX+deltaDistX,2) + pow(siteY+deltaDistY,2)));
		while(1)
		{
			if ((int)siteY > 9 || (int)siteX > 9 || (int)siteY < 0 || (int)siteX < 0)
				break;
			if (map[(int)siteY][(int)siteX])
			{
				my_mlx_pixel_line(&img, count++, 0x00FF0000,(int)sqrt(pow(siteX,2) + pow(siteY,2)));
				break;
			}
			siteX+=deltaDistX;
			siteY+=deltaDistY;
		}
		set-=0.1;
	}

	//printf("x = %lf y = %lf alp = %lf, dY = %lf",raydirX, raydirY, alp, deltaDistY);
	/*while (i < 200){
		my_mlx_pixel_line(&img, i, 0x00FF0000,100);
		i++;
	}
	my_mlx_pixel_line(&img, 100, 0x00FF0000,100);
	my_mlx_pixel_line(&img, 101, 0x00FF0000,110);
	my_mlx_pixel_line(&img, 102, 0x00FF0000,120);
	my_mlx_pixel_line(&img, 103, 0x00FF0000,130);
	my_mlx_pixel_line(&img, 104, 0x00FF0000,140);
	my_mlx_pixel_line(&img, 105, 0x00FF0000,130);
	my_mlx_pixel_line(&img, 106, 0x00FF0000,120);
	my_mlx_pixel_line(&img, 107, 0x00FF0000,110);
	my_mlx_pixel_line(&img, 108, 0x00FF0000,100);*/
	mlx_put_image_to_window(mlx, mlx_win, img.img, 0, 0);
	mlx_loop(mlx);
}