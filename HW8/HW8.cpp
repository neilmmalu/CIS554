#include <iostream>
#include <vector>
#include <stdlib.h>
#include <algorithm>

using namespace std;

typedef char Suit;


class Card {
public:
	int val;
	Suit suit;
	char face;

	Card(char i, Suit j) {
		face = i;
		suit = j;
		setVal(i);
	}

	void setVal(Suit j);

	friend ostream& operator<<(ostream& str, Card& c);
};

void Card::setVal(Suit f) {
	if (f == 'K') { val = 13; return; }
	if (f == 'Q') { val = 12; return; }
	if (f == 'J') { val = 11; return; }
	if (f == 'A') { val = 1; return; }

	val = f - '0';
}

ostream& operator<<(ostream& str, Card& c) {
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
    }
    return str;
}

class Deck{
public:
    vector<Card*> deck;
    Deck(){
        for(int i = 2; i <= 13; i++){
            if(i < 11){
                deck.push_back(new Card('0' + i, 'D'));
                deck.push_back(new Card('0' + i, 'S'));
                deck.push_back(new Card('0' + i, 'C'));
                deck.push_back(new Card('0' + i, 'H'));
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
            else if(i == 13){
                deck.push_back(new Card('K', 'D'));
                deck.push_back(new Card('K', 'S'));
                deck.push_back(new Card('K', 'C'));
                deck.push_back(new Card('K', 'H'));
            }
            else{
                deck.push_back(new Card('A', 'D'));
                deck.push_back(new Card('A', 'S'));
                deck.push_back(new Card('A', 'C'));
                deck.push_back(new Card('A', 'H'));
            }
        }
 
    }

    void shuffle(){ random_shuffle(deck.begin(), deck.end()); }

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
        str << *it << " ";
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
    D->shuffle();
    cout << "***************DECK AFTER SHUFFLE***************" << endl;

    

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
        (*it1)->hand.push_back(D->removeCard());
        it1++;   
    }

    cout << "***************AFTER CARDS ARE DEALT***************" << endl;

    for(auto p: players){
        cout << "Cards for player " << p->index << endl;
        cout << p << endl;
    }

    //Game loop
    while(numActivePlayers > 1){

        for(auto p: players){
            cout << "Hand " << p->index << endl << endl;
            cout << p << endl;
        }
        cout << endl;

        //create the table
        vector<Card> table;
        for(auto p : players){
            table.push_back(p->removeCard());
        }

        int min = INT_MAX;
        for(int i = 0; i < n; i++){
            cout << "Table " << i << endl;
            cout << table[i] << endl;
            cout << endl;

            if(table[i].val < min) min = table[i].val;

            //Case of tie
            else if(table[i].val == min){

            }
        }

        //individual battle

        
    }



    //If user wants to play again, the dealer will shift to the next player
    cout << "Play again? Y for yes." << endl;
    char c;
    cin >> c;
    if(c == 'Y' || c == 'y'){
        game(n, x+1);
    }
}

int main(){
    cout << "Number of players: " << endl;
    int n;
    cin >> n;

    cout << "Which player is the dealer?" << endl;
    int x;
    cin >> x;


    game(n, x); 
    return 0;
}