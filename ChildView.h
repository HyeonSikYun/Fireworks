
// ChildView.h: CChildView 클래스의 인터페이스
//


#pragma once
#include "Bomb.h"

// CChildView 창

class CChildView : public CWnd
{
// 생성입니다.
public:
	CChildView();

// 특성입니다.
public:

// 작업입니다.
public:
	BombEngine _bombEngine;
	int NumOfFire;
	bool _bombNum;
	CString _num;
	int _fire;
	bool _play1;
	bool _play2;

// 재정의입니다.
	protected:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);

// 구현입니다.
public:
	virtual ~CChildView();

	// 생성된 메시지 맵 함수
protected:
	afx_msg void OnPaint();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void OnNumofflameFive();
	afx_msg void OnNumofflameSeven();
	afx_msg void OnUpdateNumofflameFive(CCmdUI *pCmdUI);
	afx_msg void OnUpdateNumofflameSeven(CCmdUI *pCmdUI);
	afx_msg void OnNumofflameTen();
	afx_msg void OnUpdateNumofflameTen(CCmdUI *pCmdUI);
	afx_msg void OnSeparationOne();
	afx_msg void OnSeparationTwo();
	afx_msg void OnUpdateSeparationOne(CCmdUI *pCmdUI);
	afx_msg void OnUpdateSeparationTwo(CCmdUI *pCmdUI);
	afx_msg void OnNumofflameTwenty();
	afx_msg void OnUpdateNumofflameTwenty(CCmdUI *pCmdUI);
};

