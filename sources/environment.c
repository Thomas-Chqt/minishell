/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environment.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchoquet <tchoquet@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/07 19:59:47 by tchoquet          #+#    #+#             */
/*   Updated: 2023/08/18 17:24:16 by tchoquet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "environment.h"

t_env_list	*lstenv_new(char *key, char *val, t_bool is_export);
t_env_list	*lstenv_new_single_str(const char *keyval, t_bool is_export);
t_env_list	*lstenv_chr(const char *key, t_bool create);
void		lstenv_add_back(t_env_list	*new_node);

t_env_list	**get_lstenv(void);
char		*env_entry_to_str(t_env_entry entry);
t_env_entry	str_to_env_entry(const char *str);

t_bool		is_valid_env_key(const char *str);

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

	if (is_valid_env_key(keyval) == false)
		return (BAD_ENVIRONMENT_KEY);
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
	founded->data->value = input.value;
	if (export == true)
		founded->data->is_export = true;
	return (0);
}

char	*get_env(const char *key, int *error_code)
{
	t_env_list	*founded;
	char		*str;

	if (is_valid_env_key(key) == false)
	{
		if (error_code != NULL)
			*error_code = BAD_ENVIRONMENT_KEY;
		return (NULL);
	}
	founded = lstenv_chr(key, false);
	if (founded == NULL)
	{
		if (error_code != NULL)
			*error_code = 0;
		return (NULL);
	}
	str = ft_strdup(founded->data->value);
	if (str != NULL)
		return (str);
	if (error_code != NULL)
		*error_code = MALLOC_ERROR;
	return (NULL);
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
