
// animView.cpp : implementation of the CanimView class
//

#include "pch.h"
#include "framework.h"
#ifndef SHARED_HANDLERS
#include "anim.h"
#endif

#include "animDoc.h"
#include "animView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif
#include "MainFrm.h"


// CanimView

IMPLEMENT_DYNCREATE(CanimView, CView)

BEGIN_MESSAGE_MAP(CanimView, CView)
	ON_COMMAND( ID_START_STOP, &CanimView::OnStart )
	ON_WM_DESTROY()
	ON_WM_TIMER()
	ON_WM_ERASEBKGND()
	ON_COMMAND( ID_BALL_ADDBALL, &CanimView::OnBallAddball )
	ON_COMMAND( ID_BALL_REMOVEBALL, &CanimView::OnBallRemoveball )
	ON_WM_SIZE()
	ON_UPDATE_COMMAND_UI( ID_BALL_REMOVEBALL, &CanimView::OnUpdateBallRemoveball )
	ON_UPDATE_COMMAND_UI( ID_BALL_ADDBALL, &CanimView::OnUpdateBallAddball )
END_MESSAGE_MAP()

// CanimView construction/destruction

void CALLBACK ZfxTimerProc(
	HWND hWnd,
	UINT nMsg,
	UINT nIDEvent,
	DWORD dwTime
)
{
	::SendMessage( hWnd, WM_TIMER, 0, 0 );
}
CanimView::CanimView() noexcept
{
	m_bStart = FALSE;
	m_pClientRect = new CRect( 0, 0, 0, 0 );

	srand( (unsigned)time( NULL ) );
	balls.push_back( new CBall( 20, 20, 20 + BALLSIZE, 20 + BALLSIZE, BLUE, 3, 1, m_pClientRect ) );
	ballCount = 1;

}

CanimView::~CanimView()
{
	delete m_pClientRect;
	int size_ = balls.size();
	for(int i = 0; i < size_; i++)
	{
		delete balls[i];
	}
}

BOOL CanimView::PreCreateWindow(CREATESTRUCT& cs)
{

	return CView::PreCreateWindow(cs);
}

// CanimView drawing

void CanimView::OnDraw(CDC* pDC)
{
	CanimDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	CDC memDC;
	BOOL b = memDC.CreateCompatibleDC( pDC );
	ASSERT( b );

	CBitmap bmp;
	b = bmp.CreateCompatibleBitmap( pDC, m_pClientRect->Width(), m_pClientRect->Height() );
	ASSERT( b );
	CBitmap* pOldBitmap = memDC.SelectObject( &bmp );
	memDC.FillSolidRect( m_pClientRect, RGB( 230, 230, 200 ) );

	int size_ = balls.size();
	for(int i = 0; i < size_; i++)
	{
		balls[i]->PaintBall( &memDC );
	}

	b = pDC->BitBlt( 0, 0, m_pClientRect->Width(), m_pClientRect->Height(), &memDC, 0, 0, SRCCOPY );
	ASSERT( b );

	memDC.SelectObject( pOldBitmap );
	bmp.DeleteObject();
	memDC.DeleteDC();

}


// CanimView diagnostics

#ifdef _DEBUG
void CanimView::AssertValid() const
{
	CView::AssertValid();
}

void CanimView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CanimDoc* CanimView::GetDocument() const
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CanimDoc)));
	return (CanimDoc*)m_pDocument;
}
#endif //_DEBUG


// CanimView message handlers


void CanimView::OnStart()
{
	m_bStart = !m_bStart;

	CMainFrame* pFrame = ( CMainFrame* ) GetParentFrame();
	pFrame->ResetButton( m_bStart );
}


void CanimView::OnInitialUpdate()
{
	CView::OnInitialUpdate();

	//m_nTimerID = SetTimer( WM_USER + 1, 20, NULL );
	m_nTimerID = SetTimer( WM_USER + 1, 20, ZfxTimerProc );
}


void CanimView::OnDestroy()
{
	KillTimer( m_nTimerID );
	CView::OnDestroy();
}


void CanimView::OnTimer( UINT_PTR nIDEvent )
{
	GetClientRect( m_pClientRect );
	if( m_bStart )
	{ 
		int size_ = balls.size();
		for(int i = 0; i < size_; i++)
		{	
				if(balls[i]->right >= m_pClientRect->right || balls[i]->left <= m_pClientRect->left) balls[i]->SetOffset( -1 * balls[i]->GetOffsetX(), balls[i]->GetOffsetY() );

				if(balls[i]->bottom >= m_pClientRect->bottom || balls[i]->top <= 0) balls[i]->SetOffset( balls[i]->GetOffsetX(), -1 * balls[i]->GetOffsetY() );
				balls[i]->OffsetRect( balls[i]->GetOffsetX(), balls[i]->GetOffsetY() );	
		}

		Invalidate();
	}

	CView::OnTimer( nIDEvent );
}


BOOL CanimView::OnEraseBkgnd( CDC* pDC )
{
	return 1;
}


void CanimView::OnPrepareDC( CDC* pDC, CPrintInfo* pInfo )
{
	GetClientRect( m_pClientRect );
	CView::OnPrepareDC( pDC, pInfo );
}


void CanimView::OnBallAddball()
{
	if(ballCount < 10)
	{
		int ballsize = rand() % 100 + 30;
		int r = rand() % 256;
		int g = rand() % 256;
		int b = rand() % 256;
		int x_offset = rand() % 9 + 1;
		int y_offset = rand() % 9 + 1;
		balls.push_back( new CBall( 20, 20, 20 + ballsize, 20 + ballsize, RGB( r, g, b ), x_offset, y_offset ) );
		ballCount++;
	}
	
}


void CanimView::OnBallRemoveball()
{
	if(ballCount > 1)
	{
		delete balls.back();
		balls.pop_back();
		ballCount--;
	
	}
}


void CanimView::OnSize( UINT nType, int cx, int cy )
{
	GetClientRect( m_pClientRect );
	for(auto it = balls.begin(); it != balls.end(); it++)
	{
		( *it )->SetBoundRect( m_pClientRect );
		if(( *it )->right == m_pClientRect->right && (*it)->GetOffsetX() > 0)
		{
			( *it )->SetOffset( -1 * ( *it )->GetOffsetX() - 1, ( *it )->GetOffsetY() );
		}

		if(( *it )->bottom >= m_pClientRect->bottom && ( *it )->GetOffsetY() < 0)
		{
			( *it )->SetOffset( ( *it )->GetOffsetX(), -1 * ( *it )->GetOffsetY() + 1 );
		}
	}

	CView::OnSize( nType, cx, cy );
}


void CanimView::OnUpdateBallRemoveball( CCmdUI* pCmdUI )
{
	if(ballCount == 1)
	{
		pCmdUI->Enable( FALSE );
	}
	else pCmdUI->Enable( TRUE );
}


void CanimView::OnUpdateBallAddball( CCmdUI* pCmdUI )
{
	if(ballCount == 10)
	{
		pCmdUI->Enable( FALSE );
	}
	else pCmdUI->Enable( TRUE );
}
