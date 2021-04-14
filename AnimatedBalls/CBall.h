#pragma once
#include <atltypes.h>
#include <afxwin.h>

#define BLACK RGB(0,0,0)
class CBall :
	public CRect
{
private:
	int OffsetX;
	int OffsetY;
	COLORREF m_pBallColor;
	CPen* m_pBallPen;
	CBrush* m_pBallBrush;
	CRect* m_pBoundRect;


public:
	CBall(int LeftTopX = 0, int LeftTopY = 0, int RightBottomX = 0, int RightBottomY = 0, COLORREF color = 0, int OffsetX = 0, int OffsetY = 0, CRect* boundRect = NULL);
	CBall(CRect* rect, COLORREF color = BLACK, int OffsetX = 0, int OffsetY = 0, CRect* prect = NULL);
	CBall( const CPoint point, const CSize size = 1, COLORREF color = 0, int OffsetX = 0, int OffsetY = 0, CRect* rect = NULL );
	~CBall();

	void SetBall( CRect* rect, COLORREF BallColor );
	void SetOffset( int x, int y );
	void SetBoundRect( CRect* rect );
	int GetOffsetX() const;
	int GetOffsetY() const;


	inline void CreateObjects( COLORREF BallColor )
	{
		m_pBallPen->CreatePen( PS_SOLID, 1, BallColor );
		m_pBallBrush->CreateSolidBrush( BallColor );
	}
	inline void DeleteObjects() {
		m_pBallPen->DeleteObject();
		m_pBallBrush->DeleteObject();
	}
	void InitObjects( COLORREF BallColor );
	inline void SetBallColor( COLORREF BallColor )
	{
		DeleteObjects();
		CreateObjects( BallColor );
	}
	inline void SetBallSize( CRect* size )
	{
		m_pBoundRect = size;
	}

	inline void PaintBall( CDC* x ){
		CPen* oldPen = x->SelectObject( m_pBallPen );
		CBrush* oldBrush = x->SelectObject( m_pBallBrush );
	    x->Ellipse( this );
		x->SelectObject( oldPen );
		x->SelectObject( oldBrush );
	}

};

