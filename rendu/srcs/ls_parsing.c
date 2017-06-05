/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bduron <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/29 19:18:26 by bduron            #+#    #+#             */
/*   Updated: 2017/05/31 14:57:59 by bduron           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ls.h"

void ls_usage(char opt)
{
	printf("ls: illegal option -- %c\n", opt);
	printf("usage: ls [-Ralrt] [file ...]\n");
	exit(1);
} 

void clean_target(t_env *e)
{
	t_list *tmp;

	struct stat file_stat;

	tmp = e->target;		
	while (tmp)
	{
		if (stat((char *)tmp->content, &file_stat) < 0)
		{	
			printf("ls: %s: %s\n", (char *)tmp->content, strerror(errno));	
			free(tmp->content);
			tmp->content = NULL;
		}
		tmp = tmp->next;	
	}
}

void get_target(int argc, char **argv, int i, t_env *e)
{
	size_t ntarget;

	ntarget = argc - i;
	if (ntarget == 0)
		e->target = ft_lstnew(".", 2);
	else 
	{
		e->target = ft_lstnew(argv[i], sizeof(char) * strlen(argv[i]) + 1);
		i++;
		while (i < argc)
		{	
			ft_lstappend(&(e->target), 
					ft_lstnew(argv[i], sizeof(char) * strlen(argv[i]) + 1));
			i++;
		}
		clean_target(e);
	}
}

int get_opt(int argc, char **argv, t_env *e)
{
	int i; 

	i = 1;
	while (i < argc && argv[i][0] == '-' && argv[i][1] != '\0')
	{
		if (strcmp(argv[i], "--") == 0)
		{
			i++;
			break;
		}
		while (*++argv[i] != '\0')
		{
			if (*argv[i] == 'l')
				e->opts |= FT_LIST;	
			else if (*argv[i] == 'R')
				e->opts |= FT_RECURSIVE;	
			else if (*argv[i] == 'a')
				e->opts |= FT_HIDDEN;	
			else if (*argv[i] == 'r')
				e->opts |= FT_REVERSE;	
			else if (*argv[i] == 't')
				e->opts |= FT_TSORT;	
			else 
				ls_usage(*argv[i]);	
		}	
		i++;
	}
	return (i);
}	
