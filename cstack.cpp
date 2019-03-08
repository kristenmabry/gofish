#include <iostream>
#include "cstack.h"
#include "csimplelistcard.h"
#include "csimplelist.h"
#include "ccard.h"
using namespace std;


bool CStack::Pop(CCard &currCard)
{
	if ( !IsEmpty() )
		{
		m_cards.GetItem(0, currCard);
		m_cards.Remove(0);
		return true;
		}
	else
		{
		return false;
		}
}

bool CStack::Peek(CCard currCard)
{
	if ( !IsEmpty() )
		{
		m_cards.GetItem(0, currCard);
		return true;
		}
	else
		{
		return false;
		}
}



CStack* ShuffleDeck()
{
	CSimpleList diamonds;
	CSimpleList clubs;
	CSimpleList hearts;
	CSimpleList spades;

	CStack* deck = new CStack;

	for (int i = 1; i < 14; i++)
		{
		diamonds.Insert(i-1, i);
		clubs.Insert(i-1, i);
		hearts.Insert(i-1, i);
		spades.Insert(i-1, i);
		}


	CSimpleList array[] = {diamonds, clubs, hearts, spades};
	for (int i = 0; i < 52; i++)
		{
		// get random suit 
		int suit;
		do {
			suit = rand() % 4;
		} while (array[suit].GetNumItems() == 0);

		// find num items left and choose random from list
		int numItems = array[suit].GetNumItems();
		int num = (rand() % numItems);
		int numDrawn;
		array[suit].GetItem(num, numDrawn);
		
		// create new card and add to top of deck
		CCard newCard(suit, numDrawn);
		deck->Push(newCard);

		// remove from appropriate list
		array[suit].Remove(num);
		}

	return deck;
		
} // end of "Shuffle Deck"
