################################
######     Variables     #######
################################

NAME:=philo

CC:=cc
CFLAGS= -Wall -Wextra -Werror -pthread
LDFLAGS= -pthread
ifdef FSANITIZE
	CFLAGS+= -g3 -fsanitize=address
	LDFLAGS+= -g3 -fsanitize=address
endif

SIMULATION_SRC:= \
	simulation/philosopher.c \
	simulation/simulation.c \
	simulation/simulation_settings.c \
	simulation/simulation_states.c
SRC:= \
	time.c \
	simulation_launcher.c \
	main.c
OBJS:=${addprefix src/,${SRC:.c=.o} ${SIMULATION_SRC:.c=.o}}
INCLUDE:= \
	include

#################################
######     Main rules     #######
#################################

all:
	@${MAKE} ${NAME} -j

${NAME}: ${OBJS}
	@${CC} ${OBJS} -o ${NAME} ${LDFLAGS} && echo "Compilation of ${NAME} successful"

%.o: %.c
	@${CC} ${CFLAGS} ${addprefix -iquote ,${INCLUDE}} -c $< -o $@

bonus: re

###############################
######     Cleaning     #######
###############################

clean: 
	@rm -f ${OBJS}

fclean: clean
	@rm -f ${NAME}

re: fclean all

.PHONY: clean fclean re bonus