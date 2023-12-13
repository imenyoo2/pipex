OBJS = ft_bzero.o ft_calloc.o ft_isalnum.o ft_isalpha.o ft_isascii.o\
       ft_isdigit.o ft_isprint.o ft_itoa.o ft_memchr.o ft_memcpy.o ft_memmove.o\
       ft_memset.o ft_putchar_fd.o ft_putendl_fd.o ft_putnbr_fd.o ft_putstr_fd.o\
       ft_strchr.o ft_striteri.o ft_strjoin.o ft_strmapi.o ft_strrchr.o\
       ft_strtrim.o ft_substr.o ft_tolower.o ft_toupper.o ft_atoi.o ft_strncmp.o ft_strlcpy.o\
       ft_strdup.o ft_strlcat.o ft_split.o ft_memcmp.o ft_strnstr.o

BONUS_OBJS = ft_lstadd_back_bonus.o ft_lstadd_front_bonus.o ft_lstclear_bonus.o\
             ft_lstdelone_bonus.o ft_lstiter_bonus.o ft_lstlast_bonus.o\
             ft_lstmap_bonus.o ft_lstnew_bonus.o ft_lstsize_bonus.o

OFLAGS = -Wall -Werror -Wextra

NAME = libft.a

AR = ar -rcs

all: $(NAME)

$(NAME): $(OBJS)
	$(AR) $(NAME) $(OBJS)

bonus: $(OBJS) $(BONUS_OBJS)
	$(AR) $(NAME) $(BONUS_OBJS) $(OBJS)

%_bonus.o: %_bonus.c libft.h
	cc $(OFLAGS) -c $< -o $@

%.o: %.c libft.h
	cc $(OFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re bonus
