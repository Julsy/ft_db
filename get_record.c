/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_record.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iiliuk <iiliuk@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/04 14:38:42 by iiliuk            #+#    #+#             */
/*   Updated: 2017/05/04 18:39:13 by iiliuk           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_db.h"

/* get_str: Fetch one block of information separated by tabs */
static void	get_block(char *line, char *cs, const char delimiter)
{
	char buf[MAX_BLOCK];
	static int i = 0;
 
	while(line[i] != '\0')
	{
		if(line[i] == delimiter)
		{
			i++;
			break;
		}
		else if(line[i] == '\n')
		{
			i = 0;
			break;
		}
		*cs++ = line[i++];
	}
	*cs = '\0';
}

/* get_record: Set each text piece into structure counterparts */
void		get_record(char *line, PersonalInfo *pInfo)
{
	get_block(line, pInfo->name, TAB);
	get_block(line, pInfo->lastname, TAB);
	get_block(line, pInfo->age, TAB);
	get_block(line, pInfo->workplace, TAB);
}
