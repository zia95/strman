#ifndef OPE
#define OPE

#include "../../utl/utl/utl_str.h"
#include "../../utl/utl/utl_str_type.h"
#include "../../utl/utl/utl_type.h"
#include "../../utl/utl/utl_llist.h"

#include "opts.h"


#define remove_chars(line, data) str_remove_chs(line, str_end(line), data)


#define remove_lower(line) str_remove_iter(line, str_end(line), type_charislower)
#define remove_upper(line) str_remove_iter(line, str_end(line), type_charisupper)
#define remove_number(line) str_remove_iter(line, str_end(line), type_charisdigit)

inline int isspecial(int _C)
{
	return type_charisspecial(_C);
}


#define remove_special(line) str_remove_iter(line, str_end(line), isspecial)

//------------------------------------------------------------------------



inline char* ope_app(char* fst, char* snd)//append string
{
	pstr s = str_new_zero(str_len(fst) + str_len(snd) + 1);
	str_cpy(s, fst);
	str_cat(s, snd);
	return s;
}
inline char* ope_n(char* line, char* param)// subtract/remove num of chars from front or bottom
{
	bool successful = false;
	int num = str_try_toint(param, 10, &successful);
	if (successful && num != 0)
	{
		int len = str_len(line);
		int absnum = abs(num);
		if (absnum < len)
		{
			if (num > 0)
			{
				str_remove_range(line, str_end(line), line, (line+ num));
			}
			else
			{
				str_remove_range(line, str_end(line), (str_end(line) + num), str_end(line));
			}
		}
	}
	
	return line;
}
char* ope_run(Operations ope, char* param, char* line)
{
	switch (ope)
	{
		case APP_F:
		{
			return ope_app(line, param);
			break;
		}
		case APP_B:
		{
			return ope_app(param, line);
			break;
		}
		case RMV:
		{
			str_remove(line, str_end(line), param, SF_SUB_STR);
			return NULL;
			break;
		}
		case RMV_C:
		{
			remove_chars(line, param);
			return NULL;
			break;
		}
		case RMV_L:
		{
			remove_lower(line);
			return NULL;
			break;
		}
		case RMV_U:
		{
			remove_upper(line);
			return NULL;
			break;
		}
		case RMV_D:
		{
			remove_number(line);
			return NULL;
			break;
		}
		case RMV_S:
		{
			remove_special(line);
			return NULL;
			break;
		}
		case RMV_N:
		{
			ope_n(line, param);
			return NULL;
			break;
		}
	}
	return NULL;
}

bool is_ignored_line(int* lines, int linesc, int idx)
{
	idx++;
	for (int i = 0; i < linesc; i++)
	{
		if (lines[i] == idx)
			return true;
	}
	return false;
}
int ope_run_list(POpts ope, PLList lst)
{
	int* ign_ln = NULL;
	int ign_ln_c = 0;

	if (ope->ignore_lines_raw)
	{
		int ign_ln_siz = str_len(ope->ignore_lines_raw);
		ign_ln = mem_calloc(ign_ln_siz, sizeof(int));
		ign_ln_c = get_ints_from_str(ope->ignore_lines_raw, ",", ign_ln);
	}



	PLLElement elm = NULL;
	for (int i = 0; i < llist_count(lst); i++)
	{
		if (ope->ignore_lines_raw && is_ignored_line(ign_ln, ign_ln_c, i))
			continue;


		elm = llist_get(lst, i);
		if (elm)
		{
			char* processed = ope_run(ope->ope, ope->param, elm->pdata);
			if (processed)//means string was reallocated, and previous one needs to be freed and....
			{
				str_free(elm->pdata);
				elm->pdata = processed;
			}
		}
	}

	//cleanup....
	mem_free(ign_ln);

	return EXIT_SUCCESS;
}


#endif // !OPE