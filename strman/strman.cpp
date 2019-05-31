#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <algorithm>
#include "../../CommandLineParser/CommandLineParser/cmdlnprsr.h"

using namespace std;



wstring g_finput;
vector<wstring> g_fdata;
struct OPTIONS
{
	wchar_t* data;
	bool verbos;
	enum OPERATIONS
	{
		NONE,
		APP_F,
		APP_B,
		RMV_F,
		RMV_B,
		RMV,
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
	if (g_opt.verbos) printf("--------------------------------------------------------------\n");
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
	if (g_opt.verbos) printf("--------------------------------------------------------------\n");
}



void ope_run(wstring& line, wchar_t* data)
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
		case g_opt.RMV_F:
		{
			remove_front(line, data);
			break;
		}
		case g_opt.RMV_B:
		{
			remove_back(line, data);
			break;
		}
		case g_opt.RMV:
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
	for (auto& ln : g_fdata)
	{
		ope_run(ln, g_opt.data);
	}

	if (g_opt.verbos)
	{
		wcout << L"Printing operated strings..." << endl;
	}

	PrintFile(g_fdata);

	return EXIT_SUCCESS;
}
bool ReadWholeFile(const wstring& filepath, vector<wstring>& lines)
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

void PrintHelp()
{
	printf("Usage: strman [InputFile] [Option]\n");
	printf("Options:\n");
	printf("\t-v,--verbos                \tTurn ON verbos\n");
	printf("\t-af,--appfront  <string>   \tAppend string to front\n");
	printf("\t-ab,--appback   <string>   \tAppend string to back\n");
	printf("\t-rf,--rmvfront  <string>   \tRemove string from front\n");
	printf("\t-rb,--rmvback   <string>   \tRemove string from back\n");
	printf("\t-rc,--rmvchar   <char(s)>  \tRemove char(s)\n");
	printf("\t-rl,--rmvlower             \tRemove all lower char(s)\n");
	printf("\t-ru,--rmvupper             \tRemove all upper char(s)\n");
	printf("\t-rn,--rmvnumber            \tRemove all numbers char(s)\n");
	printf("\t-rs,--rmvspecial           \tRemove all special char(s)\n");
}


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

#ifndef NDEBUG
int wmain()
{
	int argc = 5;
	const wchar_t* argv[] = {L"strman.exe", L"C:/Users/ziaud/Desktop/test/str.txt", L"-v", L"-rc", L" \t#"};
#else
int wmain(int argc, wchar_t* argv[])
{
#endif





	g_opt = { 0 };
	g_finput.clear();
	g_fdata.clear();

	if (ParseCommandLine(argc, (wchar_t**)argv))
	{
		ReadWholeFile(g_finput, g_fdata);
		if (g_fdata.empty())
		{
			cerr << "ERROR: Can't go on because the file is empty..." << endl;
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
		cerr << "ERROR: Command line error..." << endl;
		PrintHelp();
		return -1;
	}
}