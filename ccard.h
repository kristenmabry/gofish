#ifndef CCARD_HEADER 
#define CCARD_HEADER

#include <cstring>
using namespace std;

class CCard
{
public:
	CCard(int suit, int num);
	CCard();

	int GetSuit() { return m_suitInt; }
	int GetNumber() { return m_numberInt; }
	
	friend ostream& operator<<(ostream& outStream, const CCard& disp);
	CCard& operator=(const CCard& rhs);

private:
	string m_suit;
	string m_number;
	int m_suitInt;
	int m_numberInt;
};


#endif  // CCARD_HEADER 
