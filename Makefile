NAME	= fdf
SRC		= fdf.c\
		  draw.c\
		  draw_utils.c\
		  file_handling.c\
		  get_next_line.c\
		  get_next_line_utils.c\
		  matrices.c\
		  renderer.c\
		  utils.c

OBJS	= $(SRC:.c=.o)
CC		= gcc
RM		= rm -f
CFLAGS	= -Wall -Werror -Wextra
LIB		= -Lminilibx-linux -lmlx_Linux
INCLUDE	= -Iminilibx-linux
MLXFLAG	= -lXext -lX11 -lm
.c.o:
	$(CC) ${CFLAGS} -g -c $< -o ${<:.c=.o} ${LIB} ${INCLUDE} ${MLXFLAG}
$(NAME): $(OBJS)
	cd minilibx-linux;\
	./configure
	${RM} Makefile.gen
	${CC} ${CFLAGS} ${OBJS} -o ${NAME} ${LIB} ${INCLUDE} ${MLXFLAG}
all: ${NAME}
clean:
	${RM} ${OBJS}
fclean: clean
	${RM} ${NAME}
	cd minilibx-linux;\
	./configure clean
re: fclean all