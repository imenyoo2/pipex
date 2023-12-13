/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayait-el <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/03 15:39:51 by ayait-el          #+#    #+#             */
/*   Updated: 2023/11/05 10:51:00 by ayait-el         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	free_list(t_list *base)
{
	t_list	*tmp;

	while (base)
	{
		free(base->content);
		tmp = base;
		base = base->next;
		free(tmp);
	}
}
// TODO: if c = '\0' you should return [s, NULL]

static int	add_list(char *start, char *end, t_list **head, t_list **base)
{
	t_list	*new;
	char	*content;

	content = ft_substr(start, 0, end - start);
	if (content == NULL)
		return (0);
	if (*content == '\0')
	{
		free(content);
		return (2);
	}
	new = malloc(sizeof(t_list));
	if (new == NULL)
	{
		free(content);
		return (0);
	}
	new->content = content;
	new->next = NULL;
	if (*head)
		(*head)->next = new;
	else
		*base = new;
	(*head) = new;
	return (1);
}

static int	get_malloc_size(char const *s, char c, t_list **head, t_list **base)
{
	int		count;
	char	*start;
	char	*end;
	int		add_status;

	start = (char *)s;
	end = start;
	count = 0;
	while (end && *end)
	{
		end = ft_strchr(start, c);
		add_status = add_list(start, end, head, base);
		if (!add_status)
			return (-1);
		if (add_status == 1)
			count++;
		if (end && *end)
			end++;
		start = end;
	}
	return (count);
}

static void	fill_array(char **arr, t_list *base)
{
	t_list	*tmp;
	size_t	i;

	i = 0;
	while (base)
	{
		arr[i] = base->content;
		tmp = base;
		base = base->next;
		free(tmp);
		i++;
	}
	arr[i] = NULL;
}

char	**ft_split(char const *s, char c)
{
	t_list	*head;
	t_list	*base;
	int		malloc_size;
	char	**arr;

	if (!s)
		return (NULL);
	head = NULL;
	base = NULL;
	malloc_size = get_malloc_size(s, c, &head, &base);
	if (malloc_size == -1)
	{
		free_list(base);
		return (NULL);
	}
	arr = malloc(sizeof(char *) * (malloc_size + 1));
	if (arr == NULL)
	{
		free_list(base);
		return (NULL);
	}
	fill_array(arr, base);
	return (arr);
}

/*
	 int main(void)
	 {
	 ft_split("hello!", 32:' ');
	 return 0;
	 }
	 */
