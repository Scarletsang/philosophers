################################
######     Variables     #######
################################

NAME:=philo

CC:=cc
CFLAGS= -Wall -Wextra -Werror -pthread
LDFLAGS= -lpthread
ifdef FSANITIZE
	CFLAGS+= -g3 -fsanitize=address
	LDFLAGS+= -g3 -fsanitize=address
endif
ifdef FSTHREAD
	CFLAGS+= -g3 -fsanitize=thread
	LDFLAGS+= -g3 -fsanitize=thread
endif

SIMULATION_SRC:= \
	simulation/simulation.c \
	simulation/settings.c \
	simulation/signal.c \
	simulation/states.c
REAPER_SRC:= \
	reaper/reaper.c
PHILOSOPHER_SRC:= \
	philosopher/philosopher.c \
	philosopher/action.c \
	philosopher/printer.c
SIMULATION_LAUNCHER_SRC:= \
	simulation_launcher/simulation_launcher.c \
	simulation_launcher/simulation_spawner.c \
	simulation_launcher/simulation_loner.c
SRC:= \
	time.c \
	main.c
OBJS_DIR:=obj
SRCS_DIR:=src
OBJS:=$(addprefix $(OBJS_DIR)/,$(subst /,\#,$(SIMULATION_SRC:.c=.o) $(REAPER_SRC:.c=.o) $(PHILOSOPHER_SRC:.c=.o) $(SIMULATION_LAUNCHER_SRC:.c=.o) $(SRC:.c=.o)))
INCLUDE:= \
	include

#################################
######     Main rules     #######
#################################

all:
	@$(MAKE) $(NAME) -j

$(NAME): $(OBJS_DIR) $(OBJS)
	@$(CC) $(OBJS) -o $(NAME) $(LDFLAGS) && echo "Compilation of $(NAME) successful"

.SECONDEXPANSION:
$(OBJS_DIR)/%.o: $(SRCS_DIR)/$$(subst \#,/,$$*).c
	@$(CC) $(CFLAGS) $(addprefix -iquote ,$(INCLUDE)) -c $< -o $@

$(OBJS_DIR):
	@mkdir -p $(OBJS_DIR)

bonus: re

###############################
######     Cleaning     #######
###############################

clean: 
	@rm -f $(OBJS)

fclean: clean
	@rm -rf $(OBJS_DIR)
	@rm -f $(NAME)

re: fclean all

.PHONY: clean fclean re bonus
