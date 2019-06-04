



#pragma comment(lib, "winmm.lib")
#pragma comment(lib, "comctl32.lib")
#pragma comment(lib, "rpcrt4.lib")
#pragma comment(lib, "wsock32.lib")
#pragma comment(lib, "oleacc.lib")
#pragma comment(lib, "odbc32.lib")
#pragma comment(lib, "kernel32.lib")
#pragma comment(lib, "user32.lib")
#pragma comment(lib, "gdi32.lib")
#pragma comment(lib, "winspool.lib")
#pragma comment(lib, "comdlg32.lib")
#pragma comment(lib, "advapi32.lib")
#pragma comment(lib, "shell32.lib")
#pragma comment(lib, "ole32.lib")
#pragma comment(lib, "oleaut32.lib")
#pragma comment(lib, "uuid.lib")
#pragma comment(lib, "odbccp32.lib")



#include <wx/wx.h>
#include <wx/wfstream.h>
#include "strman.h"
#include "FB_SM.h"

class dlgSInput : public _dlgSInput
{
public:
	dlgSInput(wxWindow* parent) : _dlgSInput(parent, wxID_ANY, L"Input string")
	{
		wxSize siz = this->GetSize();

		this->SetMinSize(siz);

		siz.SetWidth(600);

		this->SetMaxSize(siz);

		this->m_lblInput->SetLabelText("String:");
	}

	inline void GetInputText(wstring& str)
	{
		str = this->m_txtInput->GetLineText(0).ToStdWstring();
	}
};

class frmMain : public _frmMain
{
private:
	wxString m_file;
	wxString m_title;
public:
	frmMain() : _frmMain(nullptr)
	{
		m_title = this->GetTitle();
	}
	~frmMain()
	{

	}

	bool input_get_string(wstring& inpstr)
	{
		dlgSInput* inp = new dlgSInput(this);
		if (inp->ShowModal() == wxID_OK)
		{
			inp->GetInputText(inpstr);

			return true;
		}
		return false;
	}


	bool save_file(wxString& file)
	{
		wxFileDialog saveFileDialog(this, "Save XYZ file", "", "", "All files (*.*)|*.*", wxFD_SAVE | wxFD_OVERWRITE_PROMPT);
		if (saveFileDialog.ShowModal() == wxID_CANCEL)
			return false;     // the user changed idea...

		// save the current contents in the file;
		// this can be done with e.g. wxWidgets output streams:
		wxFileOutputStream output_stream(saveFileDialog.GetPath());
		if (!output_stream.IsOk())
		{
			wxLogError("Cannot save current contents in file '%s'.", saveFileDialog.GetPath());
			return false;
		}

		return true;
	}


	void m_mnuOpenOnMenuSelection(wxCommandEvent& event)
	{
		wxFileDialog openFileDialog(this, "Open text file", "", "",	"All files (*.*)|*.*", wxFD_OPEN | wxFD_FILE_MUST_EXIST);
		if (openFileDialog.ShowModal() == wxID_CANCEL)
			return;     // the user changed idea...

		// proceed loading the file chosen by the user;
		// this can be done with e.g. wxWidgets input streams:
		m_file = openFileDialog.GetPath();
		wxFileInputStream input_stream(m_file);
		if (!input_stream.IsOk())
		{
			wxLogError("Cannot open file '%s'.", openFileDialog.GetPath());
			return;
		}

		wxString s;
		s.reserve(input_stream.GetSize());
		while (input_stream.CanRead() && input_stream.Eof() == false)
		{
			s += input_stream.GetC();
			
		}

		this->m_txtStrings->Clear();
		this->m_txtStrings->WriteText(s);

		this->SetTitle(m_title + " - " + m_file);
	}
	void m_mnuSaveOnMenuSelection(wxCommandEvent& event)
	{

	}
	void m_mnuSaveAsOnMenuSelection(wxCommandEvent& event)
	{
		
	}
	void m_mnuExitOnMenuSelection(wxCommandEvent& event) 
	{
		//exit app
		this->Close();
	}
	void m_mnuRStringsOnMenuSelection(wxCommandEvent& event)
	{
		wstring inp;
		if (input_get_string(inp))
			str_ope_perform(str_remove_string, this->m_txtStrings, inp.c_str());
	}
	void m_mnuRCharsOnMenuSelection(wxCommandEvent& event)
	{
		wstring inp;
		if (input_get_string(inp))
			str_ope_perform(str_remove_char, this->m_txtStrings, inp.c_str());
	}

	void m_mnuASFrontOnMenuSelection(wxCommandEvent& event)
	{
		wstring inp;
		if (input_get_string(inp))
			str_ope_perform(str_append_front, this->m_txtStrings, inp.c_str());
	}
	void m_mnuASBackOnMenuSelection(wxCommandEvent& event)
	{
		wstring inp;
		if (input_get_string(inp))
			str_ope_perform(str_append_back, this->m_txtStrings, inp.c_str());
	}

	void m_mnuRLowerOnMenuSelection(wxCommandEvent& event)
	{
		str_ope_perform(str_remove_lower, this->m_txtStrings);
	}
	void m_mnuRUpperOnMenuSelection(wxCommandEvent& event)
	{
		str_ope_perform(str_remove_upper, this->m_txtStrings);
	}
	void m_mnuRNumbersOnMenuSelection(wxCommandEvent& event)
	{
		str_ope_perform(str_remove_number, this->m_txtStrings);
	}
	void m_mnuRSpecialOnMenuSelection(wxCommandEvent& event)
	{
		str_ope_perform(str_remove_special, this->m_txtStrings);
	}
	

	void m_mnuAboutOnMenuSelection(wxCommandEvent& event)
	{
		_dlgAbout* d = new _dlgAbout(this);
		d->ShowModal();
		delete d;
	}

	void m_mnuHowToOnMenuSelection(wxCommandEvent& event)
	{
		wxMessageBox("1) In text box add one string one line.\n2) In edit menu there are tools.\n3) Results will displayed in the same textbox (make sure you backup strings first).",
			"How to...", wxICON_INFORMATION | wxOK, this);
	}
};







class APP : public wxApp
{
public:

	bool OnInit()
	{
		frmMain* f = new frmMain();
		return f->Show();
	}

};



IMPLEMENT_APP(APP)