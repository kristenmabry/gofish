#include <iostream>
#include <cstring>
#include <cstdlib>
#include "ccard.h"
using namespace std;

	CCard::CCard(int suit, int num)
{
	m_suitInt = suit;
	m_numberInt = num;
	switch (suit)
		{
		case 0:
			m_suit = "Diamonds";
			break;
		case 1:
			m_suit = "Clubs";
			break;
		case 2:
			m_suit = "Hearts";
			break;
		case 3:
			m_suit = "Spades";
			break;
		}

	switch (num)
		{
		case 1:
			m_number = "Ace";
			break;
		case 11:
			m_number = "Jack";
			break;
		case 12:
			m_number = "Queen";
			break;
		case 13:
			m_number = "King";
			break;
		default:
			m_number = to_string(num);
			break;
		}

} // end of ctor



	CCard::CCard()
{
	m_number = "Queen";
	m_suit = "Diamonds";
	m_suitInt = 0;
	m_numberInt = 12;
} // end of default ctor



CCard& CCard::operator=(const CCard& rhs)
{
	if (&rhs != this)
		{
		m_number = rhs.m_number;
		m_suit = rhs.m_suit;
		m_numberInt = rhs.m_numberInt;
		m_suitInt = rhs.m_suitInt;
		}
	return *this;
} // end of "operator="



ostream& operator<<(ostream& outStream, const CCard& disp)
{
	outStream << disp.m_number << " of " << disp.m_suit;
	return outStream;
} // end of "operator<<"
