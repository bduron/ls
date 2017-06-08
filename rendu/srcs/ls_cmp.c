/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ls_cmp.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bduron <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/07 09:33:48 by bduron            #+#    #+#             */
/*   Updated: 2017/06/08 09:37:02 by bduron           ###   ########.fr       */
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
