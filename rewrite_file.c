/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rewrite_file.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iiliuk <iiliuk@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/04 14:35:07 by iiliuk            #+#    #+#             */
/*   Updated: 2017/05/04 18:39:32 by iiliuk           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_db.h"

void	write_to_line(PersonalInfo *pInfo, char *line)
{
	strcpy(line, pInfo->name);
	strcat(line, "\t");
	strcat(line, pInfo->lastname);
	strcat(line, "\t");
	strcat(line, pInfo->age);
	strcat(line, "\t");
	strcat(line, pInfo->workplace);
	strcat(line, "\n\0");
}

void	rewrite_file(FILE *fp, char **argv, int line_number, char *line)
{
	FILE *fp2;
	char buf[MAXLINE];
	int nb_lines;

	nb_lines = 0;
	rewind(fp);
	fp2 = fopen("replica.c", "w");
	while (fgets(buf, MAXLINE, fp))
	{
		nb_lines++;
		if (nb_lines != line_number)
			fputs(buf, fp2);
		else
			fputs(line, fp2);
	}
	fclose(fp2);
	remove(argv[optind]);
	rename("replica.c", argv[optind]);
}
