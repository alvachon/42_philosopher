
# --- PROJECT -
NAME			= philo
UNAME_S		 	= 	$(shell uname -s)
REL_PATH		=	$(shell pwd)
# --- FILE ----
INCL_DIR		= ./include
SRCS_DIR		= ./srcs
OBJS_DIR		= ./objs
SRCS			= $(SRCS_DIR)/action.c \
				  $(SRCS_DIR)/die_conditions.c \
				  $(SRCS_DIR)/init.c \
				  $(SRCS_DIR)/main.c \
				  $(SRCS_DIR)/mutexes_exit.c \
				  $(SRCS_DIR)/threads.c \
				  $(SRCS_DIR)/time.c
OBJS 			= $(SRCS:$(SRCS_DIR)/%.c=$(OBJS_DIR)/%.o)
HDRS_FILE		= philo.h
HDRS			= $(INCL_DIR)/$(HDRS_FILE)
$(OBJS_DIR)/%.o: $(SRCS_DIR)/%.c $(HDRS)
	@$(CC) $(CFLAGS) -c $< -o $@
#
# --- FLAGS ---
AR				= ar
ARFLAGS			= rcs
CC				= gcc
CFLAGS			= -Wall -Wextra -Werror
TFLAGS			= -pthread
SFLAGS			= -fsanitize=thread

# --- COLOR ---
YELLOW			= '\033[0;33m'
GREEN			= '\033[0;32m'
GRAY			= '\033[2;37m'
RESET_COLOR		= '\033[0m'
# --- COMMAND -
REMOVE			= rm -rf
#
#
#
all: init $(NAME)

$(NAME): $(OBJS)
	@echo $(YELLOW) "\nIncoming :\n" $(RESET_COLOR)
	$(CC) $(CFLAGS) $(TFLAGS) $(SFLAGS) $(OBJS) -o $(NAME)
	@echo $(GREEN) "\nCompilation of philosopher done.\n" $(RESET_COLOR)

init:
	@mkdir -p $(OBJS_DIR)

clean:
	@echo $(YELLOW) "\nRemoving object:\n" $(RESET_COLOR)
	$(REMOVE) $(OBJS) $(OBJS_DIR)
	@echo $(RESET_COLOR)$(GREEN) "OK - - - - - - - - - - \n" $(RESET_COLOR)

fclean: clean
	@echo $(YELLOW) "\nRemoving .a:\n" $(RESET_COLOR)
	$(REMOVE) $(NAME)
	$(REMOVE) philo.dSYM
	@echo $(RESET_COLOR)$(GREEN) "OK - - - - - - - - - - \n" $(RESET_COLOR)

re: fclean all

#Need to remove SFLAGS
#valgrind:
#	valgrind ./philo 2 2000 200 200 2
#	leaks --atExit -- ./philo 2 200 200 2
#Example for eval
#eval:
#	./philo 5 800 200 200 7 | grep "5\tis eating" | wc -l

.PHONY:	all clean fclean re init
