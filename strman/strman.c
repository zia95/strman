
#include <stdio.h>
#include <stdlib.h>


#include "utllib.h"

#include "cmndline.h"
#include "ope.h"
#include "opts.h"
#include "../../utl/utl/utl_llist.h"
#include "../../utl/utl/utl_str.h"
#include "../../utl/utl/utl_str_type.h"

#define EXIT_FAILURE_OPT -1
#define EXIT_FAILURE_FILE_STREAM -2


int num_of_digits_in_int(int _int)
{
	char mystr[128];
	snprintf(mystr, (sizeof(mystr) / sizeof(mystr[0])), "%d", _int);
	
	//str_tostr_decimal(mystr, (sizeof(mystr) / sizeof(mystr[0])), _int);
	return str_len(mystr);
}

void print_file(PLList lst, bool verbos)
{
	
	char* ln = NULL;
	size_t count = llist_count(lst);

	int ln_no_max_dgts = 0;
	
	if (verbos)
	{
		ln_no_max_dgts = num_of_digits_in_int(count);
	}
	if (verbos)
		printf("--------------------------------------------------------------\n");

	for (size_t i = 0; i < count; i++)
	{
		ln = llist_get(lst, i)->pdata;
		if (verbos)
		{
			printf("%*d ", ln_no_max_dgts, (i+1));
		}
		printf("%s\n", ln);
	}

	if (verbos)
		printf("--------------------------------------------------------------\n");
}


bool read_file_stream(FILE* file, PLList lst)
{
	char* line = NULL;
	while ((line = file_readlinea(file)) != NULL)
	{
		llist_add(lst, line);
	}
	return llist_count(lst);
}

bool read_file(POpts popt, PLList lst)
{
	if (popt->file)
	{
		FILE* f = file_opena(popt->file, "r");
		if (f)
		{
			bool result = read_file_stream(f, lst);
			file_close(f);
			return result;
		}
		
	}
	return read_file_stream(stdin, lst);
}

void llist_iter_cb_elm_free(PLList pl, size_t idx, PLLElement pelm)
{
	str_free(pelm->pdata);
}

int main(int argc, char* argv[])
{
	POpts popt = parse_command_line(argc, argv);

	if (!opt_check(popt))
	{
		fprintf(stderr, "Failed to parse options...\n");
		print_help();
		return EXIT_FAILURE_OPT;
	}
	
	PLList plst = llist_new();


	if (!read_file(popt, plst))
	{
		fprintf(stderr, "Failed to parse options...\n");
		return EXIT_FAILURE_FILE_STREAM;
	}

	if (popt->verbos)
	{
		printf("Printing file data...\n");
		print_file(plst, popt->verbos);
	}

	int res = ope_run_list(popt, plst);

	if (res == EXIT_SUCCESS)
	{
		if (popt->verbos)
		{
			printf("Printing operated strings...\n");
		}

		print_file(plst, popt->verbos);
	}

	llist_iter(plst, llist_iter_cb_elm_free);
	llist_free(plst);

	mem_free(popt);


	return res;
}
