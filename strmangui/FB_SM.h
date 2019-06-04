///////////////////////////////////////////////////////////////////////////
// C++ code generated with wxFormBuilder (version Oct 26 2018)
// http://www.wxformbuilder.org/
//
// PLEASE DO *NOT* EDIT THIS FILE!
///////////////////////////////////////////////////////////////////////////

#pragma once

#include <wx/artprov.h>
#include <wx/xrc/xmlres.h>
#include <wx/string.h>
#include <wx/bitmap.h>
#include <wx/image.h>
#include <wx/icon.h>
#include <wx/menu.h>
#include <wx/gdicmn.h>
#include <wx/font.h>
#include <wx/colour.h>
#include <wx/settings.h>
#include <wx/textctrl.h>
#include <wx/sizer.h>
#include <wx/frame.h>
#include <wx/stattext.h>
#include <wx/button.h>
#include <wx/dialog.h>

///////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
/// Class _frmMain
///////////////////////////////////////////////////////////////////////////////
class _frmMain : public wxFrame
{
	DECLARE_EVENT_TABLE()
	private:

		// Private event handlers
		void _wxFB_m_mnuOpenOnMenuSelection( wxCommandEvent& event ){ m_mnuOpenOnMenuSelection( event ); }
		void _wxFB_m_mnuSaveOnMenuSelection( wxCommandEvent& event ){ m_mnuSaveOnMenuSelection( event ); }
		void _wxFB_m_mnuSaveAsOnMenuSelection( wxCommandEvent& event ){ m_mnuSaveAsOnMenuSelection( event ); }
		void _wxFB_m_mnuExitOnMenuSelection( wxCommandEvent& event ){ m_mnuExitOnMenuSelection( event ); }
		void _wxFB_m_mnuRStringsOnMenuSelection( wxCommandEvent& event ){ m_mnuRStringsOnMenuSelection( event ); }
		void _wxFB_m_mnuRCharsOnMenuSelection( wxCommandEvent& event ){ m_mnuRCharsOnMenuSelection( event ); }
		void _wxFB_m_mnuRLowerOnMenuSelection( wxCommandEvent& event ){ m_mnuRLowerOnMenuSelection( event ); }
		void _wxFB_m_mnuRUpperOnMenuSelection( wxCommandEvent& event ){ m_mnuRUpperOnMenuSelection( event ); }
		void _wxFB_m_mnuRNumbersOnMenuSelection( wxCommandEvent& event ){ m_mnuRNumbersOnMenuSelection( event ); }
		void _wxFB_m_mnuRSpecialOnMenuSelection( wxCommandEvent& event ){ m_mnuRSpecialOnMenuSelection( event ); }
		void _wxFB_m_mnuASFrontOnMenuSelection( wxCommandEvent& event ){ m_mnuASFrontOnMenuSelection( event ); }
		void _wxFB_m_mnuASBackOnMenuSelection( wxCommandEvent& event ){ m_mnuASBackOnMenuSelection( event ); }
		void _wxFB_m_mnuHowToOnMenuSelection( wxCommandEvent& event ){ m_mnuHowToOnMenuSelection( event ); }
		void _wxFB_m_mnuAboutOnMenuSelection( wxCommandEvent& event ){ m_mnuAboutOnMenuSelection( event ); }


	protected:
		enum
		{
			ID_MNUOPEN = 1000,
			ID_MNUSAVE,
			ID_MNUSAVEAS,
			ID_MNUEXIT,
			ID_MNURSTRINGS,
			ID_MNURCHARS,
			ID_MNURLOWER,
			ID_MNURUPPER,
			ID_MNURNUMBERS,
			ID_MNURSPECIAL,
			ID_MNUASFRONT,
			ID_MNUASBACK,
			ID_MNUHOWTO,
			ID_MNUABOUT
		};

		wxMenuItem* m_mnuOpen;
		wxMenuItem* m_mnuSave;
		wxMenuItem* m_mnuSaveAs;
		wxMenuItem* m_mnuExit;
		wxMenuItem* m_mnuRStrings;
		wxMenuItem* m_mnuRChars;
		wxMenuItem* m_mnuRLower;
		wxMenuItem* m_mnuRUpper;
		wxMenuItem* m_mnuRNumbers;
		wxMenuItem* m_mnuRSpecial;
		wxMenuItem* m_mnuASFront;
		wxMenuItem* m_mnuASBack;
		wxMenuItem* m_mnuHowTo;
		wxMenuItem* m_mnuAbout;
		wxTextCtrl* m_txtStrings;

		// Virtual event handlers, overide them in your derived class
		virtual void m_mnuOpenOnMenuSelection( wxCommandEvent& event ) { event.Skip(); }
		virtual void m_mnuSaveOnMenuSelection( wxCommandEvent& event ) { event.Skip(); }
		virtual void m_mnuSaveAsOnMenuSelection( wxCommandEvent& event ) { event.Skip(); }
		virtual void m_mnuExitOnMenuSelection( wxCommandEvent& event ) { event.Skip(); }
		virtual void m_mnuRStringsOnMenuSelection( wxCommandEvent& event ) { event.Skip(); }
		virtual void m_mnuRCharsOnMenuSelection( wxCommandEvent& event ) { event.Skip(); }
		virtual void m_mnuRLowerOnMenuSelection( wxCommandEvent& event ) { event.Skip(); }
		virtual void m_mnuRUpperOnMenuSelection( wxCommandEvent& event ) { event.Skip(); }
		virtual void m_mnuRNumbersOnMenuSelection( wxCommandEvent& event ) { event.Skip(); }
		virtual void m_mnuRSpecialOnMenuSelection( wxCommandEvent& event ) { event.Skip(); }
		virtual void m_mnuASFrontOnMenuSelection( wxCommandEvent& event ) { event.Skip(); }
		virtual void m_mnuASBackOnMenuSelection( wxCommandEvent& event ) { event.Skip(); }
		virtual void m_mnuHowToOnMenuSelection( wxCommandEvent& event ) { event.Skip(); }
		virtual void m_mnuAboutOnMenuSelection( wxCommandEvent& event ) { event.Skip(); }


	public:

		_frmMain( wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = wxT("String Manipulator"), const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize( 500,300 ), long style = wxDEFAULT_FRAME_STYLE|wxTAB_TRAVERSAL );

		~_frmMain();

};

///////////////////////////////////////////////////////////////////////////////
/// Class _dlgAbout
///////////////////////////////////////////////////////////////////////////////
class _dlgAbout : public wxDialog
{
	private:

	protected:
		wxStaticText* m_lblAboutText;
		wxStdDialogButtonSizer* m_dlgBtns;
		wxButton* m_dlgBtnsOK;

	public:

		_dlgAbout( wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = wxT("About..."), const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize( -1,-1 ), long style = wxDEFAULT_DIALOG_STYLE );
		~_dlgAbout();

};

///////////////////////////////////////////////////////////////////////////////
/// Class _dlgSInput
///////////////////////////////////////////////////////////////////////////////
class _dlgSInput : public wxDialog
{
	private:

	protected:
		wxStaticText* m_lblInput;
		wxTextCtrl* m_txtInput;
		wxStdDialogButtonSizer* m_dlgBtns;
		wxButton* m_dlgBtnsOK;

	public:

		_dlgSInput( wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = wxT("SInput Dialog"), const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize( -1,-1 ), long style = wxDEFAULT_DIALOG_STYLE|wxRESIZE_BORDER );
		~_dlgSInput();

};

