/*
	Programmed by Xiaoqin Du, 383979583@qq.com
	School of Math and Computer Science, 
	Wuhan Textile University
*/

#include "stdafx.h"

#include "TicTacToe.h"
#include "TicTacToeDraw.h"
#include "TicTacToeInput.h"

MyInput::TicTacToeInput::TicTacToeInput(MyObjects::TicTacToe* pTTT, short nXFlag, short nOFlag, short nSelFlag, short nNormalFlag, MyGDI::TicTacToeDraw* pTTTDraw, UINT uXCursor, UINT uOCursor)
{
	m_pTTT = pTTT;
	m_pTTTDraw = pTTTDraw;

	m_ppTTT = m_pTTT->GetTTT();

	m_nXFlag = nXFlag;
	m_nOFlag = nOFlag;
	m_nSelFlag = nSelFlag;
	m_nNormalFlag = nNormalFlag;

	m_uXCursor = uXCursor;
	m_uOCursor = uOCursor;

	m_hXCursor = LoadCursor(AfxGetApp()->m_hInstance, MAKEINTRESOURCE(m_uXCursor));
	m_hOCursor = LoadCursor(AfxGetApp()->m_hInstance, MAKEINTRESOURCE(m_uOCursor));
	m_hArrowCursor = LoadCursor(NULL, IDC_ARROW);

	m_nWidth = m_pTTT->GetWidth();
	m_nHeight = m_pTTT->GetHeight();

	m_nXStart = m_pTTTDraw->GetXStart();
	m_nYStart = m_pTTTDraw->GetYStart();
	m_nGridWidth = m_pTTTDraw->GetGridWidth();
	m_nGridHeight = m_pTTTDraw->GetGridHeight();

	m_nSelRow = -1; //��ЧROW
	m_nSelCol = -1; //��ЧCOL
}

MyInput::TicTacToeInput::~TicTacToeInput()
{
}

void MyInput::TicTacToeInput::OnMouseMove(CView* pView, UINT nFlags, CPoint point)
{
	int row, col;

	CRect rect(m_nXStart, m_nYStart, m_nXStart + m_nWidth * m_nGridWidth, m_nYStart + m_nHeight * m_nGridHeight);

	if (rect.PtInRect(point)) {//����������
		if (m_pTTT->GetPlayer())
			SetCursor(m_hXCursor);
		else
			SetCursor(m_hOCursor);

		row = (point.y - m_nYStart) / m_nGridHeight;
		col = (point.x - m_nXStart) / m_nGridWidth;
		if (m_nSelRow == -1 || m_nSelCol == -1) {//���ս�������
			m_nSelRow = row;
			m_nSelCol = col;
			m_pTTT->Select(m_nSelRow, m_nSelCol);
			pView->Invalidate();
		}
		else if (m_nSelRow != row || m_nSelCol != col) {//����һ�����̸������һ�����̸�
			m_pTTT->DeSelect(m_nSelRow, m_nSelCol);
			m_nSelRow = row;
			m_nSelCol = col;
			m_pTTT->Select(m_nSelRow, m_nSelCol);
			pView->Invalidate();
		}//else {}������һ�����̸���
	}
	else {//��겻����������
		SetCursor(m_hArrowCursor);

		if (m_nSelRow != -1 && m_nSelCol != -1) {
			m_pTTT->DeSelect(m_nSelRow, m_nSelCol);
			pView->Invalidate();
		}
		m_nSelRow = -1; //��ЧROW
		m_nSelCol = -1; //��ЧCOL
	}
}

bool MyInput::TicTacToeInput::OnLButtonDown(CView* pView, UINT nFlags, CPoint point)
{
	if (m_nSelRow == -1 || m_nSelCol == -1)
		return false;//��Ч����

	if (m_ppTTT[m_nSelRow][m_nSelCol] != m_nSelFlag)
		return false;//��Ч����

	m_pTTT->Play(m_nSelRow, m_nSelCol);
	m_pTTT->ChgPlayer();
	pView->Invalidate();

	return true;//��Ч��������
}