/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environment2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchoquet <tchoquet@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/19 17:25:41 by tchoquet          #+#    #+#             */
/*   Updated: 2023/08/21 15:20:25 by tchoquet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "environment.h"

t_bool		is_env_key_equal(void *entry, void *key);
void		delete_entry(void *v_entry);

t_env_list	*lstenv_chr(const char *key, t_bool create);

int			analize_keyval(const char *keyval, t_env_entry *result);
t_bool		is_valid_env_key(const char *str);
char		*set_error_return(int *error, int value);

char	*get_env_create(const char *keyval, int *error_code)
{
	t_env_entry	input;
	t_env_list	*founded;
	int			temp_ret;
	char		*str;

	if (error_code != NULL)
		*error_code = 0;
	temp_ret = analize_keyval(keyval, &input);
	if (temp_ret != 0)
		return (set_error_return(error_code, temp_ret));
	founded = lstenv_chr(input.key, true);
	free(input.key);
	if (founded == NULL)
	{
		free(input.value);
		return (set_error_return(error_code, MALLOC_ERROR));
	}
	if (founded->data->value == NULL)
		founded->data->value = input.value;
	else
		free(input.value);
	str = ft_strdup(founded->data->value);
	if (founded->data->value == NULL || str != NULL)
		return (str);
	return (set_error_return(error_code, MALLOC_ERROR));
}

int	delete_env(const char *key)
{
	if (is_valid_env_key(key) == false)
		return (BAD_ENVIRONMENT_KEY);
	lst_delif(
		(t_list **)(get_lstenv()),
		&delete_entry, &is_env_key_equal,
		(void *)key);
	return (0);
}
