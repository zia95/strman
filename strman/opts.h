#ifndef OPTS
#define OPTS



#include <stdbool.h>

#include "../../utl/utl/utl_file.h"
#include "../../utl/utl/utl_mem.h"
#include "../../utl/utl/utl_str_type.h"

typedef enum OPES
{
	NONE,
	APP_F,
	APP_B,
	RMV,
	RMV_C,
	RMV_L,
	RMV_U,
	RMV_D,
	RMV_S,
	RMV_N
} Operations;

typedef struct RUN_OPTIONS
{
	char* file;
	char* ignore_lines_raw;//ignored lines un-parsed
	bool verbos;
	Operations ope;
	char* param;
} Opts, * POpts;

#define opts_check(opt) (opt->param || (opt->ope == RMV_L || opt->ope == RMV_U || opt->ope == RMV_D || opt->ope == RMV_S)) && opt->ope
#define opts_check_file(opt) file_exista(opt->file)
#define opts_new() mem_alloc_obj_zero(Opts)

inline int get_ints_from_str(char* buff, const char* sep, int* ints)
{
	char* pch;
	int num_filled = 0;
	int num;
	bool successful;


	pch = strtok(buff, sep);


	while (pch != NULL)
	{
		successful = false;
		num = str_try_toint(pch, 10, &successful);
		if (successful)
		{
			ints[num_filled] = num;
			num_filled++;
		}

		pch = strtok(NULL, ",");
	}
	return num_filled;
}

#endif // !OPTS