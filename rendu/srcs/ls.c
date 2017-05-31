/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ls.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bduron <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/29 19:18:26 by bduron            #+#    #+#             */
/*   Updated: 2017/05/31 16:57:22 by bduron           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ls.h"

void env_init(t_env *e)
{
	e->opts = 0;
//	e->files = NULL;
	e->target = NULL;

}

void del_target(void *content, size_t content_size)
{
	free(content);
	content_size = 0;
}

void clean_target(t_env *e)
{
	t_list *tmp;
	t_list *prev;

	struct stat file_stat;

	tmp = e->target;		
	prev = tmp;
	while (tmp)
	{
		if (stat((char *)tmp->content, &file_stat) < 0)
		{	
			printf("ls: %s: %s\n", (char *)tmp->content, strerror(errno));	
			if (prev == tmp)
			   e->target = e->target->next;	
			if (tmp->next == NULL)
				prev->next = NULL;
			prev->next = tmp->next;
			ft_lstdelone(&tmp, del_target);
		}
		prev = tmp;
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
				return (ERR_WRONGOPT);
		}	
		i++;
	}
	return (i);
}	



int main(int argc, char **argv)
{
	t_list *tmp;
	t_env e;


	env_init(&e);

	if ((e.nopts = get_opt(argc, argv, &e)) < 0)
	{
		printf("error\n"); // improve error put Usage()
		exit(1);
	}

	get_target(argc, argv, e.nopts, &e);		


	printf("opts: %d\n", e.opts); //

	tmp = e.target;
	while (tmp)	//
	{
		printf("%s\n", (char *)tmp->content);
		tmp = tmp->next;
	}

	//free(e.target);

	return (0);
}

