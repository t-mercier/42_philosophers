# **************************************************************************** #
#                                                                              #
#                                                         ::::::::             #
#    Makefile                                           :+:    :+:             #
#                                                      +:+                     #
#    By: tmercier <tmercier@student.codam.nl>         +#+                      #
#                                                    +#+                       #
#    Created: 2021/12/02 17:13:26 by tmercier      #+#    #+#                  #
#    Updated: 2023/04/18 11:11:37 by tmercier      ########   odam.nl          #
#                                                                              #
# **************************************************************************** #

# ifdef FSANT
# 	CFLAGS 	+= -g -fsanitize=thread
# endif
# ifdef FSANA
# 	CFLAGS 	+= -g -fsanitize=address
# endif
CFLAGS 	+= 	-I. -Werror -Wall -Wextra
SRCS 	= 	main.c threads.c mutex.c check.c logs.c actions.c time.c utils.c
OBJS 	=	$(addprefix out/, $(SRCS:.c=.o))
BIN 	= 	philo
CC 		= 	cc

$(shell mkdir -p out)

all: $(BIN)

$(BIN): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^

out/%.o: %.c philo.h _philo.h
	@if ! [ -d out ]; then mkdir out; fi
	@printf "$(CYAN)Compiling: $(RESET)$(notdir $<)\n"
	@$(CC) $(CFLAGS) -c -o $@ $<

clean:
	@if [ -d out ]; then rm -rf out; fi
	@printf "$(CYAN)\n-> obj cleaned\n$(RESET)"

fclean: clean
	@printf "$(CYAN)\n-> bin file cleaned\n$(RESET)"
	@rm -rf $(BIN)

re: fclean all

.PHONY: all clean fclean


CYAN	:= \033[36;1m
RESET	:= \033[0m