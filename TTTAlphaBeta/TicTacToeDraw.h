/*
	Programmed by Xiaoqin Du, 383979583@qq.com
	School of Math and Computer Science, 
	Wuhan Textile University
*/

#pragma once

namespace MyGDI {
	class TicTacToeDraw {
		enum XOBITMAP {XBITMAP, OBITMAP};
	public:
		TicTacToeDraw(short** ppTTT, int nWidth, int nHeight, short nXFlag, short nOFlag, short nSelFlag, UINT uXBitmap, UINT uOBitmap);
		~TicTacToeDraw();

		void Draw(CDC* pDC);

		int GetXStart() {return m_nXStart;}
		int GetYStart() {return m_nYStart;}
		int GetGridWidth() {return m_nGridWidth;}
		int GetGridHeight() {return m_nGridHeight;}

	private:
		void DrawBitmap(CDC* pDC, XOBITMAP enumBitmap, int nXStart, int nYStart, int nWidth, int nHeight);
		void DrawNormal(CDC* pDC, int x1, int y1, int x2, int y2);
		void DrawSelect(CDC* pDC, int x1, int y1, int x2, int y2);

	private:
		short** m_ppTTT;
		int m_nWidth;
		int m_nHeight;
		short m_nXFlag;
		short m_nOFlag;
		short m_nSelFlag;

		UINT m_uXBitmap;
		UINT m_uOBitmap;

		int m_nXStart;
		int m_nYStart;

		int m_nGridWidth;
		int m_nGridHeight;

		CBitmap* m_pXBitmap;
		CBitmap* m_pOBitmap;
	};
}