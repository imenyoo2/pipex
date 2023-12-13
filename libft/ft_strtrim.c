/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayait-el <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/03 16:26:01 by ayait-el          #+#    #+#             */
/*   Updated: 2023/11/04 14:56:06 by ayait-el         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	is_in(char c, char const *set)
{
	size_t	i;

	i = 0;
	while (set[i])
	{
		if (set[i] == c)
			return (1);
		i++;
	}
	return (0);
}

static void	fill_array(const char *src, char *result, size_t start, size_t end)
{
	size_t	i;

	i = 0;
	while (start <= end)
	{
		result[i] = src[start];
		start++;
		i++;
	}
	if (result[i - 1])
		result[i] = '\0';
}

static void	get_end_start(size_t *start, size_t *end, char const *s1,
		char const *set)
{
	*start = 0;
	*end = ft_strlen(s1);
	if (s1[*end] == '\0' && *end != 0)
		(*end)--;
	while (1)
	{
		if (*start > *end || (*start == 0 && *end == 0))
			return ;
		if (is_in(s1[*start], set))
			(*start)++;
		else if (is_in(s1[*end], set))
			(*end)--;
		else
			break ;
	}
}

char	*ft_strtrim(char const *s1, char const *set)
{
	size_t	start;
	size_t	end;
	char	*result;

	if (s1 == NULL || set == NULL)
		return (NULL);
	get_end_start(&start, &end, s1, set);
	if (start > end || (start == 0 && end == 0))
	{
		result = malloc(1);
		if (result == NULL)
			return (NULL);
		result[0] = '\0';
		return (result);
	}
	result = malloc(sizeof(char) * (end - start + 2));
	if (result == NULL)
		return (NULL);
	fill_array(s1, result, start, end);
	return (result);
}
