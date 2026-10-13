#include "cub3d.h"

void	put_pixel(t_img *img, int x, int y, int color)
{
	char	*pixel;

	if (x < 0 || x >= WIN_WIDTH || y < 0 || y >= WIN_HEIGHT)
		return ;
	pixel = img->data + (y * img->line_len) + (x * (img->bpp / 8));
	*(int *)pixel = color;
}

int	get_texture_pixel(t_img *tex, int x, int y)
{
	char	*pixel;

	if (x < 0 || x >= tex->width || y < 0 || y >= tex->height)
		return (0);
	pixel = tex->data + (y * tex->line_len) + (x * (tex->bpp / 8));
	return (*(int *)pixel);
}