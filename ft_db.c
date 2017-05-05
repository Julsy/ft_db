/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_db.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iiliuk <iiliuk@student.42.us.org>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/28 13:52:21 by iiliuk            #+#    #+#             */
/*   Updated: 2017/05/04 18:26:28 by iiliuk           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_db.h"

const char *const shrt_opt = "ahsdkpen";
const struct option lng_opt[] = {
		{"help", 0, NULL, 'h'},
		{"append", 0, NULL, 'a'},
		{"search", 0, NULL, 's'},
		{"delete", 0, NULL, 'd'},
		{"del_keyword", 0, NULL, 'k'},
		{"edit_keyword", 0, NULL, 'e'},
		{"edit", 0, NULL, 'c'},
		{"print all", 0, NULL, 'p'},
		{NULL, 0, NULL, 0}
	};

static void		get_options(int argc, char **argv, t_opts *opts)
{
	int next_opt;

	while ((next_opt = getopt_long(argc, argv, shrt_opt, lng_opt, NULL)) != -1)
	{
		if (next_opt == 'a')
			opts->mode = "a";
		else if (next_opt == 'h')
			print_usage(argv[0]);
		else if (next_opt =='s')
			opts->srch = 1;
		else if (next_opt == 'd')
			opts->del = 1;
		else if (next_opt == 'k')
			opts->key = 1;
		else if (next_opt == 'p')
			opts->print = 1;
		else if (next_opt == 'e')
			opts->edit = 1;
		else if (next_opt == 'n')
			opts->num = 1;
		else if (next_opt == '?')
			exit(-1);
		break ;
	}
}

static t_opts	*init_struct(t_opts *opts)
{
	opts = (t_opts *)malloc(sizeof(t_opts));
	opts->mode = "r+";
	opts->srch = 0;
	opts->key = 0;
	opts->del = 0;
	opts->edit = 0;
	opts->print = 0;
	opts->num = 0;
	return (opts);
}

static void		do_ft_db(FILE *fp, char **argv, t_opts *opts)
{
	if(strcmp(opts->mode, "a") == 0)
		create_entry(fp);
	else if (opts->srch == TRUE)
		find_record(fp);
	else if (opts->print == TRUE)
		print_database(fp);
	else if (opts->key == TRUE)
		del_by_keyword(fp, argv);
	else if (opts->del == TRUE)
		del_record_by_num(fp, argv);
	else if (opts->edit == TRUE)
		edit_by_keyword(fp, argv);
	else if (opts->num == TRUE)
		edit_record_by_num(fp, argv);
	else
		print_usage(argv[0]);
}

int				main(int argc, char **argv)
{
	FILE *fp;
	t_opts *opts;

	if(argc < 3)
		print_usage(argv[0]);
	opts = init_struct(opts);
	get_options(argc, argv, opts);
	if (strstr(argv[optind], ".db") == NULL)
	{
		printf(RED "\"%s\" isn't a valid file: ", argv[optind]);
		printf("please use files with '.db' extension\n" NC);
		exit(-1);
	}
	if((fp = fopen(argv[optind], opts->mode)) == NULL)
	{
		fprintf(stderr, BLUE "%s: Error: Cannot open file.\n" NC, argv[optind]);
		exit(-1);
	}
	do_ft_db(fp, argv, opts);
	fclose(fp);
	return (0);
}
