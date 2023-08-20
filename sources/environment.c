/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environment.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchoquet <tchoquet@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/07 19:59:47 by tchoquet          #+#    #+#             */
/*   Updated: 2023/08/20 17:16:21 by tchoquet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "environment.h"

t_env_list	*lstenv_chr(const char *key, t_bool create);

t_env_list	**get_lstenv(void);
char		*env_entry_to_str(t_env_entry entry);

t_bool		is_valid_env_key(const char *str);
int			analize_keyval(const char *keyval, t_env_entry *result);
char		*set_error_return(int *error, int value);

int	set_env(const char *key, const char *val, t_bool export)
{
	t_env_list	*founded;

	if (is_valid_env_key(key) == false)
		return (BAD_ENVIRONMENT_KEY);
	founded = lstenv_chr(key, true);
	if (founded == NULL)
		return (MALLOC_ERROR);
	founded->data->value = ft_strdup(val);
	if (val != NULL && founded->data->value == NULL)
		return (MALLOC_ERROR);
	if (export == true)
		founded->data->is_export = true;
	return (0);
}

int	set_env_single_str(const char *keyval, t_bool export)
{
	t_env_entry	input;
	t_env_list	*founded;
	int			temp_ret;

	temp_ret = analize_keyval(keyval, &input);
	if (temp_ret != 0)
		return (temp_ret);
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

char	*get_env(const char *key, int *error_code)
{
	t_env_list	*founded;
	char		*str;

	if (error_code != NULL)
		*error_code = 0;
	if (is_valid_env_key(key) == false)
		return (set_error_return(error_code, BAD_ENVIRONMENT_KEY));
	founded = lstenv_chr(key, false);
	if (founded == NULL)
		return (set_error_return(error_code, 0));
	str = ft_strdup(founded->data->value);
	if (founded->data->value == NULL || str != NULL)
		return (str);
	return (set_error_return(error_code, MALLOC_ERROR));
}

char	**get_envp(void)
{
	char		**envp;
	t_env_list	*current;
	t_uint64	i;

	current = *(get_lstenv());
	envp = ft_calloc(ft_lstsize((t_list *)current) + 1, sizeof(char *));
	if (envp == NULL)
		return (NULL);
	i = 0;
	while (current != NULL)
	{
		if (current->data->is_export == true && current->data->value != NULL)
		{
			envp[i] = env_entry_to_str(*current->data);
			if (envp[i] == NULL)
			{
				free_splited_str(envp);
				return (NULL);
			}
			i++;
		}
		current = current->next;
	}
	return (envp);
}

int	export_env(const char *key)
{
	t_env_list	*founded;

	if (is_valid_env_key(key) == false)
		return (BAD_ENVIRONMENT_KEY);
	founded = lstenv_chr(key, true);
	if (founded == NULL)
		return (MALLOC_ERROR);
	founded->data->is_export = true;
	return (0);
}
