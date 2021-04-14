#include "pch.h"
#include "CBall.h"

CBall::CBall( int LeftTopX, int LeftTopY, int RightBottomX, int RightBottomY, COLORREF color, int OffsetX, int OffsetY, CRect* boundRect ) :
	m_pBallColor(color), 
	OffsetX(OffsetX), OffsetY(OffsetY),
	CRect( CPoint( LeftTopX, LeftTopY ), CPoint( RightBottomX, RightBottomY ) )
{
	m_pBoundRect = boundRect;
	this->InitObjects(color);
}

CBall::CBall( CRect* rect, COLORREF color, int OffsetX, int OffsetY, CRect* boundRect ) : OffsetX(OffsetX), OffsetY(OffsetY), m_pBallColor(color)
{
	m_pBoundRect = boundRect;
	this->InitObjects( color );
}

CBall::CBall( const CPoint point, const CSize size, COLORREF color, int OffsetX, int OffsetY, CRect* boundRect ) : m_pBallColor(color), OffsetX(OffsetX), OffsetY(OffsetY)
{
	m_pBoundRect = boundRect;
	this->InitObjects( color );
}

CBall::~CBall()
{
	DeleteObjects();
}

void CBall::InitObjects( COLORREF BallColor )
{
	m_pBallPen = new CPen(PS_SOLID, 1, BallColor);
	m_pBallBrush = new CBrush(BallColor);
}


void CBall::SetBall( CRect* rect, COLORREF BallColor )
{
	SetBallSize( rect );
	SetBallColor( BallColor );
}
void CBall::SetOffset( int x, int y )
{
	OffsetX = x;
	OffsetY = y;
}
void CBall::SetBoundRect( CRect* rect )
{
	m_pBoundRect = rect;
}

int CBall::GetOffsetX() const
{
	return OffsetX;
}
int CBall::GetOffsetY() const
{
	return OffsetY;
}
