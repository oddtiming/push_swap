NAME	=	push_swap

NAME_BONUS	=	checker_bonus

# FOR TESTING PURPOSES
RUN_ARGS = 37 15 27 4 6 33 12 19 31 3 2 13 49 42 22 16 39 10 24 8 41 5 1 28 7 40 29 47 21 35 50 48 38 45 34 36 44 20 32 17 9 23 25 11 26 14 46 43 30 18

SHELL	=	bash

GREEN		=	\033[0;32m
BLUE		=	\033[0;34m
CYAN		=	\033[0;36m
RED			=	\033[0;31m
ON_RED		=	\033[41m
RESET_COL	=	\033[0m

CFILES	=	block_utils.c \
			calc_insert_cost.c \
			cleanup.c \
			delta_insert.c \
			deques.c \
			deque_modify.c \
			deque_operators.c \
			deque_utils.c \
			errors.c \
			ignore_lis.c \
			ignore_lis_utils.c \
			init.c \
			insert.c \
			insert_blocks.c \
			insert_blocks_utils.c \
			insert_utils.c \
			iterators.c \
			longest_increas_subseq.c \
			lis_utils.c \
			parse.c \
			partition_leaving_vals.c \
			partition_stack.c \
			print_utils.c \
			px.c \
			push_swap.c \
			rrx.c \
			rx.c \
			sort.c \
			sort_utils.c \
			sort_small.c \
			split_in_blocks.c \
			split_in_two.c \
			split_in_two_utils.c \
			sx.c \
			undo_moves.c

CFILES_BONUS	=	checker_bonus.c \
					checker_utils_bonus.c \
					deques.c \
					deque_modify.c \
					deque_operators.c \
					deque_utils.c \
					errors.c \
					ft_read_line.c \
					px_bonus.c \
					parse_bonus.c \
					rx_bonus.c \
					rrx_bonus.c \
					sx_bonus.c \
					undo_moves.c

HFILES	= 	push_swap.h \
			deques.h

SRC_DIR	= src
SRCS	= $(addprefix $(SRC_DIR)/, $(CFILES))

OBJ_DIR		= obj
OBJS		= $(addprefix $(OBJ_DIR)/, $(CFILES:.c=.o))
OBJS_BONUS	= $(addprefix $(OBJ_DIR)/, $(CFILES_BONUS:.c=.o))

INCL		= include
INCLFLAGS	= -I$(INCL)
HEADERS		= $(addprefix $(INCL)/, $(HFILES))

CC		= gcc
CFLAGS	= -Wall -Wextra -Werror -O3

LIBFT_DIR	= ./libft
LIBFT		= $(LIBFT_DIR)/libft.a
LIBFT_FLAGS	= -lft -Llibft

RM_OBJS			=	rm -rf $(OBJ_DIR)
RM_OBJS_OUT		=	$$($(RM_OBJS) 2>&1 | sed -e 's/error/\\\033[0;31merror\\\033[0m/g' -e 's/warning/\\\033[0;33mwarning\\\033[0m/g')
RM_EXE			=	rm -f $(NAME) $(NAME_BONUS)
RM_EXE_OUT		=	$$($(RM_EXE) 2>&1 | sed -e 's/error/\\\033[0;31merror\\\033[0m/g' -e 's/warning/\\\033[0;33mwarning\\\033[0m/g')
RM_LIBFT		=	make clean -sC ./libft
RM_LIBFT_OUT	=	$$($(RM_LIBFT) 2>&1 | sed -e 's/error/\\\033[0;31merror\\\033[0m/g' -e 's/warning/\\\033[0;33mwarning\\\033[0m/g')

COMPILE_EXE		=	$(CC) $(CFLAGS) $(LIBFT_FLAGS) $(INCLFLAGS) $(OBJS) -o $(NAME)
COMPILE_EXE_OUT	=	$$($(COMPILE_EXE) 2>&1 | sed -e 's/error/\\\033[0;31merror\\\033[0m/g' -e 's/warning/\\\033[0;33mwarning\\\033[0m/g')

COMPILE_C		=	$(CC) $(CFLAGS) $(INCLFLAGS) -o $@ -c $<
COMPILE_C_OUT	=	$$($(COMPILE_C) 2>&1 | sed -e 's/error/\\\033[0;31merror\\\033[0m/g' -e 's/warning/\\\033[0;33mwarning\\\033[0m/g')

COMPILE_EXE_BONUS		=	$(CC) $(CFLAGS) $(LIBFT_FLAGS) $(INCLFLAGS) $(OBJS_BONUS) -o $(NAME_BONUS)
COMPILE_EXE_BONUS_OUT	=	$$($(COMPILE_EXE_BONUS) 2>&1 | sed -e 's/error/\\\033[0;31merror\\\033[0m/g' -e 's/warning/\\\033[0;33mwarning\\\033[0m/g')

COMPILE_C_BONUS		=	$(CC) $(CFLAGS) $(INCLFLAGS) -o $@ -c $<
COMPILE_C_BONUS_OUT	=	$$($(COMPILE_C_BONUS) 2>&1 | sed -e 's/error/\\\033[0;31merror\\\033[0m/g' -e 's/warning/\\\033[0;33mwarning\\\033[0m/g')

$(OBJ_DIR)/%.o:	$(SRC_DIR)/%.c
	@mkdir -p $(OBJ_DIR)
	@printf "$(CYAN)%-32s-->%32s $(RESET_COL)$(COMPILE_C_OUT)\n" $^ $@

all: $(NAME)
	@if [ -e $(NAME) ]; \
		then \
		echo -e "$(GREEN)>>>>>>>> Compilation successful\n>>>>>>>>$(RESET_COL)"; \
	else \
		echo -e "$(RED)>>>>>>>> Compilation failed\n>>>>>>>>$(RESET_COL)"; \
	fi

bonus:	$(NAME_BONUS)
	@if [ -e $(NAME_BONUS) ]; \
		then \
		echo -e "$(GREEN)>>>>>>>> Compilation successful\n>>>>>>>>$(RESET_COL)"; \
	else \
		echo -e "$(RED)>>>>>>>> Compilation failed\n>>>>>>>>$(RESET_COL)"; \
	fi


$(NAME):	libft pretty_print $(OBJS)
	@echo -e "\n$(CYAN)>>>>>>>> Compiling $(NAME) ...$(RESET_COL)$(COMPILE_EXE_OUT)"

$(NAME_BONUS):	libft pretty_print_bonus $(OBJS_BONUS)
	@echo -e "\n$(CYAN)>>>>>>>> Compiling $(NAME_BONUS) ...$(RESET_COL)$(COMPILE_EXE_BONUS_OUT)"

silent_libft:
	@echo -e "---------------------- libft ----------------------\n"
	@echo -e "$(CYAN)>>>>>>>> Archiving libft.a ...$(RESET_COL)"
	@make -s bonus -C $(LIBFT_DIR)
	@if [ -e $(LIBFT) ]; \
		then \
		echo -e "$(GREEN)>>>>>>>> Archive successful\n>>>>>>>>$(RESET_COL)"; \
	else \
		echo -e "$(RED)>>>>>>>> Archive failed\n>>>>>>>>$(RESET_COL)"; \
	fi

libft: silent_libft

pretty_print: 
	@echo -e "\n--------------------- $(NAME) ---------------------"
											  
clean:
	@echo -e "$(RED)>>>>>>>> Deleting obj files$(RESET_COL)$(RM_OBJS_OUT)"
	@echo -e "$(GREEN)>>>>>>>> obj files deleted\n>>>>>>>>$(RESET_COL)"

clean_libft:
	@echo -e "$(RED)>>>>>>>> make fclean -sC libft $(RESET_COL)$(RM_LIBFT_OUT)"
	@echo -e "$(GREEN)>>>>>>>> libft cleaned\n>>>>>>>>$(RESET_COL)"

fclean:	clean clean_libft
	@echo -e "$(RED)>>>>>>>> Deleting $(NAME)$(RESET_COL)$(RM_EXE_OUT)"
	@echo -e "$(GREEN)>>>>>>>> ./$(NAME) deleted\n>>>>>>>>$(RESET_COL)"

re:	fclean all

pretty_print_bonus:
	@echo -e "$(GREEN)\n------------------- $(NAME_BONUS) -------------------$(RESET_COL)\n"

run: all
	./$(NAME) $(RUN_ARGS)

.PHONY: all clean clean_libft fclean re bonus libft silent_libft pretty_print pretty_print_bonus run
