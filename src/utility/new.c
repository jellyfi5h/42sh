/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aboukhri <aboukhri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/07 05:20:40 by onouaman          #+#    #+#             */
/*   Updated: 2019/11/25 19:00:11 by aboukhri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

t_cmds		*ft_new_cmds(void)
{
	t_cmds	*st_cmds;

	if ((st_cmds = (t_cmds *)malloc(sizeof(t_cmds))) == NULL)
		return (NULL);
	st_cmds->fd = NULL;
	st_cmds->st_jobctr = NULL;
	st_cmds->st_tokens = NULL;
	st_cmds->next = NULL;
	return (st_cmds);
}

t_jobctr	*ft_new_jobctr(void)
{
	t_jobctr	*st_jobctr;

	if ((st_jobctr = (t_jobctr *)malloc(sizeof(t_jobctr))) == NULL)
		return (NULL);
	st_jobctr->st_logopr = NULL;
	st_jobctr->st_tokens = NULL;
	st_jobctr->status = 0;
	st_jobctr->next = NULL;
	return (st_jobctr);
}

t_logopr	*ft_new_logopr(void)
{
	t_logopr	*st_logopr;

	if ((st_logopr = (t_logopr *)malloc(sizeof(t_logopr))) == NULL)
		return (NULL);
	st_logopr->st_pipes = NULL;
	st_logopr->st_tokens = NULL;
	st_logopr->status = 0;
	st_logopr->bl_jobctr = 0;
	st_logopr->next = NULL;
	return (st_logopr);
}

t_tokens	*ft_new_token(void)
{
	t_tokens	*st_token;

	if ((st_token = (t_tokens *)malloc(sizeof(t_tokens))) == NULL)
		return (NULL);
	st_token->token = 0;
	st_token->value = NULL;
	st_token->prev = NULL;
	st_token->next = NULL;
	st_token->indx = -1;
	st_token->is_arg = 0;
	st_token->aliased = 0;
	return (st_token);
}

t_pipes		*ft_new_pipe(void)
{
	t_pipes *st_pipes;

	if ((st_pipes = (t_pipes *)malloc(sizeof(t_pipes))) == NULL)
		return (NULL);
	st_pipes->args = NULL;
	ft_bzero(st_pipes->fds, 2);
	st_pipes->st_redir = NULL;
	st_pipes->st_tokens = NULL;
	st_pipes->tmp_env = NULL;
	st_pipes->next = NULL;
	st_pipes->bl_jobctr = 0;
	return (st_pipes);
}
