#pragma once

#include<iostream>
#include<algorithm>
using namespace std;

void str_remove_string(wstring& line, const wchar_t* data)
{
	size_t pos = line.find(data);
	if (pos != line.npos)
	{
		line.erase(pos, wcslen(data));
	}
}


void str_remove_char(wstring& line, const wchar_t* data)
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



void str_append_front(wstring& line, const wchar_t* data)
{
	line = data + line;
}
void str_append_back(wstring & line, const wchar_t* data)
{
	line = line + data;
}



void str_remove_lower(wstring & line)
{
	line.erase(remove_if(line.begin(), line.end(), [&](wchar_t& c) -> bool { return iswlower(c);  }), line.end());
}
void str_remove_upper(wstring & line)
{
	line.erase(remove_if(line.begin(), line.end(), [&](wchar_t& c) -> bool { return iswupper(c);  }), line.end());
}
void str_remove_number(wstring & line)
{
	line.erase(remove_if(line.begin(), line.end(), [&](wchar_t& c) -> bool { return iswdigit(c);  }), line.end());
}
void str_remove_special(wstring & line)
{
	line.erase(remove_if(line.begin(), line.end(), [&](wchar_t& c) -> bool { return !(iswlower(c) || iswupper(c) || iswdigit(c));  }), line.end());
}



typedef void (*OPE_PERF_D_FUNC)(wstring&, const wchar_t*);
typedef void (*OPE_PERF_FUNC)(wstring&);


template<typename T>
void str_ope_perform(T func, vector<wstring>& lines, const wchar_t* data = nullptr)
{
	for (wstring& line : lines)
		if (data)
		{
			for (wstring& line : lines)
				((OPE_PERF_D_FUNC)func)(line, data);
		}
		else
		{
			for (wstring& line : lines)
				((OPE_PERF_FUNC)func)(line);
		}
}



#ifdef _WX_WX_H_

void txt_ctrl_to_vector_str(wxTextCtrl* txtctl, vector<wstring>& lines)
{
	int nLines = txtctl->GetNumberOfLines();
	if (nLines <= 0)
		return;

	lines.reserve(nLines);
	for (int i = 0; i < nLines; i++)
	{
		lines.push_back(txtctl->GetLineText(i).ToStdWstring());
	}
}

void txt_ctrl_set_lines(wxTextCtrl* txtctl, vector<wstring>& lines)
{
	txtctl->Clear();
	for (auto& line : lines)
	{
		line += '\n';
		txtctl->AppendText(line);
	}
}

template<typename T>
void str_ope_perform(T func, wxTextCtrl* txtctl, const wchar_t* data = nullptr)
{
	vector<wstring> lines;

	txt_ctrl_to_vector_str(txtctl, lines);

	str_ope_perform(func, lines, data);

	txt_ctrl_set_lines(txtctl, lines);
}
#endif