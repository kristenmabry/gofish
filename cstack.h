#ifndef CSTACK_HEADER
#define CSTACK_HEADER

#include "ccard.h"
#include "csimplelistcard.h"


class CStack
{
public:
	void Push(CCard &newCard) { m_cards.Insert(0, newCard); }
	bool Pop(CCard &currCard);
	bool Peek(CCard currCard);
	bool IsEmpty() { return m_cards.IsEmpty(); }

private:
	CSimpleListCard m_cards;

};

CStack* ShuffleDeck();

#endif  // CSTACK_HEADER
