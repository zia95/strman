#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <algorithm>
//#include "../../CommandLineParser/CommandLineParser/cmdlnprsr.h"
#include "../../utl/utl/utl.h"
#include "../../utl/utl/utl_cmdln.h"
#include "../../utl/utl/utl_str.h"

using namespace std;



void PrintHelp()
{
	wprintf(L"Usage: strman [InputFile] [Option]\n");
	wprintf(L"Options:\n");
	wprintf(L"\t-v,--verbos                \tTurn ON verbos\n");
	wprintf(L"\t-af,--appfront  <string>   \tAppend string to front\n");
	wprintf(L"\t-ab,--appback   <string>   \tAppend string to back\n");
	wprintf(L"\t-r, --rmv       <string>   \tRemove string from front\n");
	wprintf(L"\t-rc,--rmvchar   <char(s)>  \tRemove char(s)\n");
	wprintf(L"\t-rl,--rmvlower             \tRemove all lower char(s)\n");
	wprintf(L"\t-ru,--rmvupper             \tRemove all upper char(s)\n");
	wprintf(L"\t-rn,--rmvnumber            \tRemove all numbers char(s)\n");
	wprintf(L"\t-rs,--rmvspecial           \tRemove all special char(s)\n");
}



string g_finput;//file
vector<wstring> g_fdata;//file data---read lines
struct OPTIONS
{
	char* data;
	bool verbos;
	enum OPERATIONS
	{
		NONE,
		APP_F,
		APP_B,
		RMV,
		RMV_C,
		RMV_L,
		RMV_U,
		RMV_N,
		RMV_S
	} ope;
} g_opt;





bool remove_front(wstring& line, const wchar_t* data)
{
	if (data)
	{
		size_t len = wcslen(data);
		size_t len2 = line.length();
		if (len == len2 && wcscmp(line.c_str(), data) == 0)
		{
			line.clear();
			return true;
		}
		else if (len < len2 && wcsncmp(line.c_str(), data, len) == 0)
		{
			line.erase(0, len);
			return true;
		}
	}
	return false;
}
bool remove_back(wstring& line, const wchar_t* data)
{
	if (data)
	{
		size_t len = wcslen(data);
		size_t len2 = line.length();
		size_t diff = (len2 - len);
		if (len == len2 && wcscmp(line.c_str(), data) == 0)
		{
			line.clear();
			return true;
		}
		else if (len < len2 && wcsncmp((line.c_str()+ diff), data, len) == 0)
		{
			line.erase(diff, len);
			return true;
		}
	}
	return false;
}


void remove_chars(wstring& line, const wchar_t* data)
{
	line.erase(
		remove_if(line.begin(), line.end(), [&](wchar_t& c) -> bool
			{
				bool rmv = false;
				for (const wchar_t* pc = data; *pc; pc++)
					if (c == *pc)
						rmv = true;
				return rmv;
			}), line.end());
}
void remove_lower(wstring& line)
{
	line.erase(remove_if(line.begin(), line.end(), [&](wchar_t& c) -> bool { return iswlower(c);  }), line.end());
}
void remove_upper(wstring& line)
{
	line.erase(remove_if(line.begin(), line.end(), [&](wchar_t& c) -> bool { return iswupper(c);  }), line.end());
}
void remove_number(wstring& line)
{
	line.erase(remove_if(line.begin(), line.end(), [&](wchar_t& c) -> bool { return iswdigit(c);  }), line.end());
}
void remove_special(wstring& line)
{
	line.erase(remove_if(line.begin(), line.end(), [&](wchar_t& c) -> bool { return !(iswlower(c) || iswupper(c) ||iswdigit(c));  }), line.end());
}


void PrintFile(vector<wstring>& lines, bool print_ln_nums = false)
{
	int lnNum = 1;
	if (g_opt.verbos) wprintf(L"--------------------------------------------------------------\n");
	for (auto& ln : lines)
	{
		if (print_ln_nums)
		{
			size_t siz = lines.size();
			string siz_s = std::to_string(siz);


			wprintf(L"%*d ", siz_s.length(), lnNum);
			lnNum++;
		}
		std::wcout << ln << std::endl;
	}
	if (g_opt.verbos) wprintf(L"--------------------------------------------------------------\n");
}



void ope_run(wstring& line, const wchar_t* data)
{
	switch (g_opt.ope )
	{
		case g_opt.APP_F:
		{
			line = line + data;
			break;
		}
		case g_opt.APP_B:
		{
			line = data + line;
			break;
		}
		case g_opt.RMV:
		{
			strw_remove((pstrw)line.c_str(), strw_end((pstrw)line.c_str()), data);
			//remove_front(line, data);
			break;
		}
		case g_opt.RMV_C:
		{
			remove_chars(line, data);
			break;
		}
		case g_opt.RMV_L:
		{
			remove_lower(line);
			break;
		}
		case g_opt.RMV_U:
		{
			remove_upper(line);
			break;
		}
		case g_opt.RMV_N:
		{
			remove_number(line);
			break;
		}
		case g_opt.RMV_S:
		{
			remove_special(line);
			break;
		}
	}
}
int ope_run()
{
	/*
	wchar_t* __opt_data = NULL;

	if(narrow_to_wide(g_opt.data, &__opt_data) != strlen(g_opt.data))
	{
		return EXIT_FAILURE;
	}
 */
	string __opt_data_s = g_opt.data ? g_opt.data : "";
	wstring __opt_data;
	__opt_data.assign(__opt_data_s.begin(), __opt_data_s.end());

	for (auto& ln : g_fdata)
	{
		ope_run(ln, __opt_data.c_str());
	}

	if (g_opt.verbos)
	{
		wcout << L"Printing operated strings..." << endl;
	}

	PrintFile(g_fdata);

	//delete[] __opt_data;
	return EXIT_SUCCESS;
}

bool ReadWholeFile(const string& filepath, vector<wstring>& lines)
{
	wifstream f(filepath);
	
	if (f.is_open())
	{
		wstring cline;
		while (f.eof() == false)
		{
			getline(f, cline);
			lines.push_back(cline);
			cline.clear();
		}

		f.close();
		return true;
	}
	return false;
}
/*
bool ReadWholeFile(const wchar_t* filepath, vector<wstring>& lines)
{
	char* _filepath;
	bool res = false;
	if(wide_to_narrow(filepath, &_filepath) == wcslen(filepath))
		res = ReadWholeFile(_filepath, lines);
	 
	 delete[] _filepath;

	 return res;
}
 */

/*
bool ParseCommandLine(int argc, wchar_t* argv[])
{
	const wchar_t* sargv[] = 
	{ 
		L"-v", L"--verbos", 
		L"-af", L"--appfront",
		L"-ab", L"--appback",
		L"-rf", L"--rmvfront",
		L"-rb", L"--rmvback",
		L"-rc", L"--rmvchar",
		L"-rl", L"--rmvlower",
		L"-ru", L"--rmvupper",
		L"-rn", L"--rmvnumber",
		L"-rs", L"--rmvspecial"
	};

	PCmdLnParserW_t parser = cmdln_parser_neww(argc, argv, 20, sargv);

	if (parser)
	{
		cmdln_first(parser);

		do
		{
			PKeypairW_t res = cmdln_parsew(parser);
			if (res && !g_finput.empty())
			{
				if (str_equ_insenw(res->key, sargv[0]) || //verbos
					str_equ_insenw(res->key, sargv[1]))
				{
					g_opt.verbos = true;
				}
				else if (
					str_equ_insenw(res->key, sargv[2]) || //app front
					str_equ_insenw(res->key, sargv[3]))
				{
					g_opt.ope = g_opt.APP_F;
					g_opt.data = res->val;
				}
				else if (
					str_equ_insenw(res->key, sargv[4]) || //app back
					str_equ_insenw(res->key, sargv[5]))
				{
					g_opt.ope = g_opt.APP_B;
					g_opt.data = res->val;
				}
				else if (
					str_equ_insenw(res->key, sargv[6]) || //rmv front
					str_equ_insenw(res->key, sargv[7]))
				{
					g_opt.ope = g_opt.RMV_F;
					g_opt.data = res->val;
				}
				else if (
					str_equ_insenw(res->key, sargv[8]) || //rmv back
					str_equ_insenw(res->key, sargv[9]))
				{
					g_opt.ope = g_opt.RMV_B;
					g_opt.data = res->val;
				}
				else if (
					str_equ_insenw(res->key, sargv[10]) ||//rmv chars
					str_equ_insenw(res->key, sargv[11]))
				{
					g_opt.ope = g_opt.RMV;
					g_opt.data = res->val;
				}
				else if (
					str_equ_insenw(res->key, sargv[12]) || //rmv lower
					str_equ_insenw(res->key, sargv[13]))
				{
					g_opt.ope = g_opt.RMV_L;
				}
				else if (
					str_equ_insenw(res->key, sargv[14]) ||//rm upper
					str_equ_insenw(res->key, sargv[15]))
				{
					g_opt.ope = g_opt.RMV_U;
				}
				else if (
					str_equ_insenw(res->key, sargv[16]) ||//rmv number
					str_equ_insenw(res->key, sargv[17]))
				{
					g_opt.ope = g_opt.RMV_N;
				}
				else if (
					str_equ_insenw(res->key, sargv[18]) ||//rmv special
					str_equ_insenw(res->key, sargv[19]))
				{
					g_opt.ope = g_opt.RMV_S;
				}
			}
			else
			{
				if (cmdln_curr_idx(parser) == 1)
				{
					g_finput = cmdln_curr_arg(parser);
				}
			}
		} while (cmdln_next(parser));

		cmdln_parser_free(parser);
	}
	
	return !g_finput.empty() && (g_opt.data || (g_opt.ope == g_opt.RMV_L || g_opt.ope == g_opt.RMV_U || g_opt.ope == g_opt.RMV_N || g_opt.ope == g_opt.RMV_S)) && g_opt.ope;
}
*/

#define STR_EQUI_CMDLN(K, AV, I) (str_equi(K, AV[I]) || str_equi(K, AV[(I+1)]))

bool ParseCommandLine(int argc, char* argv[])
{
	const char* sargv[] = 
	{ 
		"-v", "--verbos",//01
		"-af", "--appfront",//23
		"-ab", "--appback",//45
		"-r", "--rmv",//67
		"-rc", "--rmvchar",//89
		"-rl", "--rmvlower",//10 11
		"-ru", "--rmvupper",//12 13
		"-rn", "--rmvnumber",//14 15
		"-rs", "--rmvspecial"//16 17
	};

	PCmdLnParserA_t parser = cmdln_parser_newa(argc, argv, 20, sargv);

	if (parser)
	{
		cmdln_first(parser);

		do
		{
			PKeypairA_t res = cmdln_parsea(parser);
			if (res && !g_finput.empty())
			{
				if (STR_EQUI_CMDLN(res->key, sargv, 0)) //verbos
				{
					g_opt.verbos = true;
				}
				else if (STR_EQUI_CMDLN(res->key, sargv, 2))//app front
				{
					g_opt.ope = g_opt.APP_F;
					g_opt.data = res->val;
				}
				else if (STR_EQUI_CMDLN(res->key, sargv, 4))//app back
				{
					g_opt.ope = g_opt.APP_B;
					g_opt.data = res->val;
				}
				else if (STR_EQUI_CMDLN(res->key, sargv, 6))//rmv front
				{
					g_opt.ope = g_opt.RMV;
					g_opt.data = res->val;
				}
				else if (STR_EQUI_CMDLN(res->key, sargv, 8))//rmv chars
				{
					g_opt.ope = g_opt.RMV_C;
					g_opt.data = res->val;
				}
				else if (STR_EQUI_CMDLN(res->key, sargv, 10))//rmv lower
				{
					g_opt.ope = g_opt.RMV_L;
				}
				else if (STR_EQUI_CMDLN(res->key, sargv, 12))//rm upper
				{
					g_opt.ope = g_opt.RMV_U;
				}
				else if (STR_EQUI_CMDLN(res->key, sargv, 14))//rmv number
				{
					g_opt.ope = g_opt.RMV_N;
				}
				else if (STR_EQUI_CMDLN(res->key, sargv, 16))//rmv special
				{
					g_opt.ope = g_opt.RMV_S;
				}
			}
			else
			{
				if (cmdln_curr_idx(parser) == 1)
				{
					g_finput = cmdln_curr_arg(parser);
				}
			}
		} while (cmdln_next(parser));

		cmdln_parser_free(parser);
	}
	
	return !g_finput.empty() && (g_opt.data || (g_opt.ope == g_opt.RMV_L || g_opt.ope == g_opt.RMV_U || g_opt.ope == g_opt.RMV_N || g_opt.ope == g_opt.RMV_S)) && g_opt.ope;
}
int main(int argc, char* argv[])
{

	g_opt = { 0 };
	g_finput.clear();
	g_fdata.clear();

	if (ParseCommandLine(argc, argv))
	{
		if (!ReadWholeFile(g_finput, g_fdata) || g_fdata.empty())
		{
			wcerr << L"ERROR: Can't go on because the file doesn't exist or it is empty..." << endl;
			return -2;
		}
		else
		{
			if (g_opt.verbos)
			{
				wcout << L"Printing all file data..." << endl;
				PrintFile(g_fdata);
			}
		}
		return ope_run();
	}
	else
	{
		wcerr << L"ERROR: Command line error..." << endl;
		PrintHelp();
		return -1;
	}
}
