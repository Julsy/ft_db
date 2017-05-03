/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_db.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iiliuk <iiliuk@student.42.us.org>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/28 13:52:21 by iiliuk            #+#    #+#             */
/*   Updated: 2017/05/03 11:19:40 by iiliuk           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_db.h"

int srch = 0, key = 0, del = 0, edit = 0, print = 0, num = 0;
char *mode = "r+";

void get_options(int argc, char **argv)
{
	const char *const shrt_optns = "ahsdkpen";
	const struct option lng_optns[] = {
		{"help", 0, NULL, 'h'},
		{"append", 0, NULL, 'a'},
		{"search", 0, NULL, 's'},
		{"delete", 0, NULL, 'd'},
		{"del_keyword", 0, NULL, 'k'},
		{"edit_keyword", 0, NULL, 'e'},
		{"edit", 0, NULL, 'c'},
		{"print all", 0, NULL, 'p'},
		{NULL, 0, NULL, 0}	/* required */
	};
	int next_option;

	do
	{
		next_option = getopt_long(argc, argv, shrt_optns, lng_optns, NULL);
		switch(next_option)
		{
			case 'a':
				mode = "a";
				break;
			case 'h':
				print_usage(argv[0]);
				break;
			case 's':
				srch = 1;
				break;
			case 'd':
				del = 1;
				break;
			case 'k':
				key = 1;
				break;
			case 'p':
				print = 1;
				break;
			case 'e':
				edit = 1;
				break;
			case 'n':
				num = 1;
				break;
			case '?':
				exit(-1);
				break;
			case -1:
				break;
		}
	} while(next_option != -1);
}

int main(int argc, char **argv)
{
	FILE *fp;

	if(argc < 3)
		print_usage(argv[0]);
	get_options(argc, argv);
	if (strstr(argv[optind], ".db") == NULL)
	{
		printf(RED "\"%s\" isn't a valid file: please use files with '.db' extension\n" NC, argv[optind]);
		exit(-1);
	}
	if((fp = fopen(argv[optind], mode)) == NULL)
	{
		fprintf(stderr, BLUE "%s: Error: Cannot open file.\n" NC, argv[optind]);
		exit(-1);
	}
	if(*mode == 'a')
		create_entry(fp);
	else if (srch == TRUE)
		find_record(fp);
	else if (print == TRUE)
		print_database(fp);
	else if (key == TRUE)
		del_by_keyword(fp, argv);
	else if (del == TRUE)
		del_record_by_num(fp, argv);
	else if (edit == TRUE)
		edit_by_keyword(fp, argv);
	else if (num == TRUE)
		edit_record_by_num(fp, argv);
	else
		print_usage(argv[0]);
	fclose(fp);
	return 0;
}
