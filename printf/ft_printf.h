/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayait-el <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/06 13:45:49 by ayait-el          #+#    #+#             */
/*   Updated: 2023/12/15 15:11:53 by ayait-el         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdarg.h>
# include <unistd.h>
# include <stdlib.h>

/*
# ifdef DEBUG
#  include <stdio.h>
#  define KNRM  "\x1B[0m"
#  define KRED  "\x1B[31m"
#  define KGRN  "\x1B[32m"
#  define KYEL  "\x1B[33m"
#  define KBLU  "\x1B[34m"
#  define KMAG  "\x1B[35m"
#  define KCYN  "\x1B[36m"
#  define KWHT  "\x1B[37m"

#  define RED(x) printf(KRED); x; printf(KNRM); fflush(stdout)
# endif
*/

typedef enum flag
{
	JUSTIFY = 1 << 0,
	ZERO = 1 << 1,
	DOT = 1 << 2,
	PLUS = 1 << 3,
	SPACE = 1 << 4,
	MINUS = 1 << 5,
	HASHTAG = 1 << 6
}					t_flag;

typedef enum type
{
	STRING = 0,
	INT = 1,
}					t_type;

typedef struct format
{
	int				flags;
	char			conversion;
	size_t			justify;
	unsigned int	zero;
	unsigned int	dot;
	void			(*f)(struct format *, va_list ptr);
	size_t			printed;
	size_t			spaces;
	size_t			order[7];
	size_t			current_order;
}					t_format;

int					ft_printf_err(const char *format, ...);

void				set_conversions(const char *str, t_format *format);
size_t				ft_convert(const char *str, size_t *byt_counter,
						va_list ptr);

// printers
void				print_char(t_format *format, va_list ptr);
void				print_string(t_format *format, va_list ptr);
void				print_pointer(t_format *format, va_list ptr);
void				print_int(t_format *format, va_list ptr);
void				print_unsigned(t_format *format, va_list ptr);
void				print_uhex(t_format *format, va_list ptr);
void				print_hex(t_format *format, va_list ptr);
void				print_persent(t_format *format, va_list ptr);

// helpers
void				ft_putnbr_base(size_t nbr, const char *base);
void				ft_putsnbr_base(ssize_t nbr, const char *base);
size_t				ft_strlen(const char *s);
unsigned int		get_print_size(size_t nb, unsigned int baselen,
						t_format *format);
unsigned int		get_print_ssize(ssize_t nb, unsigned int baselen,
						t_format *format);
int					ft_atoi(const char *str);
size_t				min(size_t a, size_t b);
size_t				max(size_t a, size_t b);
void				print_nchar(char c, int n, t_format *format);
void				print_sign(int n, t_format *format);
void				put_char(char c, int n);
int					print_the_wierd_stuff(t_format *format);
void				pad_left(t_format *format, t_type type);
void				pad_right(t_format *format, t_type type);
void				pad_zero(t_format *format);
void				pad_zero_hex(t_format *format, unsigned int holder);
void				put_nstr(char *str, size_t len);
void				pad_zero_string(t_format *format);
const char			*skip_num(const char *str);
void				set_order(t_format *format, t_flag flag);
size_t				get_order(t_format *format, t_flag flag);
void				init_struct(t_format *format);
void				manage_flags_int(t_format *format);
size_t				get_max_pad(t_format *format, t_type type);
void				manage_flags_hex(t_format *format, unsigned int nb);
void				pad_left_hex(t_format *format, t_type type,
						unsigned int nb);
void				manage_flags_string(t_format *format);
int					safe_write(const char *ptr, int n);
void				pad_zero_ptr(t_format *format);
void				pad_left_ptr(t_format *format, t_type type);
void				manage_flags_char(t_format *format);
const char			*skip_white_spaces(const char *str);
int					get_result(const char *str);

// managers
void				convert_zero_to_justify(t_format *format);
void				convert_justify_to_zero(t_format *format);
void				convert_zero_to_dot(t_format *format);

// handling flags
const char			*set_justify(t_format *format, const char *str);
const char			*set_zero(t_format *format, const char *str);
const char			*set_dot(t_format *format, const char *str);
const char			*set_space(t_format *format, const char *str);
const char			*set_plus(t_format *format, const char *str);
const char			*set_minus(t_format *format, const char *str);
int					set_flags(t_format *format, const char *str);

#endif
