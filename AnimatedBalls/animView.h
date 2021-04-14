
// animView.h : interface of the CanimView class
//

#pragma once

#include "CBall.h"
#include <vector>

#define BALLSIZE 60
#define BLUE RGB(0,0,255)

class CanimView : public CView
{
protected:
	CanimView() noexcept;
	DECLARE_DYNCREATE(CanimView)

// Attributes
public:
	CanimDoc* GetDocument() const;
// Overrides
public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:

// Implementation
public:
	virtual ~CanimView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

private:
	UINT_PTR m_nTimerID;
	BOOL m_bStart;
	CRect* m_pClientRect;
	std::vector<CBall*> balls;
	int ballCount;
// Generated message map functions
protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnStart();
	virtual void OnInitialUpdate();
	afx_msg void OnDestroy();
	afx_msg void OnTimer( UINT_PTR nIDEvent );
	afx_msg BOOL OnEraseBkgnd( CDC* pDC );
	virtual void OnPrepareDC( CDC* pDC, CPrintInfo* pInfo = NULL );
	afx_msg void OnBallAddball();
	afx_msg void OnBallRemoveball();

	afx_msg void OnSize( UINT nType, int cx, int cy );
	afx_msg void OnUpdateBallRemoveball( CCmdUI* pCmdUI );
	afx_msg void OnUpdateBallAddball( CCmdUI* pCmdUI );
};

#ifndef _DEBUG  // debug version in animView.cpp
inline CanimDoc* CanimView::GetDocument() const
   { return reinterpret_cast<CanimDoc*>(m_pDocument); }
#endif

