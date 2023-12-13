
OBJS = convert_bonus.o flags2_bonus.o flags_bonus.o helpers.o helpers2_bonus.o\
		helpers3_bonus.o helpers4_bonus.o helpers5_bonus.o helpers6_bonus.o\
		helpers7_bonus.o managers_bonus.o printers2_bonus.o printers_bonus.o printf.o

CC = cc

CFLAGS = -Wall -Werror -Wextra

AR = ar -rsc

NAME = libftprintf.a

all: $(NAME)

bonus: all

$(NAME): $(OBJS)
	$(AR) $(NAME) $(OBJS)

%.o: %.c ft_printf.h
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONEY: all bonus clean fclean re
