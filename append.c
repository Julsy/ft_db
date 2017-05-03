/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   append.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iiliuk <iiliuk@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/01 12:46:42 by iiliuk            #+#    #+#             */
/*   Updated: 2017/05/02 17:46:29 by iiliuk           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_db.h"

int flag = 0;

/* fetch: Store input from user */
void	fetch(char *buffer)
{
	int c, i;
	int max = MAX_BLOCK;

	i = 0;
	while((c = getchar()) != '\n')
	{
		if(i >= max)
		{
			printf(BLUE "Exceeded maximum allowed lenght\n" NC);
			break;
		}
		buffer[i++] = c;
	}
	buffer[i] = '\0';
}

void	append(PersonalInfo *pInfo, FILE *fp)
{
	char	line[MAXLINE];

	if (flag)
	{
		getchar();
		flag = 0;
	}
	printf(CYAN "Firstname: " BLUE);
	fetch(pInfo->name);
	printf(CYAN "Lastname: " BLUE);
	fetch(pInfo->lastname);
	printf(CYAN "IQ: " BLUE);
	fetch(pInfo->iq);
	printf(CYAN "Work: " BLUE);
	fetch(pInfo->workplace);
	printf("" NC);
	flag = 1;
	write_to_line(pInfo, line);
	fputs(line, fp);
}

void	create_entry(FILE *fp)
{
	char answer[5];
	PersonalInfo info, *pInfo = &info;

	while (1)
	{
		append(pInfo, fp);
		printf(MAG "\nEntry successfully appended!\n\n" NC);
		printf(CYAN "Add more entries [yes/no]? ");
		scanf("%s" NC, answer);
		if (strcmp(answer, "no") == 0 || strcmp(answer, "n") == 0)
			break ;
	}
}
