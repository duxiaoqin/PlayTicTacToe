/*
	Programmed by Xiaoqin Du, 383979583@qq.com
	School of Math and Computer Science, 
	Wuhan Textile University
*/

#include "stdafx.h"

#include "TicTacToe.h"

MyObjects::TicTacToe::TicTacToe()
{
	m_nWidth = 3;
	m_nHeight = 3;

	//棋盘初始化
	m_ppTTT = new short*[m_nHeight];
	for (int row = 0; row < m_nHeight; row++) {
		m_ppTTT[row] = new short[m_nWidth];
	}	
	for (int row = 0; row < m_nHeight; row++) {
		for (int col = 0; col < m_nWidth; col++) {
			m_ppTTT[row][col] = NORMALFLAG;
		}
	}

	//幻方初始化
	if (m_nWidth == 3 && m_nHeight == 3) {//3X3 TicTacToe幻方
		int magic_square[] = {2, 9, 4, 7, 5, 3, 6, 1, 8};
		m_ppMagic = new short*[m_nHeight];
		for (int row = 0; row < m_nHeight; row++) {
			m_ppMagic[row] = new short[m_nWidth];
		}	
		for (int row = 0; row < m_nHeight; row++) {
			for (int col = 0; col < m_nWidth; col++) {
				m_ppMagic[row][col] = magic_square[row * m_nWidth + col];
			}
		}
	}

	m_bXOPlayer = true; //X Player
}

MyObjects::TicTacToe::TicTacToe(const TicTacToe& ttt)
{
	m_bXOPlayer = ttt.m_bXOPlayer;
	m_nWidth = ttt.m_nWidth;
	m_nHeight = ttt.m_nHeight;

	//棋盘副本，初始化
	m_ppTTT = new short*[m_nHeight];
	for (int row = 0; row < m_nHeight; row++) {
		m_ppTTT[row] = new short[m_nWidth];
	}
	for (int row = 0; row < m_nHeight; row++) {//复制外部棋盘
		for (int col = 0; col < m_nWidth; col++) {
			m_ppTTT[row][col] = ttt.m_ppTTT[row][col];
		}
	}

	//幻方副本，初始化
	m_ppMagic = new short*[m_nHeight];
	for (int row = 0; row < m_nHeight; row++) {
		m_ppMagic[row] = new short[m_nWidth];
	}
	for (int row = 0; row < m_nHeight; row++) {//复制外部棋盘
		for (int col = 0; col < m_nWidth; col++) {
			m_ppMagic[row][col] = ttt.m_ppMagic[row][col];
		}
	}

	m_dequeXStones = ttt.m_dequeXStones;
	m_dequeOStones = ttt.m_dequeOStones;
}

MyObjects::TicTacToe::~TicTacToe()
{
	m_dequeXStones.clear();
	m_dequeOStones.clear();

	for (int row = 0; row < m_nHeight; row++) {
		delete m_ppMagic[row];
	}
	delete m_ppMagic;

	for (int row = 0; row < m_nHeight; row++) {
		delete m_ppTTT[row];
	}
	delete m_ppTTT;
}

bool MyObjects::TicTacToe::IsAnyNSumToK(int n, int k, std::deque<short>* pStones)
{
    int elem;
    std::deque<short> tmp = *pStones;

    if (n == 0)
        return (k == 0);
    else if (k < 0)
        return false;
    else if (pStones->size() == 0)
        return false;
    else {
        elem = tmp.front();
        tmp.pop_front();
        if (IsAnyNSumToK(n - 1, k - elem, &tmp))
            return true;
        else if (IsAnyNSumToK(n, k, &tmp))
            return true;
    }

    return false;
}

short MyObjects::TicTacToe::IsTerminalState()
{
	return IsTerminalState(&m_dequeXStones, &m_dequeOStones);
}

short MyObjects::TicTacToe::IsTerminalState(std::deque<short>* pXStones, std::deque<short>* pOStones)
{
	if (m_nWidth != 3 || m_nHeight != 3) //非3X3 TicTacToe，暂时这样处理，方便后期扩展
		return NONTERMINAL;

	//3X3 TicTacToe
    if (IsAnyNSumToK(3, 15, pXStones)) //X win
        return XWIN;
    else if (IsAnyNSumToK(3, 15, pOStones)) //O win
        return OWIN;
    else if (pXStones->size() + 
             pOStones->size() == 9) //Draw
        return DRAW;
    else //Other
        return NONTERMINAL;
}

void MyObjects::TicTacToe::Play(int row, int col)
{
	if (m_bXOPlayer) {
		m_ppTTT[row][col] = XFLAG;
		m_dequeXStones.push_back(m_ppMagic[row][col]);
	}
	else {
		m_ppTTT[row][col] = OFLAG;
		m_dequeOStones.push_back(m_ppMagic[row][col]);
	}
}

std::deque<MyObjects::TicTacToeStone*>* MyObjects::TicTacToe::GetAllPossibleMoves()
{
	MyObjects::TicTacToeStone* pStone;

	std::deque<MyObjects::TicTacToeStone*>* pTTTStones;

	pTTTStones = new std::deque<MyObjects::TicTacToeStone*>();
	
	for (int row = 0; row < m_nHeight; row++) {
		for (int col = 0; col < m_nWidth; col++) {
			if (m_ppTTT[row][col] != XFLAG && m_ppTTT[row][col] != OFLAG) {
				pStone = new MyObjects::TicTacToeStone();
				pStone->row = row;
				pStone->col = col;
				pStone->magic_code = m_ppMagic[row][col];
				pTTTStones->push_back(pStone);
			}
		}
	}

	return pTTTStones;
}

bool MyObjects::TicTacToe::operator==(const TicTacToe& ttt)
{
	if (m_bXOPlayer != ttt.m_bXOPlayer)
		return false;
	
	if (m_nWidth != ttt.m_nWidth || m_nHeight != ttt.m_nHeight)
		return false;

	for (int row = 0; row < m_nHeight; row++) {
		for (int col = 0; col < m_nWidth; col++) {
			if (m_ppTTT[row][col] != ttt.m_ppTTT[row][col])
				return false;
		}
	}

	return true;
}

bool MyObjects::TicTacToe::operator!=(const TicTacToe& ttt)
{
	return !(*this == ttt);
}