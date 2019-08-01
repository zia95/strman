#ifndef CMNDLINE
#define CMNDLINE



#include "opts.h"

#define CMDLN_NC 0 //nocase for command line parser
#include "../../utl/utl/utl.h"
#include "../../utl/utl/utl_cmdln.h"
#include "../../utl/utl/utl_str.h"
#include "../../utl/utl/utl_file.h"


#define OPTIONS_COUNT 22

const char* cmdln_options[OPTIONS_COUNT] =
{
	"-v", "--verbos",//01
	"-i", "--ignore",//23
	"-af", "--appfront",//45
	"-ab", "--appback",//67
	"-r", "--rmv",//89
	"-rc", "--rmvchar",//10 11
	"-rl", "--rmvlower",//12 13
	"-ru", "--rmvupper",//14 15
	"-rd", "--rmvdigit",//16 17
	"-rs", "--rmvspecial",//18 19
	"-rn", "--rmvchnum",//20 21
};
#define PARAM_NONE ""
//format: opt1, opt2, param, descp
#define PRINT_HELP_PARAM(ARG1, ARG2, PARAM, DESCP)	printf("%3s,%10s    %10s\t\t%s\n", ARG1, ARG2, PARAM, DESCP);
//#define PRINT_HELP_NOPARAM(ARG1, ARG2, DESCP)		printf("%3s,%10s\t\t\t\t%s\n", ARG1, ARG2, DESCP);
#define PRINT_HELP_NOPARAM(ARG1, ARG2, DESCP)		PRINT_HELP_PARAM(ARG1, ARG2, PARAM_NONE, DESCP);
void print_help()
{
	printf("Usage: strman <InputFile> [Option]\n");
	printf("Options:\n");
	
	PRINT_HELP_NOPARAM(cmdln_options[0], cmdln_options[1], "Turn on verbos");
	PRINT_HELP_PARAM(cmdln_options[2], cmdln_options[3], "<lineno(s)>", "Ignore line(s) by number. seprated by ','");
	PRINT_HELP_PARAM(cmdln_options[4], cmdln_options[5], "<string>", "Append string to front");
	PRINT_HELP_PARAM(cmdln_options[6], cmdln_options[7], "<string>", "Append string to back");

	PRINT_HELP_PARAM(cmdln_options[8], cmdln_options[9], "<string>", "Remove string from front");

	PRINT_HELP_PARAM(cmdln_options[10], cmdln_options[11], "<char(s)>", "Remove char(s)");

	PRINT_HELP_NOPARAM(cmdln_options[12], cmdln_options[13], "Remove all lower char(s)");
	PRINT_HELP_NOPARAM(cmdln_options[14], cmdln_options[15], "Remove all upper char(s)");
	PRINT_HELP_NOPARAM(cmdln_options[16], cmdln_options[17], "Remove all numbers char(s)");
	PRINT_HELP_NOPARAM(cmdln_options[18], cmdln_options[19], "Remove all special char(s)");

	PRINT_HELP_PARAM(cmdln_options[20], cmdln_options[21], "<+num|-num>", "Remove number of chars (positive number: remove from front, negitive number: remove from back)");
}

POpts parse_command_line(int argc, char* argv[])
{
	if (argc <= 1)
		return false;

	PCmdLnParserA_t parser = cmdln_parser_newa(argc, argv, OPTIONS_COUNT, cmdln_options);

	POpts opts = mem_alloc_obj_zero(Opts);


	if (parser)
	{
		cmdln_first(parser);

		do
		{
			if (cmdln_curr_idx(parser) == 0)
				continue;

			if (cmdln_curr_idx(parser) == 1)
			{
				opts->file = cmdln_curr_arg(parser);
				if (file_exista(opts->file))
					continue;
				opts->file = NULL;
			}

			PKeypairA_t res = cmdln_parsea(parser);
			if (res)
			{
				switch (res->kidx)
				{
				case 0://verbos
				case 1:
					opts->verbos = true;
					break;
				case 2://ignore
				case 3:
					opts->ignore_lines_raw = res->val;
					break;
				case 4://app front
				case 5:
					opts->ope = APP_F;
					opts->param = res->val;
					break;
				case 6://app back
				case 7:
					opts->ope = APP_B;
					opts->param = res->val;
					break;
				case 8://rmv
				case 9:
					opts->ope = RMV;
					opts->param = res->val;
					break;
				case 10://rmv chars
				case 11:
					opts->ope = RMV_C;
					opts->param = res->val;
					break;
				case 12://rmv lower
				case 13:
					opts->ope = RMV_L;
					break;
				case 14://rmv upper
				case 15:
					opts->ope = RMV_U;
					break;
				case 16://rmv digit
				case 17:
					opts->ope = RMV_D;
					break;
				case 18://rmv special
				case 19:
					opts->ope = RMV_S;
					break;
				case 20://rmv number of chars
				case 21:
					opts->ope = RMV_N;
					opts->param = res->val;
					break;
				}
			}

		} while (cmdln_next(parser));

		cmdln_parser_free(parser);
	}

	return opts;
}


//void print_help()
//{
//	const char* opt_1, * opt_2, * param, * descp;
//	opt_1 = opt_2 = param = descp = NULL;
//
//	printf("Usage: strman [InputFile] [Option]\n");
//	printf("Options:\n");
//	for (int i = 0; i < OPTIONS_COUNT; (i += 2))
//	{
//		opt_1 = cmdln_options[i];
//		opt_2 = cmdln_options[(i + 1)];
//		param = cmdln_options_params[(i + 1)];
//		descp = cmdln_options_description[(i + 1)];
//
//		printf("%s, %s ", opt_1, opt_2);
//		if (param && param != "")
//			printf("%s\n", param);
//		else
//			printf("\n");
//		printf("\t%s\n", descp);
//	}
//}


#endif // !CMNDLINE