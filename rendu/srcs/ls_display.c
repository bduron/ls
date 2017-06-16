/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ls_display.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bduron <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/13 14:11:25 by bduron            #+#    #+#             */
/*   Updated: 2017/06/14 12:45:09 by bduron           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ls.h"

void ls_display_flush(t_list *ents, t_list *nextdirs, int opts)
{
	t_data			*data;
	t_fmt			fmt;
	
	init_fmt(&fmt, ents, opts);
	while (ents)
	{
		data = ents->content;
		
		if (*(data->path) == '.' && !(opts & FT_DOT))
		{
			ents = ents->next;
			continue;
		}
		if (opts & FT_LIST)
			ls_display_list(data, fmt);	
		else
			ft_printf("%s\n", data->path);
		ents = ents->next;
	}
	if (nextdirs)	
   		ft_printf("\n");
}

void ls_display(t_list *ents, char *dirpath, int opts)
{
	t_data			*data;
	static int		firstdir;	
	t_fmt			fmt;

	if (firstdir++ || opts & FT_DIRNAME)
  		ft_printf("%s:\n", dirpath);
	init_fmt(&fmt, ents, opts);
  	if (opts & FT_LIST)
		ft_printf("total %ld\n", fmt.total);
	while (ents)
	{
		data = ents->content;
		if (*(data->dirent->d_name) == '.' && !(opts & FT_DOT))
		{
			ents = ents->next;
			continue;
		}
		if (opts & FT_LIST)
			ls_display_list(data, fmt);	
		else
			ft_printf("%s\n", data->dirent->d_name);
		ents = ents->next;
	}
}
