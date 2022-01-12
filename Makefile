# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lbrandy <lbrandy@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/01/27 18:57:26 by jradioac          #+#    #+#              #
#    Updated: 2021/10/02 16:23:02 by lbrandy          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

MAIN_H = minishell.h

OBJ_DIR = obj
SRCS_DIR = srcs
HEADERS_DIR = includes
LIBFT_PATH		= ./srcs/libft

FILES =   	main.c \
			utills.c \
			signal_utils.c \
			signal_handler.c \
			redirs.c \
			list_separator.c \
			dup_handler.c \
			cmd_handler.c \
			cmd_handler_utills.c \
			envp_utills.c \
			ch_utills.c \
			check_redir.c \
			create_grandlist.c \
			do_token_list.c \
			dollar.c \
			pars_quotes.c \
			parser_main.c \
			preparser.c \
			token_list_actions.c \
			double_back_redir.c \
			my_env_func.c \
			my_export_func.c \
			my_cd_func.c \
			my_echo_func.c \
			my_exit_func.c \
			envp_list_creation.c \
			my_pwd_func.c \
			my_unset_func.c\
			parser_utils.c\
			my_cd_utils.c\
			my_export_utils.c\
			parser_utils2.c
	
GCC = gcc
FLAGS = -Wall -Wextra -Werror -g
NAME = minishell
RM   =  rm -rf

HEADERS = $(addprefix $(HEADERS_DIR)/, $(MAIN_H))
SRCS = $(addprefix $(SRCS_DIR)/, $(FILES))
OBJ = $(addprefix $(OBJ_DIR)/, $(FILES:.c=.o))
LIB = -L. -lft -lreadline -L ~/.brew/opt/readline/lib/
INC = -I ~/.brew/opt/readline/include


all: make_lib $(NAME)

make_lib:
	@${MAKE} -C ./srcs/libft
	
$(NAME): $(OBJ)
		@mv ./srcs/libft/libft.a .
		$(GCC) $(FLAGS) $(LIB) $(OBJ) libft.a -o $(NAME)


$(OBJ_DIR)/%.o: $(SRCS_DIR)/%.c $(HEADERS_DIR)/$(MAIN_H)
	@mkdir -p $(OBJ_DIR)
	$(GCC) $(FLAGS) -c $< -o $@ $(INC)
clean: 
	$(RM) $(OBJ)
	$(RM) $(OBJ_DIR)
	@cd $(LIBFT_PATH) && make clean

fclean: clean
	$(RM) $(NAME)
	@cd $(LIBFT_PATH) && make fclean
	@rm -f ./libft.a

re: fclean all

debug:
	gcc -g ${SRCS} ./srcs/libft/*.c -lreadline -o minishell
	
.PHONY: all clean fclean re