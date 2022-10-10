# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: nvideira <nvideira@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/08/28 21:10:24 by nvideira          #+#    #+#              #
#    Updated: 2022/10/10 10:12:27 by nvideira         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS=	main.c\
		ft_atoi.c\
		philo.c\
		utils.c\
		ft_strdup.c\
		ft_strlen.c\
		print.c\
		do_stuff.c

OBJS=	${SRCS:.c=.o}

NAME=	philo

CC=		gcc

FLAGS=	-Wall -Werror -Wextra -pthread -g -fsanitize=thread

.c.o:
		${CC} ${FLAGS} -c $< -o ${<:.c=.o}

${NAME}:	${OBJS}
		${CC} ${FLAGS} ${OBJS} -o ${NAME}

all:		${NAME}

clean:
		rm -f ${OBJS}

fclean:		clean
		rm -f ${NAME}

re:			fclean all

.PHONY:		all clean fclean re 
