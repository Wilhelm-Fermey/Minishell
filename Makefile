# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: wfermey <marvin@42.fr>                     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/05/11 09:16:34 by wfermey           #+#    #+#              #
#    Updated: 2022/05/31 13:42:01 by wilhelmfermey    ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME =	minishell

FLAGS = -Wall -Wextra -Werror

FILES =	main.c fill.c utils.c check_quote.c check_variable.c one_seg.c \
	ft_split_quotes.c utils2.c ft_cd.c substitute_var.c \
	ft_pipex.c ft_array.c execve.c ft_echo.c ft_pwd.c ft_export.c \
	ft_unset.c ft_env.c ft_exit.c free_data.c child.c merge_files.c \
	signal.c utils3.c

${NAME}:	
		gcc -o ${NAME} $(FILES) $(FLAGS) LIB42/libft.a -lreadline -I \
		.brew/opt/readline/include
			
all:	${NAME}

clean:		
		rm ${NAME}

fclean:		
		rm ${NAME}

re:		fclean all
