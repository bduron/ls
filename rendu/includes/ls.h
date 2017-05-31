/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ls.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bduron <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/29 19:18:26 by bduron            #+#    #+#             */
/*   Updated: 2017/05/29 20:49:54 by bduron           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LS_H
# define LS_H

# include <dirent.h>
# include <stdio.h>
# include <string.h>
# include <errno.h>
# include <sys/stat.h>
# include <stdlib.h>
# include <sys/types.h>
# include <pwd.h>
//# include <uuid/uuid.h>
# include <grp.h>
# include <unistd.h>

# define FT_NONE		(1 << 0) // -f
# define FT_DEFAULT		(1 << 1) // nothing, lexicographycally sorted
# define FT_HIDDEN		(1 << 2) // -a
# define FT_FOLLOWLNK	(1 << 3) // ? 
# define FT_TSORT		(1 << 4) // -t
# define FT_REVERSE		(1 << 5) // -r
# define FT_RECURSIVE	(1 << 6) // -R
# define FT_LIST		(1 << 7) // -l

# define ERR_WRONGOPT	-1


typedef struct	s_env
{
//	t_list		*files;
	int			opts;
	int			nopts;
	char 		**target;

		

}				t_env;



#endif
