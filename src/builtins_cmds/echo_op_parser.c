/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo_op_parser.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfilahi <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/26 15:38:30 by mfilahi           #+#    #+#             */
/*   Updated: 2019/09/26 15:38:40 by mfilahi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

/*
** echo option parser;
*/

int		echo_options_(char *arg, int *flag)
{
	while (*arg)
	{
		if (*arg == 'n' && (*flag & e_flg))
			*flag = e_flg | n_flg;
		else if (*arg == 'n')
			*flag = 0 | n_flg;
		else if (*arg == 'n' && ((*flag & n_flg) || (*flag == (n_flg | e_flg))))
			*flag = n_flg | e_flg;
		else if (*arg == 'e' && (*flag & n_flg))
			*flag = e_flg | n_flg;
		else if (*arg == 'e')
			*flag = 0 | e_flg;
		else if (*arg == 'E' && ((*flag & n_flg) || (*flag == (n_flg | e_flg))))
			*flag = 0 | n_flg;
		else if (*arg == 'E')
			*flag = 0 | E_flg;
		arg++;
	}
	return (1);
}

int		e_interpretation_1(char *arg)
{
	int i;

	if (!arg)
		return (0);
	i = 0;
	while (arg[i])
	{
		if (!(arg[i] == -1))
		{
			if (write(1, &arg[i], 1) == -1)
			{
				ft_strdel(&arg);
				return (-1);
			}
		}
		i++;
	}
	ft_strdel(&arg);
	return (0);
}

/*
** - check of metacharacters;
*/

int		echo_meta_char(char c)
{
	if (c == 'a')
		return ('\a');
	else if (c == 'b')
		return ('\b');
	else if (c == 'f')
		return ('\f');
	else if (c == 'n')
		return ('\n');
	else if (c == 'r')
		return ('\r');
	else if (c == 't')
		return ('\t');
	else if (c == 'v')
		return ('\v');
	else if (c == '\\')
		return ('\\');
	return (c);
}

/*
** - comparison of chars;
*/

char	echo_charcmp(char c, char *str)
{
	while (*str)
	{
		if (*str++ == c)
			return (echo_meta_char(c));
	}
	return (c);
}
