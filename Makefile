# **************************************************************************** #
#                                                                              #
#                                                         ::::::::             #
#    Makefile                                           :+:    :+:             #
#                                                      +:+                     #
#    By: tmercier <tmercier@student.codam.nl>         +#+                      #
#                                                    +#+                       #
#    Created: 2021/12/02 17:13:26 by tmercier      #+#    #+#                  #
#    Updated: 2023/03/14 12:12:56 by tmercier      ########   odam.nl          #
#                                                                              #
# **************************************************************************** #

CFLAGS 	+= 	-g3 -fsanitize=address -I.
SRCS 	= 	philo.c util.c
OBJS 	=	$(addprefix out/, $(SRCS:.c=.o))
BIN 	= 	philo
LFLAGS 	+= 	-lreadline
CC 		= 	cc

$(shell mkdir -p out)

all: $(BIN)
	$(MAKE) -C ../libs

$(BIN): $(OBJS) ../libs/lib42.a
	$(CC) $(CFLAGS) -o $@ $^ $(LFLAGS)

out/%.o: %.c philo.h
	@printf "$(CYAN)Compiling: $(RESET)$(notdir $<)\n"
	@$(CC) $(CFLAGS) -c -o $@ $<

../libs/lib42.a:
	$(MAKE) -C ../libs

clean:
	$(MAKE) -C ../libs clean
	rm -rf $(OBJS)

fclean: clean
	$(MAKE) -C ../libs fclean
	rm -rf $(BIN)

re: fclean all

.PHONY: all clean fclean


CYAN	:= \033[36;1m
RESET	:= \033[0m