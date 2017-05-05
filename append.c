/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   append.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iiliuk <iiliuk@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/01 12:46:42 by iiliuk            #+#    #+#             */
/*   Updated: 2017/05/04 18:41:23 by iiliuk           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_db.h"

int g_flag = 0;

/* fetch: Store input from user */
void		fetch(char *buffer)
{
	int c, i;

	i = 0;
	while ((c = getchar()) != '\n')
	{
		if (i >= MAX_BLOCK)
		{
			printf(BLUE "Exceeded maximum allowed lenght\n" NC);
			break ;
		}
		buffer[i++] = c;
	}
	buffer[i] = '\0';
}


static int	digit_check(char *str)
{
	int i;

	i = 0;
	while (str[i] != '\0')
	{
		if (isdigit(str[i]))
			i++;
		else
		{
			printf(RED "Error: only digits are allowed in this field\n" NC);
			return (0);
		}
	}
	return (1);
}

static void	age_loop(PersonalInfo *pInfo)
{
	char tmp[MAX_BLOCK];

	while (1)
	{
		printf(CYAN "Age: " BLUE);
		fetch((tmp));
		if (digit_check(tmp))
		{
			strcpy(pInfo->age, tmp);
			break ;
		}
		else
			printf(CYAN "Please, try again\n" BLUE);
	}
}

void		append(PersonalInfo *pInfo, FILE *fp)
{
	char line[MAXLINE];
	

	if (g_flag)
	{
		getchar();
		g_flag = 0;
	}
	printf(CYAN "Firstname: " BLUE);
	fetch(pInfo->name);
	printf(CYAN "Lastname: " BLUE);
	fetch(pInfo->lastname);
	age_loop(pInfo);
	printf(CYAN "Work: " BLUE);
	fetch(pInfo->workplace);
	printf("" NC);
	g_flag = 1;
	write_to_line(pInfo, line);
	fputs(line, fp);
}

void		create_entry(FILE *fp)
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
