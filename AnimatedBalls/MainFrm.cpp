
// MainFrm.cpp : implementation of the CMainFrame class
//

#include "pch.h"
#include "framework.h"
#include "anim.h"

#include "MainFrm.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CMainFrame

IMPLEMENT_DYNCREATE(CMainFrame, CFrameWnd)

BEGIN_MESSAGE_MAP(CMainFrame, CFrameWnd)
	ON_WM_CREATE()
END_MESSAGE_MAP()

static UINT indicators[] =
{
	ID_SEPARATOR,           // status line indicator
	ID_INDICATOR_CAPS,
	ID_INDICATOR_NUM,
	ID_INDICATOR_SCRL,
};

UINT CMainFrame::m_buttonsIDs[] =
{
	ID_START_STOP,
	ID_BALL_ADDBALL,
	ID_BALL_REMOVEBALL,
	ID_APP_ABOUT,
};


// CMainFrame construction/destruction

CMainFrame::CMainFrame() noexcept
{
	// TODO: add member initialization code here
}

CMainFrame::~CMainFrame()
{
}

int CMainFrame::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CFrameWnd::OnCreate(lpCreateStruct) == -1)
		return -1;

	if(!m_wndToolBar.Create( this ) ||
		!m_wndToolBar.LoadBitmap( IDR_MAINFRAME ) ||
		!m_wndToolBar.SetButtons( m_buttonsIDs, sizeof( m_buttonsIDs ) / sizeof( UINT ) ))
	{
		TRACE0( "Failed to create toolbar\n" );
		return -1;      // fail to create
	}

	CToolBarCtrl& BarCtrl = m_wndToolBar.GetToolBarCtrl();
	BarCtrl.SetBitmapSize( CSize( 33, 28 ) );
	BarCtrl.SetButtonSize( CSize( 41, 35 ) );

	if (!m_wndStatusBar.Create(this))
	{
		TRACE0("Failed to create status bar\n");
		return -1;      // fail to create
	}
	m_wndStatusBar.SetIndicators(indicators, sizeof(indicators)/sizeof(UINT));

	m_wndToolBar.EnableDocking(CBRS_ALIGN_ANY);
	EnableDocking(CBRS_ALIGN_ANY);
	DockControlBar(&m_wndToolBar);


	return 0;
}

BOOL CMainFrame::PreCreateWindow(CREATESTRUCT& cs)
{
	if( !CFrameWnd::PreCreateWindow(cs) )
		return FALSE;

	return TRUE;
}

// CMainFrame diagnostics

#ifdef _DEBUG
void CMainFrame::AssertValid() const
{
	CFrameWnd::AssertValid();
}

void CMainFrame::Dump(CDumpContext& dc) const
{
	CFrameWnd::Dump(dc);
}
#endif //_DEBUG


// CMainFrame message handlers



void CMainFrame::ResetButton( BOOL b )
{
	int buttonIx = sizeof( m_buttonsIDs ) / sizeof( UINT );
	if(b)
		m_wndToolBar.SetButtonInfo( 0, ID_START_STOP, TBBS_BUTTON, buttonIx );
	else
		m_wndToolBar.SetButtonInfo( 0, ID_START_STOP, TBBS_BUTTON, 0 );

	m_wndToolBar.Invalidate();
}
