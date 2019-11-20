#include <iostream>
#include <vector>

typedef char Suit;

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
    }

    void addToHand(Card card);
    Card removeCard();

};

void Player::addToHand(Card card){
    hand.push_back(card);
    numCards++;
}

Card Player::removeCard(){
    Card c = hand[hand.size()-1];
    hand.pop_back();
    numCards--;
    if(numCards < 5) active = false;
    return c;
}

class Deck{
public:
    vector<Card> deck;
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

};

class Card{
public:
    int val;
    Suit suit;
    char face;

    Card(char i, Suit j){
        face = i;
        suit = j;
        setVal(i);
    }

    void setVal(Suit j);

    friend ostream& operator<<(ostream& str, Card &c);
};

void Card::setVal(char f){
    if(f == 'K') { val = 13; return; }
    if(f == 'Q') { val = 12; return; }
    if(f == 'J') { val = 11; return; }
    if(f == 'A') { val =  1; return; }

    val = f - '0';
}

ostream& Card::operator<<(ostream& str, Card &c){
    str << face << suit;
    return str;
}

void battle(int n){

    //Setting up the players
    int numPlayers = n;
    int numActivePlayers = n;

    vector<Player> players;
    for(int i = 1; i <= n; i++){
        Player player = new Player(i);
        players.push_back(player);
    }


    //Setting up the deck of cards
    Deck D = new Deck();

    while(numActivePlayers > 1){

    }
}

int main(){
    cout << "Number of players: " << endl;
    int n;
    cin >> n;
    battle(n); 
    return 0;
}