NAME =	miniRT

RAW_SRCS =	src/mlx/mlx_utils \
			src/print/print \
			src/scene/canvas \
			src/scene/object_create \
			src/scene/render_scene \
			src/scene/scene \
			src/trace/hit/hit_sphere \
			src/trace/hit/hit_plane \
			src/trace/hit/hit_cylinder \
			src/trace/hit/hit_cy_base \
			src/trace/hit/hit \
			src/trace/hit/normal \
			src/trace/ray/phong_lighting \
			src/trace/ray/ray \
			src/trace/ray/reflect \
			src/utils/color/color3_utils \
			src/utils/object/object_utils \
			src/utils/vec3/vec3_utils \
			src/utils/vec3/vec3_constructor \
			src/utils/vec3/vec3_divide \
			src/utils/vec3/vec3_minus \
			src/utils/vec3/vec3_mult \
			src/utils/vec3/vec3_plus \
			src/utils/vec3/vec3_length \
			src/parsing/process_file \
			src/parsing/split_line \
			src/parsing/double_conversion \
			src/parsing/parsing_utils \
			src/parsing/get_xyz \
			src/parsing/put_acl \
			src/parsing/put_object \
			src/main

MAN_SRCS = $(addsuffix .c, ${RAW_SRCS})
MAN_OBJS = ${MAN_SRCS:.c=.o}

BONUS_DIR = bonus
BONUS_SRCS = $(addprefix ${BONUS_DIR}/, $(addsuffix _bonus.c, ${RAW_SRCS}))
BONUS_SRCS += ${BONUS_DIR}/src/scene/object_create_bonus2.c \
			  ${BONUS_DIR}/src/trace/hit/hit_cone_bonus.c
BONUS_OBJS = ${BONUS_SRCS:.c=.o}

MLX_DIR = minilibx
MLX_LIB = libmlx.dylib

LIBFT_DIR = libft

CC = cc
CFLAGS = -Wall -Wextra -Werror -g
LFLAGS = -L$(LIBFT_DIR) -lft -L$(MLX_DIR) -lmlx -framework OpenGL -framework AppKit
INC = -I ${LIBFT_DIR} -I ${MLX_DIR}

RM = rm -f

ifdef bonus
    INC += -I ${BONUS_DIR}/include
	SRCS = ${BONUS_SRCS}
	OBJS = ${BONUS_OBJS}
else
	SRCS = ${MAN_SRCS}
	OBJS = ${MAN_OBJS}
	INC += -I include
endif

all: ${NAME}

bonus:
	@make bonus=1 all

$(NAME): ${OBJS}
		@make bonus -C libft
		@make -C minilibx
		@cp $(MLX_DIR)/$(MLX_LIB) .
		@${CC} ${CFLAGS} ${INC} ${LFLAGS} -o ${NAME} ${OBJS}

%.o: %.c
		@${CC} ${CFLAGS} ${INC} -c $< -o ${<:.c=.o}

clean:
		${RM} ${OBJS} ${BONUS_OBJS}
		@make clean -C libft
		@make clean -C minilibx

fclean:	clean
		${RM} ${NAME}
		@make fclean -C libft
		@make clean -C minilibx
		${RM} ${MLX_LIB}

re:		fclean all

.PHONY: all clean fclean re bonus
