/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   edit_by_num.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iiliuk <iiliuk@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/01 18:09:38 by iiliuk            #+#    #+#             */
/*   Updated: 2017/05/02 18:14:40 by iiliuk           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_db.h"

void 	edit_record_by_num(FILE *fp, char **argv)
{
	PersonalInfo info, *pInfo = &info;
	char buf[MAXLINE];
	unsigned int record_nm;
	int nb_lines, j, got_it;

	j = 1;
    nb_lines = 0, got_it = 0;
	printf(MAG "Enter record number to be edited: ");
	scanf("%d" NC, &record_nm);
	rewind(fp);
	while(fgets(buf, MAXLINE, fp))
	{
		if (j == record_nm)
		{
			got_it = 1;
			get_record(buf, pInfo);
			print_record(pInfo, j);
			break;
		}
		j++;
	}
	if (!got_it)
	{
		printf(RED "\nThere's no record with this number in database\n"); 
		printf("Print database to see existing records (./ft_db -p [file_name.db]\n" NC);
		fclose(fp);
		exit(1);
	}
	else
		edit_field_loop(pInfo, fp, argv, record_nm);
}
	
void	edit_field_loop(PersonalInfo *pInfo, FILE *fp, char **argv, int record_nm)
{
	int field_nm;
	char line[MAXLINE];
	char answer[5];

	while(1)
	{
		printf(MAG "Enter field number to be edited: [1/2/3/4] ");
		scanf("%d" NC, &field_nm);
		getchar();
		edit_field(pInfo, field_nm);
		write_to_line(pInfo, line);
		rewrite_file(fp, argv, record_nm, line);
		printf(MAG "Do you want to continue editing this record? [yes/no] ");
		scanf("%s" NC, answer);
		if (strcmp(answer, "no") == 0 || strcmp(answer, "n") == 0)
			break;
	}
	fclose(fp);
}
