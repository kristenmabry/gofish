#ifndef CPLAYER_HEADER
#define CPLAYER_HEADER

#include "ccard.h"
#include "csimplelistcard.h"

class CStack;

class CPlayer
{
public:
	CPlayer(): m_numPairs(0), m_numCards(0), m_numAmounts(), m_asked(), m_dontAsk() {}

	int Search(int number); // check if go fish
	CCard* GetCards(int number, int& selected); // select cards to give to player or if match
	void GoFish(CStack* deck);
	int CheckPair(); //return char of pair
	bool CheckEmpty(CStack* deck); // if hand & deck empty, return true
	void UpdateAskList(int number);
	void RemoveAskList(int number) { m_asked[number-1] = false;
					m_dontAsk[number-1] = true; };
	void ResetAskList();
	void AddToHand(CCard* newCards, int numCards);
	int CompareLists();
	void DisplayCards();

private:
	CSimpleListCard m_hand;
	int m_numAmounts[13];
	bool m_asked[13];
	bool m_dontAsk[13];
	int m_numPairs;
	int m_numCards;

};


#endif  // CSTACK_HEADER
