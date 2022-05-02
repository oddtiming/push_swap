NAME	=	libft.a

CFILES	=	ft_atoi.c \
			ft_basic_math.c \
			ft_bzero.c \
			ft_isdigit.c \
			ft_memset.c \
			ft_putchar_fd.c \
			ft_putstr_fd.c \
			ft_split.c \
			ft_strcmp.c \
			ft_strdup.c \
			ft_strlen.c \
			ft_strlen_c.c \
			ft_strncpy.c \
			ft_substr.c \
			ft_strdup.c \
			ft_swap.c \
			ft_xalloc.c

SRC_DIR =	src

SRCS	=	$(addprefix $(SRC_DIR)/, $(CFILES))

OBJ_DIR =	obj

OBJS	=	$(addprefix $(OBJ_DIR)/,$(CFILES:.c=.o))

CC		=	gcc

CFLAGS	=	-Wall -Wextra -Werror -I.

AR		=	ar

ARFLAGS	=	-rcs

RM		=	rm -f

${NAME}:	${OBJS}
	${AR} ${ARFLAGS} $@ $^

${OBJ_DIR}/%.o: ${SRC_DIR}/%.c
	@mkdir -p obj
	${CC} ${CFLAGS} -o $@ -c $<

all:	${NAME}

clean:
	${RM} ${OBJS}
	${RM} -r ${OBJ_DIR}

fclean: clean
	${RM} ${NAME}

re:	fclean all

bonus:	all

.PHONY: all clean fclean re bonus
