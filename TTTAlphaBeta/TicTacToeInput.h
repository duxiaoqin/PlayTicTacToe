/*
	Programmed by Xiaoqin Du, 383979583@qq.com
	School of Math and Computer Science, 
	Wuhan Textile University
*/

#pragma once

namespace MyInput {
	class TicTacToeInput {
	public:
		TicTacToeInput(MyObjects::TicTacToe* pTTT, short nXFlag, short nOFlag, short nSelFlag, short nNormalFlag, MyGDI::TicTacToeDraw* pTTTDraw, UINT uXCursor, UINT uOCursor);
		~TicTacToeInput();

		void OnMouseMove(CView* pView, UINT nFlags, CPoint point);
		bool OnLButtonDown(CView* pView, UINT nFlags, CPoint point);
	
	private:
		MyObjects::TicTacToe* m_pTTT;
		MyGDI::TicTacToeDraw* m_pTTTDraw;

	private:
		short** m_ppTTT;
		int m_nXStart;
		int m_nYStart;
		int m_nWidth;
		int m_nHeight;
		int m_nGridWidth;
		int m_nGridHeight;

		UINT m_uXCursor;
		UINT m_uOCursor;

		HCURSOR m_hXCursor;
		HCURSOR m_hOCursor;
		HCURSOR m_hArrowCursor;

		short m_nXFlag;
		short m_nOFlag;
		short m_nSelFlag;
		short m_nNormalFlag;
		int m_nSelRow;
		int m_nSelCol;
	};
}