/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmp.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bduron <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/07 17:20:38 by bduron            #+#    #+#             */
/*   Updated: 2017/06/07 17:48:14 by bduron           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>


int min(int a, int b)
{
	return (a < b) ? a : b;
}

int max(int a, int b)
{
	return (a < b) ? b : a;
}

void print_cmp(int a, int b, int (*cmp)(), char *s)
{
	int res; 

	res = cmp(a, b);	
	printf("%s = %d\n", s, res);
	return ;
}

int main(int argc, char **argv)
{
	int a = atoi(argv[1]);	
	int b = atoi(argv[2]);	

	print_cmp(a, b, min, "min");
	print_cmp(a, b, max, "max");

	return (0);
}
