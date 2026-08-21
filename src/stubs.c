#include "cub3d.h"

/* TODO: implementar (B) */
int	render_frame(t_game *game)
{
	    int	x;

    x = 0;
    while (x < WIN_WIDTH)
    {
        cast_ray(game, x);
        x++;
    }
    mlx_put_image_to_window(game->mlx, game->win, game->frame.ptr, 0, 0);
    return (OK);
}

/* TODO: implementar (B) */
int	handle_keypress(int key, t_game *game)
{
	(void)key;
	(void)game;
	return (0);
}

/* TODO: implementar (B) */
int	close_window(t_game *game)
{
	(void)game;
	exit(0);
	return (0);
}

/* TODO: implementar */
int	init_mlx(t_game *game)
{
	game->mlx = mlx_init();
	if (!game->mlx)
		return (error("mlx_init failed"));
	return (OK);
}

/* TODO: implementar */
int	init_frame(t_game *game)
{
	game->frame.ptr = mlx_new_image(game->mlx, WIN_WIDTH, WIN_HEIGHT);
	if(game->frame.ptr == NULL)
		return (error("mlx_new_image failed"));
	game->frame.data = mlx_get_data_addr(game->frame.ptr, 
			&game->frame.bpp, &game->frame.line_len, 
			&game->frame.endian);
	return (OK);
}

void	render_wall_slice(t_game *game, t_ray *ray, int x)
{
	    int	color;
    int	y;

    if (ray->side == 0)
        color = 0xFF0000;
    else
        color = 0x880000;
    y = ray->draw_start;
    while (y < ray->draw_end)
    {
        *(int *)(game->frame.data + (y * game->frame.line_len)
            + (x * (game->frame.bpp / 8))) = color;
        y++;
    }
}