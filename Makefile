NAME	=	push_swap

# FOR TESTING PURPOSES
RUN_ARGS = 37 15 27 4 6 33 12 19 31 3 2 13 49 42 22 16 39 10 24 8 41 5 1 28 7 40 29 47 21 35 50 48 38 45 34 36 44 20 32 17 9 23 25 11 26 14 46 43 30 18

SHELL	=	bash

GREEN		=	\033[0;32m
BLUE		=	\033[0;34m
CYAN		=	\033[0;36m
RED			=	\033[0;31m
ON_RED		=	\033[41m
RESET_COL	=	\033[0m

CFILES	=	cherrypick.c \
			cleanup.c \
			deques.c \
			deque_operators.c \
			divide_and_conquer.c \
			errors.c \
			init.c \
			insert.c \
			insert_blocks.c \
			insert_utils.c \
			iterators.c \
			parse.c \
			partition_leaving_vals.c \
			partition_stack.c \
			print_utils.c \
			px.c \
			push_swap.c \
			rrx.c \
			rx.c \
			sort.c \
			sort_big.c \
			sort_utils.c \
			sx.c \
			try_x.c \
			undo_moves.c \
			utils.c 

HFILES	= 	push_swap.h \
			deques.h

SRC_DIR	= src
SRCS	= $(addprefix $(SRC_DIR)/, $(CFILES))


OBJ_DIR	= obj
OBJS	= $(addprefix $(OBJ_DIR)/, $(CFILES:.c=.o))

INCL		= include
INCLFLAGS	= -I$(INCL)
HEADERS		= $(addprefix $(INCL)/, $(HFILES))

CC		= gcc
CFLAGS	= -Wall -Wextra -Werror -O3

#
# DEBUG build settings
#
DBG_DIR = debug_objs
DBG_EXE = push_swap_try_pb_debug
DBG_OBJS = $(addprefix $(DBG_DIR)/, $(CFILES:.c=.o))
DBG_CFLAGS = -D DEBUG=1 -g


LIBFT_DIR	= ./libft
LIBFT		= $(LIBFT_DIR)/libft.a
LIBFT_FLAGS	= -lft -Llibft

RM_OBJS			=	rm -rf $(OBJ_DIR)
RM_OBJS_OUT		=	$$($(RM_OBJS) 2>&1 | sed -e 's/error/\\\033[0;31merror\\\033[0m/g' -e 's/warning/\\\033[0;33mwarning\\\033[0m/g')
RM_EXE			=	rm -f $(NAME)
RM_EXE_OUT		=	$$($(RM_EXE) 2>&1 | sed -e 's/error/\\\033[0;31merror\\\033[0m/g' -e 's/warning/\\\033[0;33mwarning\\\033[0m/g')
RM_LIBFT		=	make clean -sC ./libft
RM_LIBFT_OUT	=	$$($(RM_LIBFT) 2>&1 | sed -e 's/error/\\\033[0;31merror\\\033[0m/g' -e 's/warning/\\\033[0;33mwarning\\\033[0m/g')

COMPILE_EXE		=	$(CC) $(CFLAGS) $(LIBFT_FLAGS) $(INCLFLAGS) $(OBJS) -o $(NAME)
COMPILE_EXE_OUT	=	$$($(COMPILE_EXE) 2>&1 | sed -e 's/error/\\\033[0;31merror\\\033[0m/g' -e 's/warning/\\\033[0;33mwarning\\\033[0m/g')

COMPILE_C		=	$(CC) $(CFLAGS) $(INCLFLAGS) -o $@ -c $<
COMPILE_C_OUT	=	$$($(COMPILE_C) 2>&1 | sed -e 's/error/\\\033[0;31merror\\\033[0m/g' -e 's/warning/\\\033[0;33mwarning\\\033[0m/g')

$(OBJ_DIR)/%.o:	$(SRC_DIR)/%.c
	@mkdir -p $(OBJ_DIR)
	@printf "$(CYAN)%-30s-->%30s $(RESET_COL)$(COMPILE_C_OUT)\n" $^ $@

#
# DEBUG MACROS
#
COMPILE_DBG_EXE		=	$(CC) $(DBG_CFLAGS) $(LIBFT_FLAGS) $(INCLFLAGS) $(DBG_OBJS) -o $(DBG_EXE)
COMPILE_DBG_EXE_OUT	=	$$($(COMPILE_DBG_EXE) 2>&1 | sed -e 's/error/\\\033[0;31merror\\\033[0m/g' -e 's/warning/\\\033[0;33mwarning\\\033[0m/g')
COMPILE_DBGC		=	$(CC) $(DBG_CFLAGS) $(INCLFLAGS) -o $@ -c $<
COMPILE_DBGC_OUT	=	$$($(COMPILE_DBGC) 2>&1 | sed -e 's/error/\\\033[0;31merror\\\033[0m/g' -e 's/warning/\\\033[0;33mwarning\\\033[0m/g')
RM_DBG_EXE			=	rm $(DBG_EXE)
RM_DBG_EXE_OUT		=	$$($(RM_DBG_EXE) 2>&1 | sed -e 's/error/\\\033[0;31merror\\\033[0m/g' -e 's/warning/\\\033[0;33mwarning\\\033[0m/g')

$(DBG_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(DBG_DIR)
	@echo -e "$(ON_RED)>\t$^\t--> $@ $(RESET_COL)$(COMPILE_DBGC_OUT)"

all: $(NAME)
	@if [ -e $(NAME) ]; \
		then \
		echo -e "$(GREEN)>>>>>>>> Compilation successful\n>>>>>>>>$(RESET_COL)"; \
	else \
		echo -e "$(RED)>>>>>>>> Compilation failed\n>>>>>>>>$(RESET_COL)"; \
	fi


$(NAME):	libft pretty_print $(OBJS)
	@echo -e "\n$(CYAN)>>>>>>>> Compiling $(NAME) ...$(RESET_COL)$(COMPILE_EXE_OUT)"

silent_libft:
	@echo -e "---------------------- libft.a ----------------------\n"
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

clean_debug: clean
	@echo -e "$(RED)>>>>>>>> Deleting debug obj files$(RESET_COL)$(RM_DBG_EXE_OUT)"
	@echo -e "$(GREEN)>>>>>>>> obj files deleted\n>>>>>>>>$(RESET_COL)"

fclean:	clean clean_libft clean_debug
	@echo -e "$(RED)>>>>>>>> Deleting $(NAME)$(RESET_COL)$(RM_EXE_OUT)"
	@echo -e "$(GREEN)>>>>>>>> ./$(NAME) deleted\n>>>>>>>>$(RESET_COL)"

re:	fclean all

test5: all
	gcc -g push_swap_tester.c libft/libft.a && ./a.out 5;

bonus:	all

run: all
	./$(NAME) $(RUN_ARGS)

#
# Debug rules
#
pretty_print_debug:
	@echo -e "$(RED)\n------------------- $(DBG_EXE) -------------------$(RESET_COL)\n"

debug: all pretty_print_debug $(DBG_OBJS)
	@echo -e "\n$(ON_RED)>>>>>>>> Compiling $(DBG_EXE) ...$(RESET_COL)$(COMPILE_DBG_EXE_OUT)"
	./$(DBG_EXE) $(RUN_ARGS)

.PHONY: all clean clean_libft fclean re bonus libft silent_libft pretty_print pretty_print_debug run debug test5
