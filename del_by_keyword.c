/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   del_by_keyword.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iiliuk <iiliuk@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/01 12:03:09 by iiliuk            #+#    #+#             */
/*   Updated: 2017/05/02 16:14:09 by iiliuk           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_db.h"

void	del_by_keyword(FILE *fp, char **argv)
{
	PersonalInfo info, *pInfo = &info;
	char buf[MAXLINE];
	int got_it, record_nm, found_records, found;
	char keyword[MAX_BLOCK];

	record_nm = 1, got_it = 0, found_records = 0, found = 0;
	printf(MAG "Enter keyword to find a record you want to delete: ");
	scanf("%s" NC, keyword);
	while(fgets(buf, MAXLINE, fp))
	{
		get_record(buf, pInfo);
		got_it = search(pInfo, keyword, record_nm++);
		if (got_it)
		{
			if (found_records == 0)
				found = got_it;
			found_records++;
		}
	}
	if (!found_records)
	{
		printf(RED "\nThere's no record matching your request\n"); 
		printf("Print database to see existing records (./ft_db -p [file_name.db]\n" NC);
		fclose(fp);
		exit(1);
	}
	else if (found_records > 1)
	{
		printf(MAG "There are %d records found by the \"%s\" keyword\n", found_records, keyword);
		printf(MAG "Now it's best to choose record to delete by number\n");
		del_record_by_num(fp, argv);
	}
	else
		del_entry(fp, argv, found);
}

void del_entry(FILE *fp, char **argv, int line_number)
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
