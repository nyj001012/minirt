NAME =	minirt

SRCS =	src/mlx/mlx_utils.c \
		src/print/print.c \
		src/scene/canvas.c \
		src/scene/object_create.c \
		src/scene/render_scene.c \
		src/scene/scene.c \
		src/trace/hit/hit_sphere.c \
		src/trace/hit/hit_plane.c \
		src/trace/hit/hit_cylinder.c \
		src/trace/hit/hit.c \
		src/trace/hit/normal.c \
		src/trace/ray/phong_lighting.c \
		src/trace/ray/ray.c \
		src/trace/ray/reflect.c \
		src/utils/color/color3_utils.c \
		src/utils/object/object_utils.c \
		src/utils/vec3/vec3_utils.c \
		src/utils/vec3/vec3_constructor.c \
		src/utils/vec3/vec3_divide.c \
		src/utils/vec3/vec3_minus.c \
		src/utils/vec3/vec3_mult.c \
		src/utils/vec3/vec3_plus.c \
		src/utils/vec3/vec3_length.c \
		src/parsing/process_file.c \
		src/parsing/split_line.c \
		src/parsing/double_conversion.c \
		src/parsing/parsing_utils.c \
		src/parsing/get_xyz.c \
		src/parsing/put_acl.c \
		src/parsing/put_object.c \
		src/main.c
OBJS = ${SRCS:.c=.o}

MLX_DIR = minilibx
MLX_LIB = libmlx.dylib

LIBFT_DIR = libft

CC = cc
CFLAGS = -Wall -Wextra -Werror -g
LFLAGS = -L$(LIBFT_DIR) -lft -L$(MLX_DIR) -lmlx -framework OpenGL -framework AppKit
INC = -I include -I ${LIBFT_DIR} -I ${MLX_DIR}
RM = rm -f

all:	${NAME}

${NAME}: ${OBJS}
		@make bonus -C libft
		@make -C minilibx
		@cp $(MLX_DIR)/$(MLX_LIB) .
		@${CC} ${CFLAGS} ${LFLAGS} -o ${NAME} ${OBJS}

%.o: %.c
		@${CC} ${CFLAGS} ${INC} -c $< -o ${<:.c=.o}

clean:
		${RM} ${OBJS}
		@make clean -C libft
		@make clean -C minilibx

fclean:	clean
		${RM} ${NAME}
		@make fclean -C libft
		@make clean -C minilibx
		${RM} ${MLX_LIB}

re:		fclean all
