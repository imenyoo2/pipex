
OBJS = test.o helpers.o error_handlers.o
OBJS_BONUS = test_bonus.o helpers_bonus.o error_handlers.o
NAME = pipex
OFLAGS = -Wall -Werror -Wextra
LIBS = libft/libft.a printf/libftprintf.a
$(CC) = cc

# takes subdir as input
define MAKE_LIB
	make $1 -C $2

endef


all: $(NAME)

$(NAME): $(OBJS) $(LIBS)
	$(CC) $(OFLAGS) $(OBJS) $(LIBS) -o $@

%.o: %.c pipex.h
	cc $(OFLAGS) -c $< -o $@

%.a:
	$(call MAKE_LIB,all,$(word 1,$(subst /, ,$*)))

clean:
	$(foreach lib,$(LIBS),$(call MAKE_LIB,clean,$(word 1,$(subst /, ,$(lib)))))
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)
	rm -f $(LIBS)

re: fclean all

.PHONEY: all clean fclean re
