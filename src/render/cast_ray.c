#include "cub3d.h"

//prepara la dirreccion del rayo para la columna x
static void init_ray(t_game *game, t_ray *ray, int x)
{
	ray->camara_x = 2 * x  / (double)WIN_WIDTH -1;
	ray->dir_x = game->player.dir_x + game->player.plane_x * ray->camara_x;
	ray->dir_y = game->player.dir_y + game->player.plane_y * ray->camara_x;
	ray->map_x = (int)game->player.pos_x;
	ray->map_y = (int)game->player.pos_y;
	ray->delta_x = fabs (1.0 / ray->dir_x);
	ray->delta_y = fabs (1.0 / ray->dir_y);
	
}
//decide en que direccion avanza el rayo
static void init_step(t_game *game, t_ray *ray)
{
	if (ray->dir_x < 0){
		ray->step_x = -1;
		ray->sidedist_x = (game->player.pos_x - ray->map_x) * ray->delta_x;
	}
	else
	{
		ray->step_x = 1;
		ray->sidedist_x = (ray->map_x + 1.0 - game->player.pos_x) * ray->delta_x;
	}
	if (ray->dir_y < 0){
		ray->step_y = -1;
		ray->sidedist_y = (game->player.pos_y - ray->map_y) * ray->delta_y;
	}
	else
	{
		ray->step_y = 1;
		ray->sidedist_y = (ray->map_y + 1.0 - game->player.pos_y) * ray->delta_y;
	}
	
}
static void dda(t_game *game, t_ray  *ray)
{
	while(game->map.map[ray->map_y][ray->map_x] != '1')
	{
		if (ray->sidedist_x < ray->sidedist_y)
		{
			ray->sidedist_x += ray->delta_x;
			ray->map_x += ray->step_x;
			ray->side = 0;
		}
		else
		{
			ray->sidedist_y += ray->delta_y;
			ray->map_y += ray->step_y;
			ray->side = 1;
		}
	}
	if (ray->side == 0)
		ray->walldist = ray->sidedist_x - ray->delta_x;
	else
		ray->walldist = ray->sidedist_y - ray->delta_y;

}
static void calc_wall(t_game *game, t_ray *ray)
{
	ray->line_height = (int)(WIN_HEIGHT / ray->walldist);
	ray->draw_start = -ray->line_height / 2 + WIN_HEIGHT / 2;
	if(ray->draw_start < 0)
		ray->draw_start = 0;
	ray->draw_end = ray->line_height / 2 + WIN_HEIGHT / 2;
	if (ray->draw_end >= WIN_HEIGHT)
		ray->draw_end = WIN_HEIGHT - 1;
	if (ray->side == 0)
		ray->wall_x = game->player.pos_y + ray->walldist * ray->dir_y;
	else
		ray->wall_x = game->player.pos_x + ray->walldist * ray->dir_x;
	ray->wall_x -= floor(ray->wall_x);
}
void	cast_ray(t_game *game, int x)
{
	t_ray	ray;

    ft_memset(&ray, 0, sizeof(t_ray));
    init_ray(game, &ray, x);
    init_step(game, &ray);
    dda(game, &ray);
    calc_wall(game, &ray);
    render_wall_slice(game, &ray, x);
}


