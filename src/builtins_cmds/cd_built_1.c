/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_built_1.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfilahi <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/07 04:31:53 by mfilahi           #+#    #+#             */
/*   Updated: 2019/12/07 04:33:07 by mfilahi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

char	*rmbackslashs_1(char *path, int len)
{
	int		i;
	int		j;
	char	*freshstr;

	freshstr = NULL;
	freshstr = ft_strnew(len);
	i = 0;
	j = 0;
	while (path[j])
	{
		if (path[j] != -1)
			freshstr[i++] = path[j];
		j++;
	}
	ft_strdel(&path);
	freshstr[i] = '\0';
	return (freshstr);
}

char	*rmbackslashs(char *path)
{
	int	i;
	int	j;

	i = 0;
	while (path[i])
	{
		if (path[i] == '/')
		{
			i += 1;
			while (path[i] && path[i] == '/')
				path[i++] = -1;
		}
		else
			i++;
	}
	j = 0;
	i = 0;
	while (path[j])
	{
		if (path[j] != -1)
			i++;
		j++;
	}
	return (rmbackslashs_1(path, i));
}

char	*changepath(char *path)
{
	int		j;
	char	*tmp;
	char	*newpath;
	int		i;

	j = 0;
	i = -1;
	while (path[++i])
		if (path[i] == '/')
			j = i;
	newpath = ft_strsub(path, 0, j);
	if (!newpath[0])
	{
		tmp = newpath;
		newpath = ft_strdup("/");
		ft_strdel(&tmp);
	}
	ft_strdel(&path);
	return (newpath);
}

char	*createnewpath(char *path, char *pwd)
{
	char	**arr;
	int		i;

	arr = ft_strsplit(path, '/');
	i = 0;
	while (arr[i])
	{
		if ((ft_strcmp(arr[i], "..") == 0))
			pwd = changepath(pwd);
		else if ((ft_strcmp(arr[i], ".") != 0))
			pwd = ft_strjoir(pwd, ft_strjoir("/", arr[i], 0), 3);
		i++;
	}
	pwd = rmbackslashs(pwd);
	ft_free2d(arr);
	return (pwd);
}

char	*handlepath(t_cdpkg *v, char *pwd)
{
	char	*newpath;

	if (!(pwd = ft_get_vrb("PWD", g_environ)))
		pwd = ft_strdup(getcwd(v->buff, 1024));
	if (v->path[0] == '/')
	{
		ft_strdel(&pwd);
		pwd = v->path;
		if (v->path[ft_strlen(v->path) - 1] == '/')
		{
			v->path = ft_strsub(v->path, 0, (ft_strlen(v->path) - 1));
			ft_strdel(&pwd);
		}
		return (v->path);
	}
	else if ((ft_strcmp(v->path, ".") == 0) ||\
			(ft_strcmp(v->path, "./") == 0))
	{
		newpath = ft_strdup(pwd);
		ft_strdel(&pwd);
	}
	else
		newpath = createnewpath(v->path, pwd);
	ft_strdel(&v->path);
	return (newpath);
}