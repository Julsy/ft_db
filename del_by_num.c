/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   del_by_num.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iiliuk <iiliuk@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/01 12:01:56 by iiliuk            #+#    #+#             */
/*   Updated: 2017/05/02 16:17:54 by iiliuk           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_db.h"

void 	del_record_by_num(FILE *fp, char **argv)
{
	FILE *fp2;
	PersonalInfo info, *pInfo = &info;
	char buf[MAXLINE];
	unsigned int delete_line;
	int nb_lines;
	int db_size;

    nb_lines = 0;
	rewind(fp);
	printf(MAG "Enter record number to be deleted: ");
	scanf("%d" NC, &delete_line);
	db_size = get_db_size(fp);
	if (delete_line > db_size)
	{
		printf(RED "\nThere's no record matching your request\n"); 
		printf("Print database to see existing records (./ft_db -p [file_name.db]\n" NC);
		fclose(fp);
		exit(1);
	}
	fp2 = fopen("replica.c", "w");
	while(fgets(buf, MAXLINE, fp))
	{
		nb_lines++;
		if (nb_lines != delete_line)
			fputs(buf, fp2);
		else
			get_record(buf, pInfo);
	}
	fclose(fp2);
	fclose(fp);
	remove(argv[optind]);
	rename("replica.c", argv[optind]);
	printf(BLUE "\nRecord number %d successfully deleted:\n" NC, delete_line);
	print_record(pInfo, 0);
}

int		get_db_size(FILE *fp)
{
	int j;
	char buf[MAXLINE];

	j = 0;
	rewind(fp);
	while(fgets(buf, MAXLINE, fp))
		j++;
	rewind(fp);
	return j;
}