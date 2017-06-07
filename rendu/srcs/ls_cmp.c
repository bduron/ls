/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ls_cmp.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bduron <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/07 09:33:48 by bduron            #+#    #+#             */
/*   Updated: 2017/06/07 09:35:24 by bduron           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ls.h"

int cmp_av(void const *a, void const *b)
{	
	char const *pa = *(const char**)a;
	char const *pb = *(const char**)b;

	return (ft_strcmp(pa, pb)); 
}
