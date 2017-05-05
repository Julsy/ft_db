/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   edit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iiliuk <iiliuk@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/01 16:52:19 by iiliuk            #+#    #+#             */
/*   Updated: 2017/05/04 18:39:57 by iiliuk           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_db.h"

/* 	flag[0] = record number; */
/* 	flag[1] = got it - when a keyword record is found */
/* 	flag[2] = total found records */
/* 	flag[3] = record number if it's the only one in the file */


static void	edit_by_keyword_2(FILE *fp, char **argv, char *key, int found_records, int found, PersonalInfo *cInfo)
{
	if (!found_records)
		no_record_found_message(fp, 0, key);
	else if (found_records > 1)
	{
		printf(MAG "There are %d records found by the ", found_records);
		printf("\"%s\" keyword\n", key);
		printf("Now it's best to choose record to edit by number\n" NC);
		edit_record_by_num(fp, argv);
	}
	else
		edit_field_loop(cInfo, fp, argv, found);
}

void		edit_by_keyword(FILE *fp, char **argv)
{
	PersonalInfo info, *pInfo = &info;
	PersonalInfo copy_info, *cInfo = &copy_info;
	char buf[MAXLINE];
	char keyword[MAX_BLOCK];
	int flag[4];

	flag[0] = 1;
	flag[1] = 0;
	flag[2] = 0;
	flag[3] = 0;
	printf(MAG "Enter keyword to find a record you want to edit: ");
	scanf("%s" NC, keyword);
	while (fgets(buf, MAXLINE, fp))
	{
		get_record(buf, pInfo);
		flag[1] = search(pInfo, keyword, flag[0]++);
		if (flag[1])
		{
			if (flag[2] == 0)
			{
				flag[3] = flag[1];
				*cInfo = *pInfo;
			}
			flag[2]++;
		}
	}
	edit_by_keyword_2(fp, argv, keyword, flag[2], flag[3], cInfo);
}

static void	edit_field_2(PersonalInfo *pInfo, int nm)
{
	char new_entry[MAX_BLOCK];

	if (nm == 3)
	{
		printf(CYAN "Enter new age: " BLUE);
		fetch(new_entry);
		printf("\n" NC);
		strcpy(pInfo->age, new_entry);
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
}

void		edit_field(PersonalInfo *pInfo, int nm)
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
	else
		edit_field_2(pInfo, nm);
	printf(BLUE "Entry successfully edited!\n\n" NC);
	print_record(pInfo, 0);
}
