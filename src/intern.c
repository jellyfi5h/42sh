
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intern.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aboukhri <aboukhri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/24 21:41:01 by onouaman          #+#    #+#             */
/*   Updated: 2019/11/26 00:01:41 by aboukhri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

/****** intern variable management ***** */

void		add_intern_var(char *key, char *value)
{
    char *line;
    t_intern *lst;

    line = ft_strjoir(ft_strjoin(key, "="), value, 1);
    if (ft_edit_vrb(line, &g_environ, 1))
        return ;
    if (!g_intern)
        g_intern = new_intern(key, value);
    else
    {
        lst = g_intern;
        while (lst)
        {
            if (ft_strcmp(lst->key, key) == 0)
            {
                free(lst->value);
                lst->value = ft_strdup(value);
                return ;
            }
            if (!lst->next)
                break;
            lst = lst->next;
        }
        lst->next = new_intern(key, value);
    }
}

int		delete_intern_var(char *key, t_intern **head)
{
    t_intern *tmp;
    t_intern *prev;

    tmp = *head;
    prev = NULL;
    if (tmp != NULL && ft_strcmp(tmp->key, key) == 0)
    {
        *head = tmp->next;
        free(tmp);
        return (1);
    }
    while (tmp && ft_strcmp(tmp->key, key) != 0)
    {
        prev = tmp;
        tmp = tmp->next;
    }
    if (!tmp)
        return (0);
    prev->next = tmp->next;
    ft_strdel(&tmp->key);
    ft_strdel(&tmp->value);    
    free(tmp);
    return (1);
}

t_intern	get_key_value(t_tokens *st_tokens)
{
	t_intern	var;

	var.key = st_tokens->value;
	st_tokens->is_arg = T_EQUAL;
	if (NEXT && NEXT->next && NEXT->next->indx == st_tokens->indx)
	{
		NEXT->next->is_arg = T_EQUAL;
		var.value = NEXT->next->value;
	}
	else
		var.value = "";
	NEXT->is_arg = T_EQUAL;
	return (var);
}

char		*get_intern_value(char *key)
{
    t_intern *lst;

    lst = g_intern;
    while (lst)
    {
        if (ft_strcmp(key, lst->key) == 0)
            return (ft_strdup(lst->value));
        lst = lst->next;
    }
    return (NULL);
}


void    delete_intern()
{
    t_intern *lst;
    t_intern *next;

    lst = g_intern;
    while (lst)
    {
        next = lst->next;        
        ft_strdel(&lst->key);
        ft_strdel(&lst->value);
        lst = next;
    }
}