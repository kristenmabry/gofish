#include <iostream>
#include "cplayer.h"
#include "cstack.h"
#include "ccard.h"
#include "csimplelistcard.h"
using namespace std;

int CPlayer::Search(int number)
{
	int cardsFound = 0;
	for (int i = 0; i < m_numCards; i++)
		{
		CCard search;
		CLStatus success = m_hand.GetItem(i, search);
		if (success == CL_SUCCESS && number == search.GetNumber())
			{
			cardsFound++;
			}
		}
	return cardsFound;
} // end of "Search"



CCard* CPlayer::GetCards(int number, int& selected)
{
	selected = Search(number);
	CCard* matching = new CCard[selected];
	int counter = 0;
	int found = 0;
	while (counter < m_numCards && found < selected)
		{
		CCard cardSearched;
		CLStatus success = m_hand.GetItem(counter, cardSearched);
		if (success == CL_SUCCESS && number == cardSearched.GetNumber())
			{
			// add to list to give
			matching[found] = cardSearched;
			cout << cardSearched << endl;

			// remove from own hand and decrease the number of cards
			m_hand.Remove(counter-found);
			m_numAmounts[cardSearched.GetNumber()-1]--;
			m_numCards--;
			counter--;
			found++;
			}
		counter++;
		}
	return matching;

} // end of "Get Cards"



void CPlayer::GoFish(CStack* deck)
{
	// move card from deck to hand
	CCard newCard;
	deck->Pop(newCard);
	m_hand.Insert(0, newCard);
	// increase hand count and amount count
	m_numCards++;
	m_numAmounts[newCard.GetNumber()-1]++;
} // end of "Go Fish"



int CPlayer::CheckPair()
{
	for (int i = 0 ; i < 13; i++)
		{
		if (m_numAmounts[i] == 4)
			{
			cout << "Pair found: \n";
			int temp;
			CCard* cards = GetCards(i, temp);
			cout << "Score: " << m_numPairs + 1 << endl;
			delete cards;
			m_numPairs++;
			return i + 1;
			}
		}
	
	return 0;
}



bool CPlayer::CheckEmpty(CStack* deck)
{
	if (!m_numCards && deck->IsEmpty())
		{
		return true;
		}
	else if (!m_numCards)
		{
		GoFish(deck);
		}
	return false;
} // end of "Check Empty"



void CPlayer::UpdateAskList(int number)
{
	if (!m_asked[number])
		{
		m_asked[number] = true;
		}
} // end of "Update Ask List"



void CPlayer::AddToHand(CCard* newCards, int numCards)
{
	for (int i = 0; i < numCards; i++)
		{
		m_hand.Insert(0, newCards[i]);
		m_numCards++;
		m_numAmounts[newCards[i].GetNumber()-1]++;
		}
} // end of "AddToHand"



int CPlayer::CompareLists()
{
	int highestAmount = 0;
	int	cardToAsk = 0;
	for (int i = 0; i < 13; i++)
		{
		if (m_numAmounts[i] > highestAmount && m_asked[i])
			{
			highestAmount = m_numAmounts[i];
			cardToAsk = i + 1;
			}
		}

	if (cardToAsk && !m_dontAsk[cardToAsk-1])
		{
		return cardToAsk;
		}
	else
		{
		int newInt;
		do {
			newInt = rand() % 13;
		} while (m_numAmounts[newInt] == 0 && !m_dontAsk[newInt]);
		return newInt+1;
		}
} // end of "Compare Lists"



void CPlayer::DisplayCards()
{
	CCard currCard;
	for (int i = 0; i < m_numCards; i++)
		{
		m_hand.GetItem(i, currCard);
		cout << currCard << endl;
		}
} // end of "Display Cards"



void CPlayer::ResetAskList()
{
	for (int i = 0; i < 13; i++)
		{
		m_dontAsk[i] = false;
		}
}
