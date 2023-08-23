/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str_split_whitespc.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchoquet <tchoquet@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/26 00:07:36 by tchoquet          #+#    #+#             */
/*   Updated: 2023/08/27 10:23:52 by tchoquet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft_internal.h"

static size_t	count_split(const char *s);
static void		fill_split_array(const char *s, char ***split_array,
					size_t array_len);
static void		free_split_array(char ***split_array);

char	**str_split_whitespc(char const *s)
{
	size_t	split_count;
	char	**split_array;

	if (s[0] == '\0')
	{
		split_array = ft_calloc(2, sizeof(char *));
		if (split_array == NULL)
			return (NULL);
		split_array[0] = ft_strdup("");
		if (split_array[0] == NULL)
		{
			free(split_array);
			return (NULL);
		}
		return (split_array);
	}
	split_count = count_split(s);
	split_array = ft_calloc(split_count + 1, sizeof(char *));
	if (split_array == NULL)
		return (NULL);
	fill_split_array(s, &split_array, split_count);
	return (split_array);
}

static size_t	count_split(const char *s)
{
	size_t	split_count;
	size_t	split_len;
	size_t	i;

	if (s == NULL)
		return (0);
	split_count = 0;
	split_len = 0;
	i = 0;
	while (s[i])
	{
		if (!is_whitespace(s[i]))
			split_len++;
		else if (is_whitespace(s[i]) && split_len > 0)
		{
			split_count++;
			split_len = 0;
		}
		i++;
	}
	if (split_len > 0)
		split_count++;
	return (split_count);
}

static void	fill_split_array(const char *s, char ***split_array,
					size_t array_len)
{
	size_t	i;
	size_t	split_len;	
	size_t	split_count;

	i = -1;
	split_len = 0;
	split_count = 0;
	while (split_count < array_len)
	{
		if (is_whitespace(s[++i]) || s[i] == '\0')
		{
			if (split_len == 0)
				continue ;
			(*split_array)[split_count]
				= ft_substr(s, (unsigned int)(i - split_len), split_len);
			if ((*split_array)[split_count++] == NULL)
			{
				free_split_array(split_array);
				return ;
			}
			split_len = 0;
		}
		else
			split_len++;
	}
}

static void	free_split_array(char ***split_array)
{
	size_t	i;

	i = 0;
	while ((*split_array)[i])
	{
		free((*split_array)[i]);
		(*split_array)[i++] = NULL;
	}
	free((*split_array));
	(*split_array) = NULL;
}
