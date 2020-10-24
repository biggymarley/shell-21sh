# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: afaragi <afaragi@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/01/27 02:25:57 by afaragi           #+#    #+#              #
#    Updated: 2020/10/24 00:51:42 by afaragi          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = 21SH
LIBFT_PATH = libft/
INC = -I ./include/ -I $(LIBFT_PATH)
SRC_DIR = srcs/
OBJ_DIR = obj/
FLAGS = -Wall -Wextra -Werror

SRC_NAME =	main.c \
			environ_to_list.c \
			free_cmd_list.c \
			errors.c \
			pipe_tools.c \
			sep_pipe_parser.c \
			red_parser.c \
			printer.c \
			free_env.c \
			execute_cmd.c \
			found_cmd.c \
			ltot.c \
			execute_red.c \
			herdoc_reader.c \


SRCS = $(addprefix $(SRC_DIR), $(SRC_NAME))
OBJS = $(addprefix $(OBJ_DIR), $(SRC_NAME:.c=.o))

all : $(NAME)

$(NAME) : $(OBJS)
			@make -s -C $(LIBFT_PATH)
			@gcc $(FLAGS) $(OBJS) $(INC) -L $(LIBFT_PATH) -lft -o $(NAME)
$(OBJ_DIR)%.o: $(SRC_DIR)%.c
			@mkdir -p obj
			@gcc -c $(INC) $^ -o $@
clean:
		@make clean -C $(LIBFT_PATH)
		@rm -rf $(OBJ_DIR)
fclean:
		@make clean -C $(LIBFT_PATH)
		@rm -f $(NAME)
		@rm -rf obj/
re: fclean all
			