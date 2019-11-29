//HW8 Neil Malu
//SU NetID: nemalu	SUID: 635692900

#include <iostream>
#include <vector>
#include <stdlib.h>
#include <algorithm>
#include <fstream>
#include <random>
#include <chrono>

using namespace std;

unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
default_random_engine rng(seed);

class Card {
public:
	int val;
	char suit;
	char face;

	Card(char i, char j) {
		face = i;
		suit = j;
		setVal(i);
	}

	void setVal(char j);

	friend ostream& operator<<(ostream& str, Card& c);
};

void Card::setVal(char f) {
	if (f == 'K') { val = 13; return; }
	if (f == 'Q') { val = 12; return; }
	if (f == 'J') { val = 11; return; }
	if (f == 'A') { val = 1; return; }
	if (f == 'X') { val = 10; return; }

	val = f - '0';
}

ostream& operator<<(ostream& str, Card& c) {
	if (c.face == 'X') {
		str << "10" << c.suit;
		return str;
	}

	str << c.face << c.suit;
	return str;
}

class Player{
public:
    int index;
    int numCards;
    bool active;
    bool isDealer;
    vector<Card> hand;

    Player(int i){
        numCards = 0;
        index = i;
        active = true;
        isDealer = false;
    }

    void addToHand(Card card);
    Card removeCard();
	void myShuffle() { shuffle(begin(hand), end(hand), rng); }
    friend ostream& operator<<(ostream& str, Player &P);
};

void Player::addToHand(Card card){
    hand.push_back(card);
    numCards++;
}

Card Player::removeCard(){
    Card c = hand[hand.size()-1];
    hand.pop_back();
    numCards--;
    return c;
}

ostream& operator<<(ostream& str, Player& P) {
    auto it = P.hand.begin();
    while(it != P.hand.end()){
        str << *it << " ";
		it++;
    }
    return str;
}

class Deck{
public:
    vector<Card*> deck;
    Deck(){
        for(int i = 1; i <= 13; i++){
			if (i == 1) {
				deck.push_back(new Card('A', 'D'));
				deck.push_back(new Card('A', 'S'));
				deck.push_back(new Card('A', 'C'));
				deck.push_back(new Card('A', 'H'));
			}
            else if(i < 10){
                deck.push_back(new Card('0' + i, 'D'));
                deck.push_back(new Card('0' + i, 'S'));
                deck.push_back(new Card('0' + i, 'C'));
                deck.push_back(new Card('0' + i, 'H'));
            }
			else if (i == 10) {
				deck.push_back(new Card('X', 'D'));
				deck.push_back(new Card('X', 'S'));
				deck.push_back(new Card('X', 'C'));
				deck.push_back(new Card('X', 'H'));
			}
            else if(i == 11){
                deck.push_back(new Card('J', 'D'));
                deck.push_back(new Card('J', 'S'));
                deck.push_back(new Card('J', 'C'));
                deck.push_back(new Card('J', 'H'));
            }
            else if(i == 12){
                deck.push_back(new Card('Q', 'D'));
                deck.push_back(new Card('Q', 'S'));
                deck.push_back(new Card('Q', 'C'));
                deck.push_back(new Card('Q', 'H'));
            }
            else {
                deck.push_back(new Card('K', 'D'));
                deck.push_back(new Card('K', 'S'));
                deck.push_back(new Card('K', 'C'));
                deck.push_back(new Card('K', 'H'));
            }
        }
 
    }

    void myShuffle(){ shuffle(begin(deck), end(deck), rng); }

    Card removeCard();

    friend ostream& operator<<(ostream &str, Deck &D);

};

Card Deck::removeCard(){
    Card* c = deck[deck.size()-1];
    deck.pop_back();
    return *c;
}

ostream& operator<<(ostream &str, Deck &D){
    auto it = D.deck.begin();
    while(it != D.deck.end()){
        str << **it << " ";
		it++;
    }
    return str;
}

ostream& operator<<(ostream& str, vector<Card>& V) {
	auto it = V.begin();
	while (it != V.end()) {
		str << *it << " ";
		it++;
	}
	return str;
}


/*
*   n : number of players 
*   x : player index who is the dealer
*/
void game(int n, int x){

    //Setting up the deck of cards
    Deck* D = new Deck();

    cout << "***************DECK BEFORE SHUFFLE***************" << endl;
    cout << *D << endl;
    D->myShuffle();
    cout << "***************DECK AFTER SHUFFLE***************" << endl;
    cout << *D << endl;
    

    if(x < 1) return;

    if(x > n) x = 1;

    //Setting up the players
    int numPlayers = n;
    int numActivePlayers = n;

    vector<Player*> players;
    for(int i = 1; i <= n; i++){
        Player* player = new Player(i);
        if(i == x){
            player->isDealer = true;
        } 
        players.push_back(player);
    }




    //Dealing cards
    auto it1 = players.begin();
    while(!(*it1)->isDealer) it1++;
    it1++;
    while(!D->deck.empty()){
        if(it1 == players.end()) it1 = players.begin();
        (*it1)->addToHand(D->removeCard());
        it1++;   
    }

    cout << "***************AFTER CARDS ARE DEALT***************" << endl;

    for(auto p: players){
        cout << "Cards for player " << p->index << endl;
        cout << *p << endl;
    }

	cout << endl;
    //Game loop
    while(numActivePlayers > 1){

        for(auto p: players){
            cout << "Hand " << p->index << endl;
            cout << *p << endl << endl;
        }
        cout << endl;

        //create the table
        vector<Card> table;

		//Need to figure out how to offset inactive players in the table
		//Probably a dummy card with val = 0
        for(auto p : players){
			if (p->active) table.push_back(p->removeCard());
			else table.push_back(Card('0','0'));
        }

		//Find the minimum in the table
        int min = INT_MAX;
		int minIndex;
		bool tie = false;
		int tieIndex;
        for(int i = 0; i < n; i++){
            cout << "Table " << (i+1) << endl;
            if(players[i]->active) cout << table[i] << endl;
            cout << endl;

            if(!players[i]->active) continue;

			if (table[i].val < min && table[i].val != 0) {
				min = table[i].val;
				minIndex = i;
			}

            //Case of tie
            else if(table[i].val == min){

				tie = true;
				tieIndex = i;
				//Need to add all the tie cards except first one, to the winners hands
            }


        }

		if (tie) {
			vector<Card> tie1;
			vector<Card> tie2;

			tie1.push_back(table[minIndex]);
			tie1.push_back(players[minIndex]->removeCard());
			tie1.push_back(players[minIndex]->removeCard());

			tie2.push_back(table[tieIndex]);
			tie2.push_back(players[tieIndex]->removeCard());
			tie2.push_back(players[tieIndex]->removeCard());

			for (auto p : players) {
				cout << "Hand " << p->index << endl;
				if (p->active) cout << *p << endl << endl;
			}
			cout << endl;

			for (int j = 0; j < n; j++) {

				cout << "Table " << (j+1) << endl;
				if (!players[j]->active) continue;
				if (j == minIndex) {
					cout << tie1 << endl;
				}
				else if (j == tieIndex) {
					cout << tie2 << endl;
				}
				else {
					cout << table[j] << endl;
				}
				cout << endl;
			}

			Card c1 = tie1[tie1.size() - 1];
			Card c2 = tie2[tie2.size() - 1];

			if (c2.val < c1.val) minIndex = tieIndex;

			players[minIndex]->addToHand(tie1[1]);
			players[minIndex]->addToHand(tie1[2]);
			players[minIndex]->addToHand(tie2[1]);
			players[minIndex]->addToHand(tie2[2]);
		}

        //MinIndex is the index of the lowest card
        //Need to add all of the cards in the table to winner
        //Check if any player is below 5 cards and change active = false
		for (auto c : table) {
			if(c.val != 0) players[minIndex]->addToHand(c);
		}
        players[minIndex]->myShuffle();

        for(auto p : players){
            if(p->active && p->numCards < 5){
                p->active = false;
                numActivePlayers--;
                while(p->numCards > 0){
                    players[minIndex]->addToHand(p->removeCard());
                }
            }
        }

		players[minIndex]->myShuffle();

        
    }

	for (auto p : players) {
		cout << "Hand " << p->index << endl;
		cout << *p << endl << endl;
	}

	for (auto p : players) {
		if (p->active) cout << "Player " << p->index << " wins!" << endl;
	}


	//Need to delete deck, players and all pointers to avoid mem leaks
	for (auto c : D->deck) {
		delete c;
	}
	delete D;

	for (auto p : players) {
		delete p;
	}
}

int main(){
    cout << "Number of players: " << endl;
    int n;
    cin >> n;

	if (n > 7 || n < 2) return 0;

    cout << "Which player is the dealer?" << endl;
    int x;
    cin >> x;


	//Redirect std::cout to the output file
	ofstream out("data1.txt");
	auto* outbuff = cout.rdbuf();
	cout.rdbuf(out.rdbuf());


    game(n, x); 

    return 0;
}