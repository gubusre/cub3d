#include "cub3d.h"

static int	has_cub_extension(char *file)
{
	int	len;

	len = ft_strlen(file);
	if (len < 5)
		return (0);
	return (ft_strncmp(file + len - 4, ".cub", 4) == 0);
}

static int	is_config(char *line)
{
	if (ft_strncmp(line, "NO ", 3) == 0 || ft_strncmp(line, "SO ", 3) == 0
		|| ft_strncmp(line, "WE ", 3) == 0 || ft_strncmp(line, "EA ", 3) == 0
		|| ft_strncmp(line, "F ", 2) == 0 || ft_strncmp(line, "C ", 2) == 0)
		return (1);
	return (0);
}

static int	parse_config(char **lines, t_game *game)
{
	int	i;
	int	found;

	i = 0;
	found = 0;
	while (lines[i])
	{
		if (lines[i][0] == '\0')
			i++;
		else if (is_config(lines[i]))
		{
			if (parse_element(lines[i], game, &found) != OK)
				return (-1);
			i++;
		}
		else
			break ;
	}
	if (found != 0x3F)
		return (error("missing scene elements"), -1);
	return (i);
}

int	parse_scene(char *file, t_game *game)
{
	char	**lines;
	int		i;

	if (!has_cub_extension(file))
		return (error("scene file must have .cub extension"));
	lines = read_file(file);
	if (!lines)
		return (error("cannot read scene file"));
	i = parse_config(lines, game);
	if (i < 0)
		return (free_split(lines), ERROR);
	if (parse_map(lines + i, game) != OK)
		return (free_split(lines), ERROR);
	free_split(lines);
	return (validate_map(game));
}
