/*
	Programmed by Xiaoqin Du, 383979583@qq.com
	School of Math and Computer Science, 
	Wuhan Textile University
*/

#pragma once

#include <deque>

namespace MyObjects {
	
	struct TicTacToeStone {//TicTacToe落子位置信息
		int row;
		int col;
		short magic_code;
	};

	class TicTacToe {
	public:
		TicTacToe();
		TicTacToe(const TicTacToe& ttt); //拷贝构造函数
		~TicTacToe();

		short** GetTTT() {return m_ppTTT;}
		short** GetMagic() {return m_ppMagic;}
		int GetWidth() {return m_nWidth;}
		int GetHeight() {return m_nHeight;}
		bool GetPlayer() {return m_bXOPlayer;}
		void ChgPlayer() {m_bXOPlayer = !m_bXOPlayer;}
		void Play(int row, int col);
		void Select(int row, int col) {
			if (m_ppTTT[row][col] == NORMALFLAG)
				m_ppTTT[row][col] = SELFLAG;
		}
		void DeSelect(int row, int col) {
			if (m_ppTTT[row][col] == SELFLAG)
				m_ppTTT[row][col] = NORMALFLAG;
		}

		std::deque<TicTacToeStone*>* GetAllPossibleMoves(); //返回所有的可能下一落子位置信息，分配的空间由调用者负责释放
		short IsTerminalState();
		short IsTerminalState(std::deque<short>* pXStones, std::deque<short>* pOStones);

		bool operator==(const TicTacToe& ttt);
		bool operator!=(const TicTacToe& ttt);

		bool IsBeginning() {
			return m_dequeXStones.size() == 0 && m_dequeOStones.size() == 0;
		}

	public:
		static const short XFLAG = 1;
		static const short OFLAG = -1;
		static const short SELFLAG = -2;
		static const short NORMALFLAG = 0;

		static const short XWIN = 1;
		static const short OWIN = -1;
		static const short DRAW = 0;
		static const short NONTERMINAL = 2;

	private:
		bool IsAnyNSumToK(int n, int k, std::deque<short>* pStones);

	private:
		bool m_bXOPlayer;
		int m_nWidth;
		int m_nHeight;
		short** m_ppTTT; //TicTacToe棋盘
		short** m_ppMagic; //为判断胜负方便，使用幻方数字解释TicTacToe棋盘，需要依据棋盘大小初始化

		std::deque<short> m_dequeXStones; //保存X棋子位置（索引）
		std::deque<short> m_dequeOStones; //保存O棋子位置（索引）
	};
}