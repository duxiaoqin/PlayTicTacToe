/*
	Programmed by Xiaoqin Du, 383979583@qq.com
	School of Math and Computer Science, 
	Wuhan Textile University
*/

// TTTAlphaBetaView.h : interface of the CTTTAlphaBetaView class
//

#pragma once

#include "TicTacToe.h"
#include "TicTacToeDraw.h"
#include "TicTacToeInput.h"
#include "PlayTicTacToe.h"

//定义函数模板，用于成员函数线程化
template <typename TYPE, void (MyAI::PlayTicTacToe::*DoStandardAlphaBeta)()>
DWORD WINAPI ThreadComputerTurn_StandardAlphaBeta(LPVOID lpParameter)
{
	TYPE* pView = (TYPE*)lpParameter;
	pView->GetTTTPlay()->DoStandardAlphaBeta();
	return 0;
}

class CTTTAlphaBetaView : public CView
{
protected: // create from serialization only
	CTTTAlphaBetaView();
	DECLARE_DYNCREATE(CTTTAlphaBetaView)

// Attributes
public:
	CTTTAlphaBetaDoc* GetDocument() const;

// Operations
public:
	enum WHO_FIRST {COMPUTER_FIRST, HUMAN_FIRST};

	MyObjects::TicTacToe* GetTTT() {return m_pTTT;}
	MyAI::PlayTicTacToe* GetTTTPlay() {return m_pTTTPlay;}
	void ComputerTurn() {
		if (m_hTTTPlayThread) {
			CloseHandle(m_hTTTPlayThread);
			m_hTTTPlayThread = NULL;
		}

		m_hTTTPlayThread = CreateThread(NULL, 0, ThreadComputerTurn_StandardAlphaBeta<CTTTAlphaBetaView, &MyAI::PlayTicTacToe::DoStandardAlphaBeta>, this, 0, NULL);
	}
	WHO_FIRST GetWhoFirst() {return m_enumWhoFirst;}
	void RegenerateTTT();

private:
	MyObjects::TicTacToe* m_pTTT;
	MyGDI::TicTacToeDraw* m_pTTTDraw;
	MyInput::TicTacToeInput* m_pTTTInput;
	MyAI::PlayTicTacToe* m_pTTTPlay;
	HANDLE m_hTTTPlayThread;

	WHO_FIRST m_enumWhoFirst;

private:
	void Play();

	void ClearTTT();

// Overrides
public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// Implementation
public:
	virtual ~CTTTAlphaBetaView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in TTTAlphaBetaView.cpp
inline CTTTAlphaBetaDoc* CTTTAlphaBetaView::GetDocument() const
   { return reinterpret_cast<CTTTAlphaBetaDoc*>(m_pDocument); }
#endif

