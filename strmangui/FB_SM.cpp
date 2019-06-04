///////////////////////////////////////////////////////////////////////////
// C++ code generated with wxFormBuilder (version Oct 26 2018)
// http://www.wxformbuilder.org/
//
// PLEASE DO *NOT* EDIT THIS FILE!
///////////////////////////////////////////////////////////////////////////

#include "FB_SM.h"

///////////////////////////////////////////////////////////////////////////

BEGIN_EVENT_TABLE( _frmMain, wxFrame )
	EVT_MENU( ID_MNUOPEN, _frmMain::_wxFB_m_mnuOpenOnMenuSelection )
	EVT_MENU( ID_MNUSAVE, _frmMain::_wxFB_m_mnuSaveOnMenuSelection )
	EVT_MENU( ID_MNUSAVEAS, _frmMain::_wxFB_m_mnuSaveAsOnMenuSelection )
	EVT_MENU( ID_MNUEXIT, _frmMain::_wxFB_m_mnuExitOnMenuSelection )
	EVT_MENU( ID_MNURSTRINGS, _frmMain::_wxFB_m_mnuRStringsOnMenuSelection )
	EVT_MENU( ID_MNURCHARS, _frmMain::_wxFB_m_mnuRCharsOnMenuSelection )
	EVT_MENU( ID_MNURLOWER, _frmMain::_wxFB_m_mnuRLowerOnMenuSelection )
	EVT_MENU( ID_MNURUPPER, _frmMain::_wxFB_m_mnuRUpperOnMenuSelection )
	EVT_MENU( ID_MNURNUMBERS, _frmMain::_wxFB_m_mnuRNumbersOnMenuSelection )
	EVT_MENU( ID_MNURSPECIAL, _frmMain::_wxFB_m_mnuRSpecialOnMenuSelection )
	EVT_MENU( ID_MNUASFRONT, _frmMain::_wxFB_m_mnuASFrontOnMenuSelection )
	EVT_MENU( ID_MNUASBACK, _frmMain::_wxFB_m_mnuASBackOnMenuSelection )
	EVT_MENU( ID_MNUHOWTO, _frmMain::_wxFB_m_mnuHowToOnMenuSelection )
	EVT_MENU( ID_MNUABOUT, _frmMain::_wxFB_m_mnuAboutOnMenuSelection )
END_EVENT_TABLE()

_frmMain::_frmMain( wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style ) : wxFrame( parent, id, title, pos, size, style )
{
	this->SetSizeHints( wxDefaultSize, wxDefaultSize );

	wxMenuBar* m_mbMain;
	m_mbMain = new wxMenuBar( 0 );
	wxMenu* m_mnuFile;
	m_mnuFile = new wxMenu();
	m_mnuOpen = new wxMenuItem( m_mnuFile, ID_MNUOPEN, wxString( wxT("Open") ) , wxEmptyString, wxITEM_NORMAL );
	m_mnuFile->Append( m_mnuOpen );

	m_mnuSave = new wxMenuItem( m_mnuFile, ID_MNUSAVE, wxString( wxT("Save") ) , wxEmptyString, wxITEM_NORMAL );
	m_mnuFile->Append( m_mnuSave );

	m_mnuSaveAs = new wxMenuItem( m_mnuFile, ID_MNUSAVEAS, wxString( wxT("Save as...") ) , wxEmptyString, wxITEM_NORMAL );
	m_mnuFile->Append( m_mnuSaveAs );

	m_mnuFile->AppendSeparator();

	m_mnuExit = new wxMenuItem( m_mnuFile, ID_MNUEXIT, wxString( wxT("Exit") ) , wxEmptyString, wxITEM_NORMAL );
	m_mnuFile->Append( m_mnuExit );

	m_mbMain->Append( m_mnuFile, wxT("File") );

	wxMenu* m_mnuEdit;
	m_mnuEdit = new wxMenu();
	wxMenu* m_mnuRemove;
	m_mnuRemove = new wxMenu();
	wxMenuItem* m_mnuRemoveItem = new wxMenuItem( m_mnuEdit, wxID_ANY, wxT("Remove..."), wxEmptyString, wxITEM_NORMAL, m_mnuRemove );
	m_mnuRStrings = new wxMenuItem( m_mnuRemove, ID_MNURSTRINGS, wxString( wxT("String...") ) , wxEmptyString, wxITEM_NORMAL );
	m_mnuRemove->Append( m_mnuRStrings );

	m_mnuRChars = new wxMenuItem( m_mnuRemove, ID_MNURCHARS, wxString( wxT("Chars...") ) , wxEmptyString, wxITEM_NORMAL );
	m_mnuRemove->Append( m_mnuRChars );

	m_mnuRLower = new wxMenuItem( m_mnuRemove, ID_MNURLOWER, wxString( wxT("All lower") ) , wxEmptyString, wxITEM_NORMAL );
	m_mnuRemove->Append( m_mnuRLower );

	m_mnuRUpper = new wxMenuItem( m_mnuRemove, ID_MNURUPPER, wxString( wxT("All upper") ) , wxEmptyString, wxITEM_NORMAL );
	m_mnuRemove->Append( m_mnuRUpper );

	m_mnuRNumbers = new wxMenuItem( m_mnuRemove, ID_MNURNUMBERS, wxString( wxT("All numbers") ) , wxEmptyString, wxITEM_NORMAL );
	m_mnuRemove->Append( m_mnuRNumbers );

	m_mnuRSpecial = new wxMenuItem( m_mnuRemove, ID_MNURSPECIAL, wxString( wxT("All special") ) , wxEmptyString, wxITEM_NORMAL );
	m_mnuRemove->Append( m_mnuRSpecial );

	m_mnuEdit->Append( m_mnuRemoveItem );

	wxMenu* m_mnuAppend;
	m_mnuAppend = new wxMenu();
	wxMenuItem* m_mnuAppendItem = new wxMenuItem( m_mnuEdit, wxID_ANY, wxT("Append"), wxEmptyString, wxITEM_NORMAL, m_mnuAppend );
	m_mnuASFront = new wxMenuItem( m_mnuAppend, ID_MNUASFRONT, wxString( wxT("String front") ) , wxEmptyString, wxITEM_NORMAL );
	m_mnuAppend->Append( m_mnuASFront );

	m_mnuASBack = new wxMenuItem( m_mnuAppend, ID_MNUASBACK, wxString( wxT("String back") ) , wxEmptyString, wxITEM_NORMAL );
	m_mnuAppend->Append( m_mnuASBack );

	m_mnuEdit->Append( m_mnuAppendItem );

	m_mbMain->Append( m_mnuEdit, wxT("Edit") );

	wxMenu* m_mnuHelp;
	m_mnuHelp = new wxMenu();
	m_mnuHowTo = new wxMenuItem( m_mnuHelp, ID_MNUHOWTO, wxString( wxT("How to...") ) , wxEmptyString, wxITEM_NORMAL );
	m_mnuHelp->Append( m_mnuHowTo );

	m_mnuAbout = new wxMenuItem( m_mnuHelp, ID_MNUABOUT, wxString( wxT("About") ) , wxEmptyString, wxITEM_NORMAL );
	m_mnuHelp->Append( m_mnuAbout );

	m_mbMain->Append( m_mnuHelp, wxT("Help") );

	this->SetMenuBar( m_mbMain );

	wxBoxSizer* bSizer4;
	bSizer4 = new wxBoxSizer( wxVERTICAL );

	m_txtStrings = new wxTextCtrl( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_DONTWRAP|wxTE_MULTILINE );
	bSizer4->Add( m_txtStrings, 1, wxEXPAND, 5 );


	this->SetSizer( bSizer4 );
	this->Layout();

	this->Centre( wxBOTH );
}

_frmMain::~_frmMain()
{
}

_dlgAbout::_dlgAbout( wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style ) : wxDialog( parent, id, title, pos, size, style )
{
	this->SetSizeHints( wxDefaultSize, wxDefaultSize );

	wxBoxSizer* bSizer6;
	bSizer6 = new wxBoxSizer( wxVERTICAL );

	m_lblAboutText = new wxStaticText( this, wxID_ANY, wxT("\tAbout\nString Manipulator App \nMade by Ziauddin"), wxDefaultPosition, wxDefaultSize, 0 );
	m_lblAboutText->Wrap( -1 );
	bSizer6->Add( m_lblAboutText, 1, wxALL|wxEXPAND, 5 );

	m_dlgBtns = new wxStdDialogButtonSizer();
	m_dlgBtnsOK = new wxButton( this, wxID_OK );
	m_dlgBtns->AddButton( m_dlgBtnsOK );
	m_dlgBtns->Realize();

	bSizer6->Add( m_dlgBtns, 0, wxALL|wxEXPAND, 5 );


	this->SetSizer( bSizer6 );
	this->Layout();
	bSizer6->Fit( this );

	this->Centre( wxBOTH );
}

_dlgAbout::~_dlgAbout()
{
}

_dlgSInput::_dlgSInput( wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style ) : wxDialog( parent, id, title, pos, size, style )
{
	this->SetSizeHints( wxSize( -1,-1 ), wxSize( -1,-1 ) );

	wxBoxSizer* bSizer8;
	bSizer8 = new wxBoxSizer( wxHORIZONTAL );

	m_lblInput = new wxStaticText( this, wxID_ANY, wxT("Input:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_lblInput->Wrap( -1 );
	bSizer8->Add( m_lblInput, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5 );

	m_txtInput = new wxTextCtrl( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
	bSizer8->Add( m_txtInput, 1, wxALIGN_CENTER_VERTICAL|wxALL, 5 );

	m_dlgBtns = new wxStdDialogButtonSizer();
	m_dlgBtnsOK = new wxButton( this, wxID_OK );
	m_dlgBtns->AddButton( m_dlgBtnsOK );
	m_dlgBtns->Realize();

	bSizer8->Add( m_dlgBtns, 0, wxEXPAND, 5 );


	this->SetSizer( bSizer8 );
	this->Layout();
	bSizer8->Fit( this );

	this->Centre( wxBOTH );
}

_dlgSInput::~_dlgSInput()
{
}
