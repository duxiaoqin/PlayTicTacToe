/*
	Programmed by Xiaoqin Du, 383979583@qq.com
	School of Math and Computer Science, 
	Wuhan Textile University
*/

#pragma once

#include <deque>

namespace MyObjects {
	
	struct TicTacToeStone {//TicTacToe����λ����Ϣ
		int row;
		int col;
		short magic_code;
	};

	class TicTacToe {
	public:
		TicTacToe();
		TicTacToe(const TicTacToe& ttt); //�������캯��
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

		std::deque<TicTacToeStone*>* GetAllPossibleMoves(); //�������еĿ�����һ����λ����Ϣ������Ŀռ��ɵ����߸����ͷ�
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
		short** m_ppTTT; //TicTacToe����
		short** m_ppMagic; //Ϊ�ж�ʤ�����㣬ʹ�û÷����ֽ���TicTacToe���̣���Ҫ�������̴�С��ʼ��

		std::deque<short> m_dequeXStones; //����X����λ�ã�������
		std::deque<short> m_dequeOStones; //����O����λ�ã�������
	};
}