/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   edit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iiliuk <iiliuk@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/01 16:52:19 by iiliuk            #+#    #+#             */
/*   Updated: 2017/05/02 18:10:53 by iiliuk           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_db.h"

void	edit_by_keyword(FILE *fp, char **argv)
{
	PersonalInfo info, *pInfo = &info;
	PersonalInfo copy_info, *cInfo = &copy_info;
	char buf[MAXLINE];
	int got_it, record_nm, found_records, found;
	char keyword[MAX_BLOCK];

	record_nm = 1, got_it = 0, found_records = 0, found = 0;
	printf(MAG "Enter keyword to find a record you want to edit: ");
	scanf("%s" NC, keyword);
	while(fgets(buf, MAXLINE, fp))
	{
		get_record(buf, pInfo);
		got_it = search(pInfo, keyword, record_nm);
		record_nm++;
		if (got_it)
		{
			if (found_records == 0)
			{
				found = got_it;
				*cInfo = *pInfo;
			}
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
	else if (found_records == 1)
		edit_field_loop(cInfo, fp, argv, found);
	else
	{
		printf(MAG "There are %d records found by the \"%s\" keyword\n", found_records, keyword);
		printf(MAG "Now it's best to choose record to edit by number\n");
		edit_record_by_num(fp, argv);
	}
}

void	edit_field(PersonalInfo *pInfo, int nm)
{
	char new_entry[MAX_BLOCK];

	if (nm == 1)
	{
		printf(CYAN "Enter new firstname: " BLUE);
		fetch(new_entry);
		printf("\n" NC);
		strcpy(pInfo->name, new_entry);
	}
	else if (nm == 2)
	{
		printf(CYAN "Enter new lastname: " BLUE);
		fetch(new_entry);
		printf("\n" NC);
		strcpy(pInfo->lastname, new_entry);
	}
	else if (nm == 3)
	{
		printf(CYAN "Enter new IQ: " BLUE);
		fetch(new_entry);
		printf("\n" NC);
		strcpy(pInfo->iq, new_entry);
	}
	else if (nm == 4)
	{
		printf(CYAN "Enter new workplace: " BLUE);
		fetch(new_entry);
		printf("\n" NC);
		strcpy(pInfo->workplace, new_entry);
	}
	else
	{
		printf(BLUE "Please, choose between 4 fields: [1/2/3/4]\n\n" NC);
		return ;
	}
	printf(BLUE "Entry successfully edited!\n\n" NC);
	print_record(pInfo, 0);
}

void	write_to_line(PersonalInfo *pInfo, char *line)
{
	strcpy(line, pInfo->name);
	strcat(line, "\t");
	strcat(line, pInfo->lastname);
	strcat(line, "\t");
	strcat(line, pInfo->iq);
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
	while(fgets(buf, MAXLINE, fp))
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
