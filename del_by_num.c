/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   del_by_num.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iiliuk <iiliuk@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/01 12:01:56 by iiliuk            #+#    #+#             */
/*   Updated: 2017/05/04 15:32:08 by iiliuk           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_db.h"

static void	del_record_by_num_2(FILE *fp, char **argv, int line_to_del)
{
	FILE *fp2;
	int nb_lines;
	char buf[MAXLINE];
	PersonalInfo info, *pInfo = &info;

	nb_lines = 0;
	fp2 = fopen("replica.c", "w");
	while (fgets(buf, MAXLINE, fp))
	{
		nb_lines++;
		if (nb_lines != line_to_del)
			fputs(buf, fp2);
		else
			get_record(buf, pInfo);
	}
	fclose(fp2);
	fclose(fp);
	remove(argv[optind]);
	rename("replica.c", argv[optind]);
	printf(BLUE "\nRecord number %d successfully deleted:\n" NC, line_to_del);
	print_record(pInfo, 0);
}

void 		del_record_by_num(FILE *fp, char **argv)
{
	int db_size;
	unsigned int line_to_del;

	rewind(fp);
	printf(MAG "Enter record number to be deleted: ");
	scanf("%d" NC, &line_to_del);
	db_size = get_db_size(fp);
	if (line_to_del > db_size)
		no_record_found_message(fp, line_to_del, NULL);
	del_record_by_num_2(fp, argv, line_to_del);
}

int			get_db_size(FILE *fp)
{
	int j;
	char buf[MAXLINE];

	j = 0;
	rewind(fp);
	while (fgets(buf, MAXLINE, fp))
		j++;
	rewind(fp);
	return (j);
}
