/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debbug.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bduron <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/07 09:21:04 by bduron            #+#    #+#             */
/*   Updated: 2017/06/09 15:01:16 by bduron           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ls.h"

void printav(char **av)
{
	while (*av)
		printf("%s\n", *av++);
}

void ft_print_lst(t_list *head)
{
	while (head)
	{
		printf("%s ", ((t_data *)head->content)->path);
		head = head->next;	
	}		
	printf("\n");
}
