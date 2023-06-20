# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: kkaiyawo <kkaiyawo@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/05/16 09:22:56 by kkaiyawo          #+#    #+#              #
#    Updated: 2023/06/20 12:50:52 by kkaiyawo         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

### EXECUTABLE ###
NAME			=	philo

### DIR ###
SRC_DIR			=	./src/
BONUS_DIR		=	./bonus/
BUILD_DIR		=	./build/

### FILES ###
SRC_FILE		=	cycle_utils.c data_utils.c ft_atou.c philo.c philo_cycle.c \
					philo_error.c philo_utils.c ft_putstr_fd.c \
					ft_putendl_fd.c ft_strlen.c
BONUS_FILE		=

### PATH ###
SRC				=	${addprefix ${BUILD_DIR},${SRC_FILE}}
BONUS			=	${addprefix ${BUILD_DIR},${BONUS_FILE}}

### OBJECTS ###
SRC_OBJ			=	${SRC:.c=.o}
BONUS_OBJ		=	${BONUS:.c=.o}

### COMPILATION ###
CC				=	gcc
CFLAG			=	-g -pthread -Wall -Wextra -Werror -O3 -fsanitize=address
RM				=	rm -f

all:			${BUILD_DIR} ${NAME}

${NAME}:		${SRC_OBJ}
					${CC} ${CFLAG} ${SRC_OBJ} -o ${NAME}

bonus:			${BUILD_DIR} ${BONUS_OBJ}
					${CC} ${CFLAG} -o ${NAME} ${BONUS_OBJ}

${BUILD_DIR}:
					mkdir -p ${BUILD_DIR}

${BUILD_DIR}%.o:${SRC_DIR}%.c
						${CC} ${CFLAG} -c -o $@ $^

${BUILD_DIR}%.o:${BONUS_DIR}%.c
						${CC} ${CFLAG} -c -o $@ $^

clean:
					${RM} ${SRC_OBJ} ${BONUS_OBJ}

fclean:			clean
					${RM} ${NAME}

re:				fclean all

b:				bonus clean

m:				all clean

.PHONY:			all clean fclean re bonus
