
// ChildView.cpp: CChildView 클래스의 구현
//

#include "stdafx.h"
#include "MFC_0513.h"
#include "ChildView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CChildView

CChildView::CChildView()
{
	NumOfFire = 0;
	_bombNum = false;
	_fire = 10;
	_play1 = false;
	_play2 = true;
}

CChildView::~CChildView()
{
}


BEGIN_MESSAGE_MAP(CChildView, CWnd)
	ON_WM_PAINT()
	ON_WM_LBUTTONDOWN()
	ON_WM_TIMER()
	ON_WM_CREATE()
	ON_WM_KEYDOWN()
	ON_WM_ERASEBKGND()
	ON_WM_ERASEBKGND()
	ON_COMMAND(ID_NUMOFFLAME_FIVE, &CChildView::OnNumofflameFive)
	ON_COMMAND(ID_NUMOFFLAME_SEVEN, &CChildView::OnNumofflameSeven)
	ON_UPDATE_COMMAND_UI(ID_NUMOFFLAME_FIVE, &CChildView::OnUpdateNumofflameFive)
	ON_UPDATE_COMMAND_UI(ID_NUMOFFLAME_SEVEN, &CChildView::OnUpdateNumofflameSeven)
	ON_COMMAND(ID_NUMOFFLAME_TEN, &CChildView::OnNumofflameTen)
	ON_UPDATE_COMMAND_UI(ID_NUMOFFLAME_TEN, &CChildView::OnUpdateNumofflameTen)
	ON_COMMAND(ID_SEPARATION_ONE, &CChildView::OnSeparationOne)
	ON_COMMAND(ID_SEPARATION_TWO, &CChildView::OnSeparationTwo)
	ON_UPDATE_COMMAND_UI(ID_SEPARATION_ONE, &CChildView::OnUpdateSeparationOne)
	ON_UPDATE_COMMAND_UI(ID_SEPARATION_TWO, &CChildView::OnUpdateSeparationTwo)
	ON_COMMAND(ID_NUMOFFLAME_TWENTY, &CChildView::OnNumofflameTwenty)
	ON_UPDATE_COMMAND_UI(ID_NUMOFFLAME_TWENTY, &CChildView::OnUpdateNumofflameTwenty)
END_MESSAGE_MAP()



// CChildView 메시지 처리기

BOOL CChildView::PreCreateWindow(CREATESTRUCT& cs) 
{
	if (!CWnd::PreCreateWindow(cs))
		return FALSE;

	cs.dwExStyle |= WS_EX_CLIENTEDGE;
	cs.style &= ~WS_BORDER;
	cs.lpszClass = AfxRegisterWndClass(CS_HREDRAW|CS_VREDRAW|CS_DBLCLKS, 
		::LoadCursor(nullptr, IDC_ARROW), reinterpret_cast<HBRUSH>(COLOR_WINDOW+1), nullptr);

	return TRUE;
}

void CChildView::OnPaint() 
{
	CPaintDC dc(this); // 그리기를 위한 디바이스 컨텍스트입니다.
	
	// TODO: 여기에 메시지 처리기 코드를 추가합니다.
	CRect rect;
	GetClientRect(&rect);
	CDC memDc;
	memDc.CreateCompatibleDC(&dc);
	CBitmap bitmap;
	bitmap.CreateCompatibleBitmap(&dc, rect.right, rect.bottom);
	memDc.SelectObject(&bitmap);

	auto pos = _bombEngine._bombParticles.GetHeadPosition();
	while (pos != nullptr) {
		auto bomb = _bombEngine._bombParticles.GetNext(pos);
		bomb.draw(&memDc);
	}

	_num.Format(_T("불꽃 갯수 : %d"), NumOfFire);
	memDc.TextOut(5, 5, _num);
	dc.BitBlt(0, 0, rect.Width(), rect.Height(), &memDc, 0, 0, SRCCOPY);
	// 그리기 메시지에 대해서는 CWnd::OnPaint()를 호출하지 마십시오.
}


void CChildView::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	if (nIDEvent == 0) {
		auto pos = _bombEngine._bombParticles.GetHeadPosition();
		while (pos != nullptr) {
			auto cur = pos;
			auto &bomb = _bombEngine._bombParticles.GetNext(pos);
			bomb.update(0.1f);
			if (bomb.isDead()) {
				if (bomb._level == 0)
				{
					NumOfFire--;
					_bombNum = false;
				}
				if (_play1 == true)
				{
					if (bomb._level < 1) {
						for (int i = 0; i < _fire; i++) {
							float theta = i * rand() % 360 / 180.0f*3.141592; // 36.0f인건 개수가 10이라 360을 10으로 나눈것
							Bomb tailBomb;
							tailBomb._speed = 10.0f; // 터지고 나서 위로 살짝 이동 ( 이쁘게 하려고 )
							double px = bomb.x() + 30.0f*cos(theta);
							double py = bomb.y() + 30.0f*sin(theta);
							tailBomb.setPos(px, py);
							tailBomb._size = bomb._size / 3.0f;
							tailBomb._R = bomb._oR;
							tailBomb._G = bomb._oG;
							tailBomb._B = bomb._oB;
							tailBomb.x_dir = bomb.x_dir;
							tailBomb.x_move = bomb.x_move;
							tailBomb._level = bomb._level + 1;
							tailBomb._timeLeft = 1.0f / (1 + tailBomb._level);
							_bombEngine.add(tailBomb);
						}
					}
					_bombEngine._bombParticles.RemoveAt(cur);
				}
				else if (_play2 == true)
				{
					if (bomb._level < 3) {
						for (int i = 0; i < _fire; i++) {
							float theta = i * rand() % 360 / 180.0f*3.141592; // 36.0f인건 개수가 10이라 360을 10으로 나눈것
							Bomb tailBomb;
							tailBomb._speed = 10.0f; // 터지고 나서 위로 살짝 이동 ( 이쁘게 하려고 )
							double px = bomb.x() + 30.0f*cos(theta);
							double py = bomb.y() + 30.0f*sin(theta);
							tailBomb.setPos(px, py);
							tailBomb._size = bomb._size / 3.0f;
							tailBomb._R = bomb._oR;
							tailBomb._G = bomb._oG;
							tailBomb._B = bomb._oB;
							tailBomb.x_dir = bomb.x_dir;
							tailBomb.x_move = bomb.x_move;
							tailBomb._level = bomb._level + 1;
							tailBomb._timeLeft = 1.0f / (1 + tailBomb._level);
							_bombEngine.add(tailBomb);
						}
					}
					_bombEngine._bombParticles.RemoveAt(cur);
				}
			}
		}
	}
	Invalidate();
	CWnd::OnTimer(nIDEvent);
}


int CChildView::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CWnd::OnCreate(lpCreateStruct) == -1)
		return -1;

	// TODO:  여기에 특수화된 작성 코드를 추가합니다.
	SetTimer(0, 30, NULL);
	return 0;
}


void CChildView::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	switch (nChar)
	{
	case VK_SPACE:
		Bomb bomb;
		bomb.setPos(600, 650);
		_bombEngine.add(bomb);
		NumOfFire++;
		_bombNum = true;
		Invalidate();
	}

	CWnd::OnKeyDown(nChar, nRepCnt, nFlags);
}

BOOL CChildView::OnEraseBkgnd(CDC* pDC)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	return true;
	//return CWnd::OnEraseBkgnd(pDC);
}


void CChildView::OnNumofflameFive()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CClientDC dc(this);
	_fire = 5;
}


void CChildView::OnNumofflameSeven()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	_fire = 7;
}


void CChildView::OnUpdateNumofflameFive(CCmdUI *pCmdUI)
{
	// TODO: 여기에 명령 업데이트 UI 처리기 코드를 추가합니다.
	pCmdUI->SetCheck(_fire == 5);
}


void CChildView::OnUpdateNumofflameSeven(CCmdUI *pCmdUI)
{
	// TODO: 여기에 명령 업데이트 UI 처리기 코드를 추가합니다.
	pCmdUI->SetCheck(_fire == 7);
}


void CChildView::OnNumofflameTen()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	_fire = 10;
}


void CChildView::OnUpdateNumofflameTen(CCmdUI *pCmdUI)
{
	// TODO: 여기에 명령 업데이트 UI 처리기 코드를 추가합니다.
	pCmdUI->SetCheck(_fire == 10);
}


void CChildView::OnSeparationOne()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	_play1 = true;
	_play2 = false;
}


void CChildView::OnSeparationTwo()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	_play1 = false;
	_play2 = true;
}


void CChildView::OnUpdateSeparationOne(CCmdUI *pCmdUI)
{
	// TODO: 여기에 명령 업데이트 UI 처리기 코드를 추가합니다.
	pCmdUI->SetCheck(_play1 == true);
}


void CChildView::OnUpdateSeparationTwo(CCmdUI *pCmdUI)
{
	// TODO: 여기에 명령 업데이트 UI 처리기 코드를 추가합니다.
	pCmdUI->SetCheck(_play2 == true);
}


void CChildView::OnNumofflameTwenty()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	_fire = 20;
}


void CChildView::OnUpdateNumofflameTwenty(CCmdUI *pCmdUI)
{
	// TODO: 여기에 명령 업데이트 UI 처리기 코드를 추가합니다.
	pCmdUI->SetCheck(_fire == 20);
}
