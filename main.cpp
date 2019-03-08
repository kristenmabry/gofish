#include <iostream>
#include <cstdlib> // rand
#include "cstack.h"
#include "ccard.h"
#include "cplayer.h"
using namespace std;

int PickCard(CPlayer& player);
void DisplayCardAsked(int number);

int main()
{
	srand(time(NULL));
	CStack* deck = ShuffleDeck();

	CPlayer user;
	CPlayer cp;

	// deal cards
	for (int i = 0; i < 5; i++)
		{
		user.GoFish(deck);
		cp.GoFish(deck);
		}
	user.CheckPair();
	cp.CheckPair();

	cout << endl << "Cp" << endl;
	cp.DisplayCards();
	cout << endl << endl;


	bool gameOver = false;
	while (!gameOver)
	{
	// while player's turn
	bool match = true;
	while (match && !gameOver)
		{
		// pick a card to ask for
		cout << "CP:\n";
		cp.DisplayCards();
		cout << endl;
		int cardAsked = PickCard(user);
		match = cp.Search(cardAsked); 
		// take from player or draw from deck
		if (match)
			{
			int change;
			cout << "\nYou received from the computer:\n";
			CCard* newCards = cp.GetCards(cardAsked, change);
			cout << endl;
			user.AddToHand(newCards, change);
			}
		else
			{
			cout << "The computer does not have that card. Go fish!\n";
			user.GoFish(deck);
			cp.ResetAskList();
			}
		// check for match and empty hand
		int pair = user.CheckPair();	
		gameOver = user.CheckEmpty(deck);
		if (gameOver)
			{
			cout << "Game over!\n";
			break;
			}
		// if not match, add number of card to list of cards that cp knows
		// that player has
		if (!pair)
			{
			cp.UpdateAskList(cardAsked);
			}
		}

	// while computer turn
	match = true;
	while (match && !gameOver)
		{
		// see if list of player cards matches computer's cards
		cout << "\nIt's now the computer's turn.\n";
		int cardAsked = cp.CompareLists();
		DisplayCardAsked(cardAsked);
		match = user.Search(cardAsked);
		//	take from player or draw from deck
		if (match)
			{
			int change;
			cout << "You gave the computer: ";
			CCard* newCards = user.GetCards(cardAsked, change);
			cout << endl;
			cp.AddToHand(newCards, change);
			cp.RemoveAskList(cardAsked);
			}
		else
			{
			cout << "\nYou don't have those cards. The computer went fishing.\n\n";
			cp.GoFish(deck);
			}
		// check for  match and empty hand
		int pair = cp.CheckPair();	
		gameOver = cp.CheckEmpty(deck);
		if (gameOver)
			{
			cout << "Game over!\n";
			break;
			}
		}
	}
	return 1;
} // end of "main"



int PickCard(CPlayer& player)
{
	char response;
	cout << "Your cards:" << endl;
	player.DisplayCards();
	cout << "Which card would you like to ask for? ";
	cin >> response;

	response = toupper(response);
	int card = response;
	if (card < 58)
		{
		card -= 48;
		}
	else if (card == 'A')
		{
		card = 1;
		}
	else if (card == 'J')
		{
		card = 11;
		}
	else if (card == 'Q')
		{
		card = 12;
		}
	else if (card == 'K')
		{
		card = 13;
		}
	
	if (card == 1)
		{
		cin.get(response);
		if (response == '0')
			{
			card = 10;
			}
		}

	return card;
} // end of "Pick Card"



void DisplayCardAsked(int number)
{
	cout << "The computer asked you for ";
	if (number > 1 && number < 11)
		{
		cout << number << "s\n";
		}
	else
		{
		switch (number)
			{
			case 1:
				cout << "Aces\n";
				break;
			case 11:
				cout << "Jacks\n";
				break;
			case 12:
				cout << "Queens\n";
				break;
			case 13:
				cout << "Kings\n";
				break;
			}
		}
}
