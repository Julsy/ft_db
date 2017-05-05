/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   search.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iiliuk <iiliuk@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/01 12:46:22 by iiliuk            #+#    #+#             */
/*   Updated: 2017/05/04 18:39:38 by iiliuk           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_db.h"

static char *to_lower(char *str)
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

int			search(PersonalInfo *pInfo, char *srch_term, int counter)
{
	if (strcmp(to_lower(pInfo->name), to_lower(srch_term)) == 0)
	{
		print_record(pInfo, counter);
		return (counter);
	}
	else if (strcmp(to_lower(pInfo->lastname), to_lower(srch_term)) == 0)
	{
		print_record(pInfo, counter);
		return (counter);
	}
	else if (strcmp(pInfo->age, srch_term) == 0)
	{
		print_record(pInfo, counter);
		return (counter);
	}
	else if (strcmp(to_lower(pInfo->workplace), to_lower(srch_term)) == 0)
	{
		print_record(pInfo, counter);
		return (counter);
	}
	return (0);
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
	while (fgets(buf, MAXLINE, fp))
	{
		get_record(buf, pInfo);
		{
			ret_val = search(pInfo, srch_term, counter++);
			if (ret_val)
				found_records++;
		}
	}
	if (!found_records)
		no_record_found_message(fp, 0, srch_term);
}
