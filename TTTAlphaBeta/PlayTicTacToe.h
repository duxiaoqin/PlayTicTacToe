/*
	Programmed by Xiaoqin Du, 383979583@qq.com
	School of Math and Computer Science, 
	Wuhan Textile University
*/

#pragma once

#include "TicTacToe.h"

namespace MyAI {

	struct TicTacToeNode {
		MyObjects::TicTacToeStone stone;
		short value;
	};

	//���庯��ģ�壬���ڳ�Ա�����̻߳�
	template <typename TYPE, TicTacToeNode* (TYPE::*StandardMinimax)(MyObjects::TicTacToe*)>
	DWORD WINAPI DoThreadStandardMinimax(LPVOID lpParameter)
	{
		TicTacToeNode* pTTTNode = NULL;
	
		TYPE* objPlayTTT = (TYPE*)lpParameter;
		pTTTNode = objPlayTTT->StandardMinimax(objPlayTTT->GetTTT());
		if (pTTTNode) {//�����������
			PlayTicTacToe::m_TTTNodeResult.stone.row = pTTTNode->stone.row;
			PlayTicTacToe::m_TTTNodeResult.stone.col = pTTTNode->stone.col;
			PlayTicTacToe::m_TTTNodeResult.stone.magic_code = pTTTNode->stone.magic_code;
			PlayTicTacToe::m_TTTNodeResult.value = pTTTNode->value;
		}
		else {
			PlayTicTacToe::m_TTTNodeResult.stone.row = -1;
			PlayTicTacToe::m_TTTNodeResult.stone.col = -1;
			PlayTicTacToe::m_TTTNodeResult.stone.magic_code = -1;
		}
		return 0;
	}

	//���庯��ģ�壬���ڳ�Ա�����̻߳�
	template <typename TYPE, TicTacToeNode* (TYPE::*NegamaxMinimax)(MyObjects::TicTacToe*)>
	DWORD WINAPI DoThreadNegamaxMinimax(LPVOID lpParameter)
	{
		TicTacToeNode* pTTTNode = NULL;
	
		TYPE* objPlayTTT = (TYPE*)lpParameter;
		pTTTNode = objPlayTTT->NegamaxMinimax(objPlayTTT->GetTTT());
		if (pTTTNode) {//�����������
			PlayTicTacToe::m_TTTNodeResult.stone.row = pTTTNode->stone.row;
			PlayTicTacToe::m_TTTNodeResult.stone.col = pTTTNode->stone.col;
			PlayTicTacToe::m_TTTNodeResult.stone.magic_code = pTTTNode->stone.magic_code;
			PlayTicTacToe::m_TTTNodeResult.value = pTTTNode->value;
		}
		else {
			PlayTicTacToe::m_TTTNodeResult.stone.row = -1;
			PlayTicTacToe::m_TTTNodeResult.stone.col = -1;
			PlayTicTacToe::m_TTTNodeResult.stone.magic_code = -1;
		}
		return 0;
	}

	//���庯��ģ�壬���ڳ�Ա�����̻߳�
	template <typename TYPE, TicTacToeNode* (TYPE::*StandardAlphaBeta)(MyObjects::TicTacToe*, short alpha, short beta)>
	DWORD WINAPI DoThreadStandardAlphaBeta(LPVOID lpParameter)
	{
		TicTacToeNode* pTTTNode = NULL;
	
		TYPE* objPlayTTT = (TYPE*)lpParameter;
		pTTTNode = objPlayTTT->StandardAlphaBeta(objPlayTTT->GetTTT(), objPlayTTT->MIN_VALUE, objPlayTTT->MAX_VALUE);
		if (pTTTNode) {//�����������
			PlayTicTacToe::m_TTTNodeResult.stone.row = pTTTNode->stone.row;
			PlayTicTacToe::m_TTTNodeResult.stone.col = pTTTNode->stone.col;
			PlayTicTacToe::m_TTTNodeResult.stone.magic_code = pTTTNode->stone.magic_code;
			PlayTicTacToe::m_TTTNodeResult.value = pTTTNode->value;
		}
		else {
			PlayTicTacToe::m_TTTNodeResult.stone.row = -1;
			PlayTicTacToe::m_TTTNodeResult.stone.col = -1;
			PlayTicTacToe::m_TTTNodeResult.stone.magic_code = -1;
		}
		return 0;
	}

	//���庯��ģ�壬���ڳ�Ա�����̻߳�
	template <typename TYPE, TicTacToeNode* (TYPE::*NegamaxAlphaBeta)(MyObjects::TicTacToe*, short alpha, short beta)>
	DWORD WINAPI DoThreadNegamaxAlphaBeta(LPVOID lpParameter)
	{
		TicTacToeNode* pTTTNode = NULL;
	
		TYPE* objPlayTTT = (TYPE*)lpParameter;
		pTTTNode = objPlayTTT->NegamaxAlphaBeta(objPlayTTT->GetTTT(), objPlayTTT->MIN_VALUE, objPlayTTT->MAX_VALUE);
		if (pTTTNode) {//�����������
			PlayTicTacToe::m_TTTNodeResult.stone.row = pTTTNode->stone.row;
			PlayTicTacToe::m_TTTNodeResult.stone.col = pTTTNode->stone.col;
			PlayTicTacToe::m_TTTNodeResult.stone.magic_code = pTTTNode->stone.magic_code;
			PlayTicTacToe::m_TTTNodeResult.value = pTTTNode->value;
		}
		else {
			PlayTicTacToe::m_TTTNodeResult.stone.row = -1;
			PlayTicTacToe::m_TTTNodeResult.stone.col = -1;
			PlayTicTacToe::m_TTTNodeResult.stone.magic_code = -1;
		}
		return 0;
	}

	class PlayTicTacToe {
	public:
		PlayTicTacToe(MyObjects::TicTacToe& ttt);
		~PlayTicTacToe();

		void DoStandardMinimax() {
			m_bResult = false;
			m_hMinimaxThread = CreateThread(NULL, 0, DoThreadStandardMinimax<PlayTicTacToe, &PlayTicTacToe::StandardMinimax>, this, 0, NULL);
			WaitForSingleObject(m_hMinimaxThread, INFINITE);
			CloseHandle(m_hMinimaxThread);
			m_hMinimaxThread = NULL;
			m_bResult = true; //�õ������־
		}

		void DoNegamaxMinimax() {
			m_bResult = false;
			m_hMinimaxThread = CreateThread(NULL, 0, DoThreadNegamaxMinimax<PlayTicTacToe, &PlayTicTacToe::NegamaxMinimax>, this, 0, NULL);
			WaitForSingleObject(m_hMinimaxThread, INFINITE);
			CloseHandle(m_hMinimaxThread);
			m_hMinimaxThread = NULL;
			m_bResult = true; //�õ������־
		}

		void DoStandardAlphaBeta() {
			m_bResult = false;
			m_hMinimaxThread = CreateThread(NULL, 0, DoThreadStandardAlphaBeta<PlayTicTacToe, &PlayTicTacToe::StandardAlphaBeta>, this, 0, NULL);
			WaitForSingleObject(m_hMinimaxThread, INFINITE);
			CloseHandle(m_hMinimaxThread);
			m_hMinimaxThread = NULL;
			m_bResult = true; //�õ������־
		}

		void DoNegamaxAlphaBeta() {
			m_bResult = false;
			m_hMinimaxThread = CreateThread(NULL, 0, DoThreadNegamaxAlphaBeta<PlayTicTacToe, &PlayTicTacToe::NegamaxAlphaBeta>, this, 0, NULL);
			WaitForSingleObject(m_hMinimaxThread, INFINITE);
			CloseHandle(m_hMinimaxThread);
			m_hMinimaxThread = NULL;
			m_bResult = true; //�õ������־
		}

		TicTacToeNode* StandardMinimax(MyObjects::TicTacToe* pTTT); //ʹ��Standard Minimax�㷨����������ӣ�����λ����ֵ����ڷ��صĽṹ�У������������ͷſռ�
		TicTacToeNode* NegamaxMinimax(MyObjects::TicTacToe* pTTT); //ʹ��Negamax Minimax�㷨����������ӣ�����λ����ֵ����ڷ��صĽṹ�У������������ͷſռ�

		TicTacToeNode* StandardAlphaBeta(MyObjects::TicTacToe* pTTT, short alpha, short beta); //ʹ��Standard alpha-beta�㷨����������ӣ�����λ����ֵ����ڷ��صĽṹ�У������������ͷſռ�
		TicTacToeNode* NegamaxAlphaBeta(MyObjects::TicTacToe* pTTT, short alpha, short beta); //ʹ��Negamax alpha-beta�㷨����������ӣ�����λ����ֵ����ڷ��صĽṹ�У������������ͷſռ�

		MyObjects::TicTacToe* GetTTT() {return m_pTTT;}
		HANDLE GetMinimaxThread() {return m_hMinimaxThread;}
		void ClearMinimaxThread() { 
			if (m_hMinimaxThread) {
				CloseHandle(m_hMinimaxThread); 
				m_hMinimaxThread = NULL;
			}
		}

		void Update(MyObjects::TicTacToe& ttt);
		bool GetResult() {
			return m_bResult;
		}

		void ClearResult() {
			m_bResult = false;
		}

	private:
		void Clear();

	public:
		static const short MAX_VALUE = 10000;
		static const short MIN_VALUE = -10000;

		static TicTacToeNode m_TTTNodeResult;

	private:
		MyObjects::TicTacToe* m_pTTT; //�ⲿ�������ĸ������������������

		std::deque<MyAI::TicTacToeNode*> m_dequeTTTNodeSpace; //�ռ�Minimax�����в����Ŀռ䣬���ͷ�

		HANDLE m_hMinimaxThread; //Minimax�߳�
		bool m_bResult;
	};
}