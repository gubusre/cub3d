#ifndef CUB3D_H
# define CUB3D_H

# include <stdio.h>
# include <stdlib.h>
# include <math.h>
# include <mlx.h>
# include <unistd.h>
# include <fcntl.h>
# include "../libft/libft.h" 

# define OK 0
# define ERROR 1

# define WIN_WIDTH 800
# define WIN_HEIGHT 600

# define NO 0
# define SO 1
# define WE 2
# define EA 3

# define FLOOR 4
# define CEILING 5

typedef struct s_player
{
	double	pos_x;
	double	pos_y;
	double	dir_x;
	double	dir_y;
	double	plane_x;
	double	plane_y;
}	t_player;

typedef struct s_img
{
	void	*ptr;
	char	*data;
	int		bpp;
	int		line_len;
	int		endian;
	int		width;
	int		height;
}	t_img;

typedef struct s_map
{
	char	**map;
	int		width;
	int		height;
	int		floor;
	int		ceiling;
}	t_map;

typedef struct s_game
{
	void		*mlx;
	void		*win;
	t_player	player;
	t_map		map;
	t_img		frame;
	t_img		texture[4];
}	t_game;

typedef struct s_ray
{
	double	camara_x;
	double	dir_x;
	double	dir_y;
	int		map_x;
	int		map_y;
	int		step_x;
	int		step_y;
	double	sidedist_x;
	double	sidedist_y;
	double	delta_x;
	double	delta_y;
	double	walldist;
	int		side;
	double	wall_x;
	int		draw_start;
	int		draw_end;
	int		line_height;
}	t_ray;

/* parsing */
int		parse_scene(char *file, t_game *game);
int		parse_element(char *line, t_game *game, int *found);
int		parse_texture(char *line, t_game *game, int id, int *found);
int		parse_color(char *line, t_game *game, int id, int *found);
int		parse_map(char **lines, t_game *game);
int		validate_map(t_game *game);

/* utils */
int		error(char *msg);
void	free_split(char **split);
void	free_game(t_game *game);

/* init */
int		init_mlx(t_game *game);
int		init_frame(t_game *game);

/* render */
int		render_frame(t_game *game);
void	cast_ray(t_game *game, int x);
void	render_wall_slice(t_game *game, t_ray *ray, int x);


/* input */
int		handle_keypress(int key, t_game *game);
int		close_window(t_game *game);
#endif