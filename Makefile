NAME = 	sphere

SRCS =	src/print/print.c \
		src/scene/canvas.c \
		src/scene/object_create.c \
		src/scene/scene.c \
		src/trace/hit/hit_sphere.c \
		src/trace/hit/hit.c \
		src/trace/hit/normal.c \
		src/trace/ray/phong_lighting.c \
		src/trace/ray/ray.c \
		src/trace/ray/reflect.c \
		src/utils/object/object_utils.c \
		src/utils/vec3/vec3_utils.c \
		src/utils/vec3/vec3_constructor.c \
		src/utils/vec3/vec3_divide.c \
		src/utils/vec3/vec3_minus.c \
		src/utils/vec3/vec3_mult.c \
		src/utils/vec3/vec3_plus.c \
		src/utils/vec3/vec3_length.c \
		src/main.c
OBJS = ${SRCS:.c=.o}

CC = cc
CFLAGS = -Wall -Wextra -Werror -g
LFLAGS = -L libft -L minilibx -framework OpenGL -framework AppKit
INC = -I include -I libft -I minilibx
RM = rm -f

all:	${NAME}

${NAME}: ${OBJS}
		${CC} ${CFLAGS} ${LFLAGS} -o ${NAME} ${OBJS}

%.o: %.c
		${CC} ${CFLAGS} ${INC} -c $< -o ${<:.c=.o}

clean:
		${RM} ${OBJS}

fclean:	clean
		${RM} ${NAME}

re:		fclean all
