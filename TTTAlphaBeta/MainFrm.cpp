/*
	Programmed by Xiaoqin Du, 383979583@qq.com
	School of Math and Computer Science, 
	Wuhan Textile University
*/

// MainFrm.cpp : implementation of the CMainFrame class
//

#include "stdafx.h"
#include "TTTAlphaBeta.h"

#include "MainFrm.h"

#include "TTTAlphaBetaDoc.h"
#include "TTTAlphaBetaView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CMainFrame

IMPLEMENT_DYNCREATE(CMainFrame, CFrameWnd)

BEGIN_MESSAGE_MAP(CMainFrame, CFrameWnd)
	ON_WM_CREATE()
	ON_WM_TIMER()
	ON_WM_CLOSE()
END_MESSAGE_MAP()

static UINT indicators[] =
{
	ID_SEPARATOR,           // status line indicator
	ID_INDICATOR_CAPS,
	ID_INDICATOR_NUM,
	ID_INDICATOR_SCRL,
};

// CMainFrame construction/destruction

CMainFrame::CMainFrame()
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

	if (!m_wndToolBar.CreateEx(this, TBSTYLE_FLAT, WS_CHILD | WS_VISIBLE | CBRS_TOP | CBRS_GRIPPER | CBRS_TOOLTIPS | CBRS_FLYBY | CBRS_SIZE_DYNAMIC) ||
		!m_wndToolBar.LoadToolBar(IDR_MAINFRAME))
	{
		TRACE0("Failed to create toolbar\n");
		return -1;      // fail to create
	}

	if (!m_wndStatusBar.Create(this))
	{
		TRACE0("Failed to create status bar\n");
		return -1;      // fail to create
	}
	m_wndStatusBar.SetIndicators(indicators, sizeof(indicators)/sizeof(UINT));

	// TODO: Delete these three lines if you don't want the toolbar to be dockable
	m_wndToolBar.EnableDocking(CBRS_ALIGN_ANY);
	EnableDocking(CBRS_ALIGN_ANY);
	DockControlBar(&m_wndToolBar);

	SetTimer(1,500,NULL);

	return 0;
}

BOOL CMainFrame::PreCreateWindow(CREATESTRUCT& cs)
{
	if( !CFrameWnd::PreCreateWindow(cs) )
		return FALSE;
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

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

void CMainFrame::OnTimer(UINT_PTR nIDEvent)
{
	short result;

	// TODO: Add your message handler code here and/or call default
	CTTTAlphaBetaView* pTTTView = (CTTTAlphaBetaView*)GetActiveView();

	if (pTTTView->GetTTTPlay()->GetResult()) {
		pTTTView->GetTTTPlay()->ClearResult();
		CString str(L"TicTacToe thinking completed!");
		m_wndStatusBar.SetPaneText(0,str);
		if (MyAI::PlayTicTacToe::m_TTTNodeResult.stone.row != -1 && MyAI::PlayTicTacToe::m_TTTNodeResult.stone.col != -1) {
			pTTTView->GetTTT()->Play(MyAI::PlayTicTacToe::m_TTTNodeResult.stone.row, MyAI::PlayTicTacToe::m_TTTNodeResult.stone.col);
			pTTTView->GetTTT()->ChgPlayer();
			pTTTView->Invalidate();

			result = pTTTView->GetTTT()->IsTerminalState();
			if (result == pTTTView->GetTTT()->XWIN) {
				if (pTTTView->GetWhoFirst() == pTTTView->HUMAN_FIRST)
					MessageBox(L"Human win!");
				else
					MessageBox(L"Computer win!");

				pTTTView->RegenerateTTT();
				pTTTView->Invalidate();
			}
			else if (result == pTTTView->GetTTT()->OWIN) {
				if (pTTTView->GetWhoFirst() == pTTTView->HUMAN_FIRST)
					MessageBox(L"Computer win!");
				else
					MessageBox(L"Human win!");

				pTTTView->RegenerateTTT();
				pTTTView->Invalidate();
			}
			else if (result == pTTTView->GetTTT()->DRAW) {
				MessageBox(L"Draw!");

				pTTTView->RegenerateTTT();
				pTTTView->Invalidate();
			}
		}
	}

	if (pTTTView->GetTTTPlay()->GetMinimaxThread()) {
		CString str(L"TicTacToe is thinking...");
		m_wndStatusBar.SetPaneText(0,str);
	}

	CFrameWnd::OnTimer(nIDEvent);
}


void CMainFrame::OnClose()
{
	// TODO: Add your message handler code here and/or call default
	CTTTAlphaBetaView* pTTTView = (CTTTAlphaBetaView*)GetActiveView();

	if (pTTTView->GetTTTPlay()->GetMinimaxThread()) {
		MessageBox(L"TicTacToe is thinking!");
		return;
	}

	CFrameWnd::OnClose();
}