NAME		= cub3D

CC			= cc
CFLAGS		= -Wall -Wextra -Werror
RM			= rm -f

SRC_DIR		= src
OBJ_DIR		= obj
INC_DIR		= includes
LIBFT_DIR	= libft
MLX_DIR		= minilibx-linux

LIBFT		= $(LIBFT_DIR)/libft.a
MLX			= $(MLX_DIR)/libmlx.a

INCLUDES	= -I$(INC_DIR) -I$(LIBFT_DIR) -I$(MLX_DIR)
LDFLAGS		= -L$(LIBFT_DIR) -lft -L$(MLX_DIR) -lmlx -lXext -lX11 -lm

SRC_INIT	= init/init_mlx.c \
			  init/free_game.c

SRC_PARSING	= parsing/read_file.c \
			  parsing/parse_scene.c \
			  parsing/parse_element.c \
			  parsing/parse_texture.c \
			  parsing/parse_color.c \
			  parsing/parse_map.c \
			  parsing/validate_map.c

SRC_RENDER	= render/render_frame.c \
			  render/cast_ray.c \
			  render/render_wall_slice.c \
			  render/draw_utils.c

SRC_INPUT	= input/keys.c \
			  input/close_window.c

SRC_UTILS	= utils/error.c \
			  utils/free.c

SRCS		= main.c $(SRC_INIT) $(SRC_PARSING) $(SRC_RENDER) \
			  $(SRC_INPUT) $(SRC_UTILS)

OBJS		= $(addprefix $(OBJ_DIR)/, $(SRCS:.c=.o))

all: $(NAME)

$(NAME): $(LIBFT) $(MLX) $(OBJS)
	$(CC) $(OBJS) $(LDFLAGS) -o $(NAME)

$(LIBFT):
	$(MAKE) -C $(LIBFT_DIR)

$(MLX):
	$(MAKE) -C $(MLX_DIR)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c $(INC_DIR)/cub3d.h
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

clean:
	$(RM) -r $(OBJ_DIR)
	$(MAKE) -C $(LIBFT_DIR) clean
	$(MAKE) -C $(MLX_DIR) clean

fclean: clean
	$(RM) $(NAME)
	$(MAKE) -C $(LIBFT_DIR) fclean

re: fclean all

bonus: all

.PHONY: all clean fclean re bonus
