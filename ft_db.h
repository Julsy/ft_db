/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_db.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgutniko <lgutniko@student.42.us.org>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/27 12:06:04 by lgutniko          #+#    #+#             */
/*   Updated: 2017/05/03 14:01:03 by iiliuk           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_DB_H
# define FT_DB_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <getopt.h>
#include <errno.h>
#include <ctype.h>

#define TAB '\t'
#define MAX_BLOCK 20
#define MAXLINE 80
#define TRUE 1
#define FALSE 0

# define MAG "\033[0;35m"
# define RED "\033[0;31m"
# define GREEN "\033[1;32m"
# define CYAN "\033[0;36m"
# define BLUE "\033[0;34m"
# define NC "\033[0m"

struct _PersonalInfo
{
	int	rec_num;
	char name[20];
	char lastname[20];
	char iq[20];
	char workplace[30];
};

typedef struct _PersonalInfo PersonalInfo;

void get_options(int argc, char **argv);
void get_record(char *line, PersonalInfo *pInfo);

void find_record(FILE *fp);

void del_record_by_num(FILE *fp, char **argv);
int get_db_size(FILE *fp);

void create_entry(FILE *fp);
void append(PersonalInfo *pInfo, FILE *fp);

void fetch(char *buffer);
int	search(PersonalInfo *pInfo, char *search_criteria, int counter);

void del_entry(FILE *fp, char **argv, int line_number);
int del_search(char *line, char *search_criteria);
void del_by_keyword(FILE *fp, char **argv);

void print_database(FILE *fp);
void print_record(PersonalInfo *pInfo, int counter);
void print_usage(const char *prog_name);

void edit_record(char *buf, char *srch_term, FILE *fp, char **argv);
void edit_field(PersonalInfo *pInfo, int nm);
void write_to_line(PersonalInfo *pInfo, char *line);
void rewrite_file(FILE *fp, char **argv, int line_number, char *line);

void edit_by_keyword(FILE *fp, char **argv);
void edit_record_by_num(FILE *fp, char **argv);
void edit_field_loop(PersonalInfo *pInfo, FILE *fp, char **argv, int record_nm);

#endif
