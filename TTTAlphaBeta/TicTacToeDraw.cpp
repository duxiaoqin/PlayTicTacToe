/*
	Programmed by Xiaoqin Du, 383979583@qq.com
	School of Math and Computer Science, 
	Wuhan Textile University
*/

#include "stdafx.h"

#include "TicTacToeDraw.h"

MyGDI::TicTacToeDraw::TicTacToeDraw(short** ppTTT, int nWidth, int nHeight, short nXFlag, short nOFlag, short nSelFlag, UINT uXBitmap, UINT uOBitmap)
{
	m_ppTTT = ppTTT;
	m_nWidth = nWidth;
	m_nHeight = nHeight;

	m_nXFlag = nXFlag;
	m_nOFlag = nOFlag;
	m_nSelFlag = nSelFlag;

	m_uXBitmap = uXBitmap;
	m_uOBitmap = uOBitmap;

	m_nXStart = 20;
	m_nYStart = 20;

	m_nGridWidth = 100;
	m_nGridHeight = 100;

	m_pXBitmap = new CBitmap();
	m_pOBitmap = new CBitmap();

	m_pXBitmap->LoadBitmap(m_uXBitmap);
	m_pOBitmap->LoadBitmap(m_uOBitmap);
}

MyGDI::TicTacToeDraw::~TicTacToeDraw()
{
	delete m_pXBitmap;
	delete m_pOBitmap;
}

void MyGDI::TicTacToeDraw::Draw(CDC* pDC)
{
	int nXStart, nYStart;

	nXStart = m_nXStart;
	nYStart = m_nYStart;
	for (int row = 0; row < m_nHeight; row++) {
		for (int col = 0; col < m_nWidth; col++) {
			if (m_ppTTT[row][col] == m_nXFlag)
				DrawBitmap(pDC, XBITMAP, nXStart, nYStart, m_nGridWidth, m_nGridHeight);
			else if (m_ppTTT[row][col] == m_nOFlag)
				DrawBitmap(pDC, OBITMAP, nXStart, nYStart, m_nGridWidth, m_nGridHeight);
			else if (m_ppTTT[row][col] == m_nSelFlag)
				DrawSelect(pDC, nXStart, nYStart, nXStart + m_nGridWidth, nYStart + m_nGridHeight);
			else
				DrawNormal(pDC, nXStart, nYStart, nXStart + m_nGridWidth, nYStart + m_nGridHeight);

			nXStart += m_nGridWidth;
		}
		nXStart = m_nXStart;
		nYStart += m_nGridHeight;
	}
}

void MyGDI::TicTacToeDraw::DrawBitmap(CDC* pDC, XOBITMAP enumBitmap, int nXStart, int nYStart, int nWidth, int nHeight)
{
	CDC dcMemory;

	dcMemory.CreateCompatibleDC(pDC);
	
	BITMAP bmpInfo;
	CBitmap* pOldBitmap;

	if (enumBitmap == XBITMAP) {
		m_pXBitmap->GetBitmap(&bmpInfo);
		pOldBitmap = dcMemory.SelectObject(m_pXBitmap);
	}
	else if (enumBitmap == OBITMAP) {
		m_pOBitmap->GetBitmap(&bmpInfo);
		pOldBitmap = dcMemory.SelectObject(m_pOBitmap);
	}
	pDC->StretchBlt(nXStart, nYStart, nWidth, nHeight, &dcMemory, 0, 0, bmpInfo.bmWidth, bmpInfo.bmHeight, SRCCOPY);
	dcMemory.SelectObject(pOldBitmap);
}

void MyGDI::TicTacToeDraw::DrawNormal(CDC* pDC, int x1, int y1, int x2, int y2)
{
	CBrush brushGreen(RGB(0, 255, 0));
	CBrush* pOldBrush = pDC->SelectObject(&brushGreen);
				
	CPen penWhite;
	penWhite.CreatePen(PS_SOLID, 3, RGB(255, 255, 255));
	CPen* pOldPen = pDC->SelectObject(&penWhite);

	pDC->Rectangle(x1, y1, x2, y2);

	pDC->SelectObject(pOldBrush);
	pDC->SelectObject(pOldPen);
}

void MyGDI::TicTacToeDraw::DrawSelect(CDC* pDC, int x1, int y1, int x2, int y2)
{
	CBrush brushBlue(RGB(0, 0, 255));
	CBrush* pOldBrush = pDC->SelectObject(&brushBlue);
				
	CPen penBlack;
	penBlack.CreatePen(PS_SOLID, 3, RGB(0, 0, 0));
	CPen* pOldPen = pDC->SelectObject(&penBlack);

	pDC->Rectangle(x1, y1, x2, y2);

	pDC->SelectObject(pOldBrush);
	pDC->SelectObject(pOldPen);
}