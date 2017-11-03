/*
	Programmed by Xiaoqin Du, 383979583@qq.com
	School of Math and Computer Science, 
	Wuhan Textile University
*/

#include "stdafx.h"

#include "PlayTicTacToe.h"

MyAI::TicTacToeNode MyAI::PlayTicTacToe::m_TTTNodeResult;

MyAI::PlayTicTacToe::PlayTicTacToe(MyObjects::TicTacToe& ttt)
{
	m_pTTT = new MyObjects::TicTacToe(ttt);
	m_hMinimaxThread = NULL;
	m_bResult = false;
}

MyAI::PlayTicTacToe::~PlayTicTacToe()
{
	Clear();
}

void MyAI::PlayTicTacToe::Clear()
{
	std::deque<MyAI::TicTacToeNode*>::iterator iter;

	for (iter = m_dequeTTTNodeSpace.begin(); iter < m_dequeTTTNodeSpace.end(); iter++) {
		delete *iter;
	}
	m_dequeTTTNodeSpace.clear();

	if (m_pTTT)
		delete m_pTTT;
	m_pTTT = NULL;

	if (m_hMinimaxThread)
		CloseHandle(m_hMinimaxThread);
	m_hMinimaxThread = NULL;
	m_bResult = false;
}

void MyAI::PlayTicTacToe::Update(MyObjects::TicTacToe& ttt)
{
	if (*m_pTTT == ttt)
		return;

	Clear();
	m_pTTT = new MyObjects::TicTacToe(ttt);
}

MyAI::TicTacToeNode* MyAI::PlayTicTacToe::StandardMinimax(MyObjects::TicTacToe* pTTT)
{
	MyAI::TicTacToeNode* pTTTNode; //本函数分配的空间，将置于m_dequeTTTNodeSpace中，析构函数会释放
	MyAI::TicTacToeNode* pTTTNodeTmp; //本函数递归调用分配的空间，同pTTTNode一样处理

	std::deque<MyObjects::TicTacToeStone*>* pTTTStones; //GetAllPossibleMoves返回的空间，本函数（调用者）负责释放
	std::deque<MyObjects::TicTacToeStone*>::iterator iter;

	MyObjects::TicTacToe* pTTTTmp; //本函数会立即释放该空间
	
	pTTTNode = new MyAI::TicTacToeNode();
	m_dequeTTTNodeSpace.push_back(pTTTNode);

	pTTTNode->stone.row = -1;
	pTTTNode->stone.col = -1;
	pTTTNode->stone.magic_code = -1;

	short value = pTTT->IsTerminalState();
	if (value != MyObjects::TicTacToe::NONTERMINAL) {//到达终端节点
		pTTTNode->value = value;

		return pTTTNode;
	}

	pTTTStones = pTTT->GetAllPossibleMoves(); //需释放空间，函数最后会释放它
	if (pTTT->GetPlayer()) {//X Player
		pTTTNode->value = MIN_VALUE;
		for (iter = pTTTStones->begin(); iter < pTTTStones->end(); iter++) {
			pTTTTmp = new MyObjects::TicTacToe(*pTTT);
			pTTTTmp->Play((*iter)->row, (*iter)->col);
			pTTTTmp->ChgPlayer();
			pTTTNodeTmp = StandardMinimax(pTTTTmp);
			if (pTTTNode->value < pTTTNodeTmp->value) {
				pTTTNode->stone.row = (*iter)->row;
				pTTTNode->stone.col = (*iter)->col;
				pTTTNode->stone.magic_code = (*iter)->magic_code;
				pTTTNode->value = pTTTNodeTmp->value;
			}
			delete pTTTTmp;
		}
	}
	else {//O Player
		pTTTNode->value = MAX_VALUE;
		for (iter = pTTTStones->begin(); iter < pTTTStones->end(); iter++) {
			pTTTTmp = new MyObjects::TicTacToe(*pTTT);
			pTTTTmp->Play((*iter)->row, (*iter)->col);
			pTTTTmp->ChgPlayer();
			pTTTNodeTmp = StandardMinimax(pTTTTmp);
			if (pTTTNode->value > pTTTNodeTmp->value) {
				pTTTNode->stone.row = (*iter)->row;
				pTTTNode->stone.col = (*iter)->col;
				pTTTNode->stone.magic_code = (*iter)->magic_code;
				pTTTNode->value = pTTTNodeTmp->value;
			}
			delete pTTTTmp;
		}
	}

	//释放GetAllPossibleMoves返回的空间
	for (iter = pTTTStones->begin(); iter < pTTTStones->end(); iter++) {
		delete *iter;
	}
	pTTTStones->clear();
	delete pTTTStones;

	return pTTTNode;
}

MyAI::TicTacToeNode* MyAI::PlayTicTacToe::NegamaxMinimax(MyObjects::TicTacToe* pTTT)
{
	MyAI::TicTacToeNode* pTTTNode; //本函数分配的空间，将置于m_dequeTTTNodeSpace中，析构函数会释放
	MyAI::TicTacToeNode* pTTTNodeTmp; //本函数递归调用分配的空间，同pTTTNode一样处理

	std::deque<MyObjects::TicTacToeStone*>* pTTTStones; //GetAllPossibleMoves返回的空间，本函数（调用者）负责释放
	std::deque<MyObjects::TicTacToeStone*>::iterator iter;

	MyObjects::TicTacToe* pTTTTmp; //本函数会立即释放该空间
	
	pTTTNode = new MyAI::TicTacToeNode();
	m_dequeTTTNodeSpace.push_back(pTTTNode);

	pTTTNode->stone.row = -1;
	pTTTNode->stone.col = -1;
	pTTTNode->stone.magic_code = -1;

	short value = pTTT->IsTerminalState();
	if (value != MyObjects::TicTacToe::NONTERMINAL) {//到达终端节点
		if (pTTT->GetPlayer())
			pTTTNode->value = value;
		else
			pTTTNode->value = -value;

		return pTTTNode;
	}

	pTTTStones = pTTT->GetAllPossibleMoves(); //需释放空间，函数最后会释放它
	pTTTNode->value = MIN_VALUE;
	for (iter = pTTTStones->begin(); iter < pTTTStones->end(); iter++) {
		pTTTTmp = new MyObjects::TicTacToe(*pTTT);
		pTTTTmp->Play((*iter)->row, (*iter)->col);
		pTTTTmp->ChgPlayer();
		pTTTNodeTmp = NegamaxMinimax(pTTTTmp);
		if (pTTTNode->value < - pTTTNodeTmp->value) {
			pTTTNode->stone.row = (*iter)->row;
			pTTTNode->stone.col = (*iter)->col;
			pTTTNode->stone.magic_code = (*iter)->magic_code;
			pTTTNode->value = - pTTTNodeTmp->value;
		}
		delete pTTTTmp;
	}

	//释放GetAllPossibleMoves返回的空间
	for (iter = pTTTStones->begin(); iter < pTTTStones->end(); iter++) {
		delete *iter;
	}
	pTTTStones->clear();
	delete pTTTStones;

	return pTTTNode;
}

MyAI::TicTacToeNode* MyAI::PlayTicTacToe::StandardAlphaBeta(MyObjects::TicTacToe* pTTT, short alpha, short beta)
{
	MyAI::TicTacToeNode* pTTTNode; //本函数分配的空间，将置于m_dequeTTTNodeSpace中，析构函数会释放
	MyAI::TicTacToeNode* pTTTNodeTmp; //本函数递归调用分配的空间，同pTTTNode一样处理

	std::deque<MyObjects::TicTacToeStone*>* pTTTStones; //GetAllPossibleMoves返回的空间，本函数（调用者）负责释放
	std::deque<MyObjects::TicTacToeStone*>::iterator iter;

	MyObjects::TicTacToe* pTTTTmp; //本函数会立即释放该空间
	
	pTTTNode = new MyAI::TicTacToeNode();
	m_dequeTTTNodeSpace.push_back(pTTTNode);

	pTTTNode->stone.row = -1;
	pTTTNode->stone.col = -1;
	pTTTNode->stone.magic_code = -1;

	short value = pTTT->IsTerminalState();
	if (value != MyObjects::TicTacToe::NONTERMINAL) {//到达终端节点
		pTTTNode->value = value;

		return pTTTNode;
	}

	pTTTStones = pTTT->GetAllPossibleMoves(); //需释放空间，函数最后会释放它
	if (pTTT->GetPlayer()) {//X Player
		pTTTNode->value = MIN_VALUE;
		for (iter = pTTTStones->begin(); iter < pTTTStones->end(); iter++) {
			pTTTTmp = new MyObjects::TicTacToe(*pTTT);
			pTTTTmp->Play((*iter)->row, (*iter)->col);
			pTTTTmp->ChgPlayer();
			pTTTNodeTmp = StandardAlphaBeta(pTTTTmp, alpha, beta);
			if (pTTTNode->value < pTTTNodeTmp->value) {
				pTTTNode->stone.row = (*iter)->row;
				pTTTNode->stone.col = (*iter)->col;
				pTTTNode->stone.magic_code = (*iter)->magic_code;
				pTTTNode->value = pTTTNodeTmp->value;
			}
			delete pTTTTmp;
			alpha = max(alpha, pTTTNode->value);
			if (beta <= alpha)
				break;
		}
	}
	else {//O Player
		pTTTNode->value = MAX_VALUE;
		for (iter = pTTTStones->begin(); iter < pTTTStones->end(); iter++) {
			pTTTTmp = new MyObjects::TicTacToe(*pTTT);
			pTTTTmp->Play((*iter)->row, (*iter)->col);
			pTTTTmp->ChgPlayer();
			pTTTNodeTmp = StandardAlphaBeta(pTTTTmp, alpha, beta);
			if (pTTTNode->value > pTTTNodeTmp->value) {
				pTTTNode->stone.row = (*iter)->row;
				pTTTNode->stone.col = (*iter)->col;
				pTTTNode->stone.magic_code = (*iter)->magic_code;
				pTTTNode->value = pTTTNodeTmp->value;
			}
			delete pTTTTmp;
			beta = min(beta, pTTTNode->value);
			if (beta <= alpha)
				break;
		}
	}

	//释放GetAllPossibleMoves返回的空间
	for (iter = pTTTStones->begin(); iter < pTTTStones->end(); iter++) {
		delete *iter;
	}
	pTTTStones->clear();
	delete pTTTStones;

	return pTTTNode;
}

MyAI::TicTacToeNode* MyAI::PlayTicTacToe::NegamaxAlphaBeta(MyObjects::TicTacToe* pTTT, short alpha, short beta)
{
	MyAI::TicTacToeNode* pTTTNode; //本函数分配的空间，将置于m_dequeTTTNodeSpace中，析构函数会释放
	MyAI::TicTacToeNode* pTTTNodeTmp; //本函数递归调用分配的空间，同pTTTNode一样处理

	std::deque<MyObjects::TicTacToeStone*>* pTTTStones; //GetAllPossibleMoves返回的空间，本函数（调用者）负责释放
	std::deque<MyObjects::TicTacToeStone*>::iterator iter;

	MyObjects::TicTacToe* pTTTTmp; //本函数会立即释放该空间
	
	pTTTNode = new MyAI::TicTacToeNode();
	m_dequeTTTNodeSpace.push_back(pTTTNode);

	pTTTNode->stone.row = -1;
	pTTTNode->stone.col = -1;
	pTTTNode->stone.magic_code = -1;

	short value = pTTT->IsTerminalState();
	if (value != MyObjects::TicTacToe::NONTERMINAL) {//到达终端节点
		if (pTTT->GetPlayer())
			pTTTNode->value = value;
		else
			pTTTNode->value = -value;

		return pTTTNode;
	}

	pTTTStones = pTTT->GetAllPossibleMoves(); //需释放空间，函数最后会释放它
	pTTTNode->value = MIN_VALUE;
	for (iter = pTTTStones->begin(); iter < pTTTStones->end(); iter++) {
		pTTTTmp = new MyObjects::TicTacToe(*pTTT);
		pTTTTmp->Play((*iter)->row, (*iter)->col);
		pTTTTmp->ChgPlayer();
		pTTTNodeTmp = NegamaxAlphaBeta(pTTTTmp, -beta, -alpha);
		if (pTTTNode->value < - pTTTNodeTmp->value) {
			pTTTNode->stone.row = (*iter)->row;
			pTTTNode->stone.col = (*iter)->col;
			pTTTNode->stone.magic_code = (*iter)->magic_code;
			pTTTNode->value = - pTTTNodeTmp->value;
		}
		delete pTTTTmp;
		alpha = max(alpha, pTTTNode->value);
		if (beta <= alpha)
			break;
	}

	//释放GetAllPossibleMoves返回的空间
	for (iter = pTTTStones->begin(); iter < pTTTStones->end(); iter++) {
		delete *iter;
	}
	pTTTStones->clear();
	delete pTTTStones;

	return pTTTNode;
}