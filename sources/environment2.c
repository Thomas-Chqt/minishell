/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environment2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchoquet <tchoquet@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/19 17:25:41 by tchoquet          #+#    #+#             */
/*   Updated: 2023/08/19 17:56:26 by tchoquet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "environment.h"

t_env_list	*lstenv_chr(const char *key, t_bool create);

int		analize_keyval(const char *keyval, t_env_entry *result);
char	*set_error_return(int *error, int value);

char	*get_env_create(const char *keyval, int *error_code)
{
	t_env_entry	input;
	t_env_list	*founded;
	int			temp_ret;
	char		*str;

	temp_ret = analize_keyval(keyval, &input);
	if (temp_ret != 0)
		return (set_error_return(error_code, temp_ret));
	founded = lstenv_chr(input.key, false);
	free(input.key);
	if (founded == NULL)
	{
		*error_code = 0;
		if (input.value != NULL)
			*error_code = set_env_single_str(keyval, false);
		if (*error_code == 0)
			return (input.value);
		free(input.value);
		return (NULL);
	}
	free(input.value);
	str = ft_strdup(founded->data->value);
	if (str != NULL)
		return (str);
	return (set_error_return(error_code, MALLOC_ERROR));
}
