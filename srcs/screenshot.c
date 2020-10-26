#include "../include/cub3d.h"

static void     fill_theader_bmp(t_mlx *mlx, t_bmp_header *theader)
{
	theader->type = 0x4d42;
	theader->offset = 0x36;
	theader->dib_header_size = 0x28;
	theader->width_px = mlx->win_width;
	theader->height_px = mlx->win_height;
	theader->num_planes = 0x01;
	theader->bits_per_pixel = 0x20;
}

static void     write_header_bmp(char *header, t_bmp_header *theader)
{
	ft_bzero(header, 54);
	ft_memmove(header, &(theader->type), 2);
	ft_memmove(header+2, &(theader->size), 4);
	ft_memmove(header+6, &(theader->reserved1), 2);
	ft_memmove(header+8, &(theader->reserved2), 2);
	ft_memmove(header+10, &(theader->offset), 4);
	ft_memmove(header+14, &(theader->dib_header_size), 4);
	ft_memmove(header+18, &(theader->width_px), 4);
	ft_memmove(header+22, &(theader->height_px), 4);
	ft_memmove(header+26, &(theader->num_planes), 2);
	ft_memmove(header+28, &(theader->bits_per_pixel), 2);
	ft_memmove(header+30, &(theader->compression), 4);
	ft_memmove(header+34, &(theader->image_size_bytes), 4);
	ft_memmove(header+38, &(theader->x_resolution_ppm), 4);
	ft_memmove(header+42, &(theader->y_resolution_ppm), 4);
	ft_memmove(header+46, &(theader->num_colors), 4);
	ft_memmove(header+50, &(theader->important_colors), 4);
	header[53] = 0;
}

static int      write_bmp_file(t_mlx *mlx, int size)
{
	int             fd;
	int             data[size];
    char            header[53];
    t_bmp_header    theader;

    ft_bzero(&theader, sizeof(t_bmp_header));
    fill_theader_bmp(mlx, &theader);
    write_header_bmp(header, &theader);
	ft_bzero(data, size);
	fd = open("screenshot.bmp", O_WRONLY | O_APPEND | O_TRUNC | O_CREAT, 0666);
	write(fd, &header, sizeof(t_bmp_header));
	while (size)
	{
		write(fd, &mlx->img.data[size - 1], mlx->win_width * 4);
		size-= mlx->win_width;
	}
	close(fd);
    return (0);
}

int             screenshot(t_mlx *mlx, char *argv)
{
	int			size;

	if (ft_init(mlx) < 0)
		return (exit_game_err(mlx));
	if (parsing_map(mlx, argv) < 0)
		return (exit_game_err(mlx));
	mlx->save = 1;
	size = mlx->win_height * mlx->win_width;
	mlx->img.img_ptr = mlx_new_image(mlx->mlx_ptr, mlx->win_width, mlx->win_height);
	mlx->img.data = (int *)mlx_get_data_addr(mlx->img.img_ptr, &mlx->img.bpp, &mlx->img.size_l,
	&mlx->img.endian);
	ft_raycasting(mlx, &mlx->vec, &mlx->player);
	write_bmp_file(mlx,size);
	return (0);
}
