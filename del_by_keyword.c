/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   del_by_keyword.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iiliuk <iiliuk@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/01 12:03:09 by iiliuk            #+#    #+#             */
/*   Updated: 2017/05/04 18:26:20 by iiliuk           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_db.h"

static void	del_by_keyword_2(FILE *fp, char **argv, int found, char *keyword)
{
	if (!found)
		no_record_found_message(fp, 0, keyword);
	else if (found > 1)
	{
		printf(MAG "There are %d records found by the ", found);
		printf("\"%s\" keyword\n", keyword);
		printf("Now it's best to choose record to delete by number\n" NC);
		del_record_by_num(fp, argv);
	}
}

void		del_by_keyword(FILE *fp, char **argv)
{
	PersonalInfo info, *pInfo = &info;
	char buf[MAXLINE];
	int got_it, record_nm, found_records, match;
	char keyword[MAX_BLOCK];

	record_nm = 1, got_it = 0, found_records = 0, match = 0;
	printf(MAG "Enter keyword to find a record you want to delete: ");
	scanf("%s" NC, keyword);
	while(fgets(buf, MAXLINE, fp))
	{
		get_record(buf, pInfo);
		got_it = search(pInfo, keyword, record_nm++);
		if (got_it)
		{
			if (found_records == 0)
				match = got_it;
			found_records++;
		}
	}
	del_by_keyword_2(fp, argv, found_records, keyword);
	if (found_records == 1)
		del_entry(fp, argv, match);
}

void		del_entry(FILE *fp, char **argv, int line_number)
{
	FILE *fp2;
	char buf[MAXLINE];
	PersonalInfo info, *pInfo = &info;
	int nb_lines;

    nb_lines = 0;
	rewind(fp);
	fp2 = fopen("replica.c", "w");
	while(fgets(buf, MAXLINE, fp))
	{
		nb_lines++;
		if (nb_lines != line_number)
			fputs(buf, fp2);
		else
			get_record(buf, pInfo);
	}
	fclose(fp2);
	fclose(fp);
	remove(argv[optind]);
	rename("replica.c", argv[optind]);
	printf(MAG "Record number %d successfully deleted:\n" NC, line_number);
	print_record(pInfo, 0);
}
