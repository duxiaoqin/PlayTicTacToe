/*
	Programmed by Xiaoqin Du, 383979583@qq.com
	School of Math and Computer Science, 
	Wuhan Textile University
*/

// TTTAlphaBetaView.cpp : implementation of the CTTTAlphaBetaView class
//

#include "stdafx.h"
// SHARED_HANDLERS can be defined in an ATL project implementing preview, thumbnail
// and search filter handlers and allows sharing of document code with that project.
#ifndef SHARED_HANDLERS
#include "TTTAlphaBeta.h"
#endif

#include "TTTAlphaBetaDoc.h"
#include "TTTAlphaBetaView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CTTTAlphaBetaView

IMPLEMENT_DYNCREATE(CTTTAlphaBetaView, CView)

BEGIN_MESSAGE_MAP(CTTTAlphaBetaView, CView)
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
	ON_WM_MOUSEMOVE()
	ON_WM_LBUTTONDOWN()
END_MESSAGE_MAP()

// CTTTAlphaBetaView construction/destruction

CTTTAlphaBetaView::CTTTAlphaBetaView()
{
	// TODO: add construction code here
	m_pTTT = new MyObjects::TicTacToe();
	m_pTTTDraw = NULL;
	m_pTTTInput = NULL;
	m_pTTTPlay = NULL;

	m_hTTTPlayThread = NULL;

	m_enumWhoFirst = HUMAN_FIRST;

	Play();
}

CTTTAlphaBetaView::~CTTTAlphaBetaView()
{
	ClearTTT();
}

void CTTTAlphaBetaView::ClearTTT()
{
	if (m_pTTTPlay)
		delete m_pTTTPlay;
	m_pTTTPlay = NULL;

	if (m_pTTTInput)
		delete m_pTTTInput;
	m_pTTTInput = NULL;

	if (m_pTTTDraw)
		delete m_pTTTDraw;
	m_pTTTDraw = NULL;

	if (m_pTTT)
		delete m_pTTT;
	m_pTTT = NULL;

	if (m_hTTTPlayThread)
		CloseHandle(m_hTTTPlayThread);
	m_hTTTPlayThread = NULL;
}

BOOL CTTTAlphaBetaView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

// CTTTAlphaBetaView drawing

void CTTTAlphaBetaView::OnDraw(CDC* pDC)
{
	CTTTAlphaBetaDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: add draw code for native data here
	if (m_pTTTDraw)
		m_pTTTDraw->Draw(pDC);
}

void CTTTAlphaBetaView::RegenerateTTT()
{
	ClearTTT();
	m_pTTT = new MyObjects::TicTacToe();

	Play();
}

void CTTTAlphaBetaView::Play()
{
	if (!m_pTTTDraw)
		m_pTTTDraw = new MyGDI::TicTacToeDraw(m_pTTT->GetTTT(), m_pTTT->GetWidth(), m_pTTT->GetHeight(), m_pTTT->XFLAG, m_pTTT->OFLAG, m_pTTT->SELFLAG, IDB_XBITMAP, IDB_OBITMAP);

	if (!m_pTTTInput)
		m_pTTTInput = new MyInput::TicTacToeInput(m_pTTT, m_pTTT->XFLAG, m_pTTT->OFLAG, m_pTTT->SELFLAG, m_pTTT->NORMALFLAG, m_pTTTDraw, IDC_XCURSOR, IDC_OCURSOR);

	if (!m_pTTTPlay)
		m_pTTTPlay = new MyAI::PlayTicTacToe(*m_pTTT);

	if (m_pTTT->IsBeginning() && m_enumWhoFirst == COMPUTER_FIRST) {
		m_pTTT->Play(1, 1);
		m_pTTT->ChgPlayer();
	}
}

// CTTTAlphaBetaView printing

BOOL CTTTAlphaBetaView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CTTTAlphaBetaView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CTTTAlphaBetaView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}


// CTTTAlphaBetaView diagnostics

#ifdef _DEBUG
void CTTTAlphaBetaView::AssertValid() const
{
	CView::AssertValid();
}

void CTTTAlphaBetaView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CTTTAlphaBetaDoc* CTTTAlphaBetaView::GetDocument() const // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CTTTAlphaBetaDoc)));
	return (CTTTAlphaBetaDoc*)m_pDocument;
}
#endif //_DEBUG


// CTTTAlphaBetaView message handlers
void CTTTAlphaBetaView::OnMouseMove(UINT nFlags, CPoint point)
{
	// TODO: Add your message handler code here and/or call default
	if (m_pTTTInput &&
		((m_enumWhoFirst == HUMAN_FIRST && m_pTTT->GetPlayer()) || 
		 (m_enumWhoFirst == COMPUTER_FIRST && !m_pTTT->GetPlayer())))
		m_pTTTInput->OnMouseMove(this, nFlags, point);

	CView::OnMouseMove(nFlags, point);
}

void CTTTAlphaBetaView::OnLButtonDown(UINT nFlags, CPoint point)
{
	short result;
	bool isBeginning = false;

	// TODO: Add your message handler code here and/or call default
	if (m_pTTTInput && 
		((m_enumWhoFirst == HUMAN_FIRST && m_pTTT->GetPlayer()) || 
		 (m_enumWhoFirst == COMPUTER_FIRST && !m_pTTT->GetPlayer()))) {
		if (!m_pTTTInput->OnLButtonDown(this, nFlags, point)) {//Human turn
			CView::OnLButtonDown(nFlags, point);
			return;
		}

		result = m_pTTT->IsTerminalState();
		if (result == m_pTTT->XWIN) {
			if (m_enumWhoFirst == HUMAN_FIRST)
				MessageBox(L"Human win!");
			else
				MessageBox(L"Computer win!");
			RegenerateTTT();
			Invalidate();
			isBeginning = true;
		}
		else if (result == m_pTTT->OWIN) {
			if (m_enumWhoFirst == HUMAN_FIRST)
				MessageBox(L"Computer win!");
			else
				MessageBox(L"Human win!");
			RegenerateTTT();
			Invalidate();
			isBeginning = true;
		}
		else if (result == m_pTTT->DRAW) {
			MessageBox(L"Draw!");
			RegenerateTTT();
			Invalidate();
			isBeginning = true;
		}
	
		//Computer turn
		if (*m_pTTTPlay->GetTTT() != *m_pTTT && !isBeginning) {
			m_pTTTPlay->Update(*m_pTTT);
			ComputerTurn();
		}
	}

	CView::OnLButtonDown(nFlags, point);
}