/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iiliuk <iiliuk@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/01 13:31:23 by iiliuk            #+#    #+#             */
/*   Updated: 2017/05/04 18:39:26 by iiliuk           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_db.h"

void 	print_record(PersonalInfo *pInfo, int counter)
{
	if (counter != 0)
		printf(GREEN "Record No.: %d\n" NC, counter);
	printf("Firstname: %s\n", pInfo->name);
	printf("Lastname: %s\n", pInfo->lastname);
	printf("Age: %s\n", pInfo->age);
	printf("Workplace: %s\n\n", pInfo->workplace);
}

void	print_database(FILE *fp)
{
	int j;
	char buf[MAXLINE];
	PersonalInfo info, *pInfo = &info;

	j = 0;
	rewind(fp);
	while(fgets(buf, MAXLINE, fp))
	{
		j++;
		get_record(buf, pInfo);
		print_record(pInfo, j);
	}
	printf(GREEN "Database consists of %d record(s) total.\n\n" NC, j);
}

void	print_usage(const char *prog_name)
{
	fprintf(stderr, RED
		"Usage: %s [-option] [file_name.db]\n"
		BLUE"--help			-h	print this information\n"
		"--append		-a	add records or create new file if not present\n"
		"--search		-s	find records in specified file\n"
		"--delete		-d	delete record by number in a file\n"
		"--del_keyword		-k	delete record by keyword\n"
		"--edit			-n	edit record by number in specified file\n"
		"--edit_keyword		-e	edit record by keyword file\n"
		"--print all		-p	print all records in specified file\n" NC,
		prog_name);
	exit(-1);
}

void	no_record_found_message(FILE *fp, int record_nm, char *key)
{
	if (record_nm)
		printf(RED "\nThere's no record No %d in database\n", record_nm);
	else if (key)
		printf(RED "\nThere's no record found by the \"%s\" keyword\n", key);
	else
		printf(RED "\nThere's no record matching your request\n");
	printf("Print database to see existing records");
	printf("(./ft_db -p [file_name.db])\n" NC);
	fclose(fp);
	exit(1);
}
