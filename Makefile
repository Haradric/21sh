#******************************************************************************#
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mbraslav <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/04/10 16:59:45 by mbraslav          #+#    #+#              #
#    Updated: 2017/04/10 16:59:46 by mbraslav         ###   ########.fr        #
#                                                                              #
#******************************************************************************#

CC = gcc
FLAGS = -Wall -Wextra -Werror
SOURCE =	main.c\
			shell.c\
			environment.c\
			history.c\
			terminal.c\
			input.c\
			input_validate.c\
			cursor.c\
			cursor2.c\
			keys.c\
			keys_handle.c\
			keys_handle2.c\
			tokens.c\
			tokens2.c\
			get_program.c\
			get_program2.c\
			get_pipeline.c\
			run_command.c\
			run_process.c\
			heredoc.c\
			builtin_cd.c\
			builtin_echo.c\
			builtin_env.c\
			builtin_setenv.c\
			builtin_unsetenv.c\
			builtin_exit.c\
			signal.c\
			free.c\
			error.c\
			utils.c
OBJECT =	$(SOURCE:.c=.o)
NAME =		21sh
LIBFT =		./libft/libft.a

all: $(NAME)

$(NAME): $(OBJECT) $(LIBFT)
	$(CC) $(FLAGS) $(LIBFT) -ltermcap -o $@ $(OBJECT)

%.o: %.c
	$(CC) $(FLAGS) -o $@ -c $<

$(LIBFT):
	make -C libft

clean:
	make clean -C ./libft
	rm -f $(OBJECT)

fclean:
	make fclean -C ./libft
	rm -f $(OBJECT)
	rm -f $(NAME)

re: fclean all
