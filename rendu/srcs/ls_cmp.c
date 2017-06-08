/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ls_cmp.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bduron <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/07 09:33:48 by bduron            #+#    #+#             */
/*   Updated: 2017/06/08 16:23:53 by bduron           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ls.h"

int cmp_av(void const *a, void const *b)
{	
	char const *pa = *(const char**)a;
	char const *pb = *(const char**)b;

	return (ft_strcmp(pa, pb)); 
}

int ls_cmpname(t_list *a, t_list *b)
{
	char *name_a;
	char *name_b;

	name_a = ((t_data *)a->content)->dirent->d_name;
	name_b = ((t_data *)b->content)->dirent->d_name;

	return (ft_strcmp(name_a, name_b));
}

int ls_cmpmtime(t_list *a, t_list *b)
{
	char *name_a;
	char *name_b;
	long time_a;
	long time_b;

	time_a = ((t_data *)a->content)->stat.st_mtime;
	time_b = ((t_data *)b->content)->stat.st_mtime;
	name_a = ((t_data *)a->content)->dirent->d_name;
	name_b = ((t_data *)b->content)->dirent->d_name;
	if (time_a == time_b)
		return (ft_strcmp(name_a, name_b));
	return (time_b - time_a);
}
