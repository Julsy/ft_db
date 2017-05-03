/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   search.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iiliuk <iiliuk@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/01 12:46:22 by iiliuk            #+#    #+#             */
/*   Updated: 2017/05/03 11:36:04 by iiliuk           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_db.h"

static char *loop_tolower(char *str)
{
	int i;
	char *copy;

	i = 0;
	copy = strdup(str);
	while (copy[i])
	{
		copy[i] = tolower(copy[i]);
		i++;
	}
	return (copy);
}

int			search(PersonalInfo *pInfo, char *search_criteria, int counter)
{
	if (strcmp(loop_tolower(pInfo->name), loop_tolower(search_criteria)) == 0)
	{
		print_record(pInfo, counter);
		return counter;
	}
	else if (strcmp(loop_tolower(pInfo->lastname), loop_tolower(search_criteria)) == 0)
	{
		print_record(pInfo, counter);
		return counter;
	}
	else if (strcmp(loop_tolower(pInfo->iq), loop_tolower(search_criteria)) == 0)
	{
		print_record(pInfo, counter);
		return counter;
	}
	else if (strcmp(loop_tolower(pInfo->workplace), loop_tolower(search_criteria)) == 0)
	{
		print_record(pInfo, counter);
		return counter;
	}
	return 0;
}

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
	get_block(line, pInfo->iq, TAB);
	get_block(line, pInfo->workplace, TAB);
}

void		find_record(FILE *fp)
{
	PersonalInfo info, *pInfo = &info;
	char buf[MAXLINE];
	char srch_term[MAX_BLOCK];
	int ret_val = 0, found_records = 0, counter = 1;

	printf(MAG "Enter the keyword to search for: " BLUE);
	fetch(srch_term);
	printf("\n" NC);
	while(fgets(buf, MAXLINE, fp))
	{
		get_record(buf, pInfo);
		{
			ret_val = search(pInfo, srch_term, counter++);
			if(ret_val)
				found_records++;
		}
	}
	if(!found_records)
	{
		printf(BLUE "There's no record matching your request\n" NC);
		printf("Print database to see existing records (./ft_db -p [file_name.db]\n" NC);
	}
}
