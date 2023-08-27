/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environment2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchoquet <tchoquet@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/19 17:25:41 by tchoquet          #+#    #+#             */
/*   Updated: 2023/08/24 14:30:05 by tchoquet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "environment.h"

char		*set_error_return(int *error, int value);
t_env_entry	str_to_env_entry(const char *str);

t_env_list	*lstenv_chr(const char *key, t_bool create);

static int	analize_keyval(const char *keyval, t_env_entry *input);

int	set_env_single_str(const char *keyval, t_bool export)
{
	t_env_entry	input;
	t_env_list	*founded;
	int			temp_ret;

	temp_ret = is_valid_keyval(keyval);
	if (temp_ret != 0)
		return (temp_ret);
	input = str_to_env_entry(keyval);
	if (input.key == NULL)
		return (MALLOC_ERROR);
	founded = lstenv_chr(input.key, true);
	free(input.key);
	if (founded == NULL)
	{
		free(input.value);
		return (MALLOC_ERROR);
	}
	free(founded->data->value);
	founded->data->value = input.value;
	if (export == true)
		founded->data->is_export = true;
	return (0);
}

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

static int	analize_keyval(const char *keyval, t_env_entry *input)
{
	int	temp_ret;

	temp_ret = is_valid_keyval(keyval);
	if (temp_ret != 0)
		return (temp_ret);
	*input = str_to_env_entry(keyval);
	if (input->key == NULL)
		return (MALLOC_ERROR);
	return (0);
}
