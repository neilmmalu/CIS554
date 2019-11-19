#include <iostream>
#include <vector>

typedef char Suit;

class Player{
    int index;
    int numCards;
    bool active;
    vector<Card> hand;

    Player(int i){
        index = i;
        active = true;
    }

};

class Deck{
    vector<Card> deck;
    Deck(){
        for(int i = 1; i <= 13; i++){
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
            else{
                deck.push_back(new Card('K', 'D'));
                deck.push_back(new Card('K', 'S'));
                deck.push_back(new Card('K', 'C'));
                deck.push_back(new Card('K', 'H'));
            }
        }

        shuffle();   
    }

    void shuffle();

};

void Deck::shuffle(){
    random_shuffle(deck.begin(), deck.end());
}



class Card{
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
    if(f == 'A') { val = 1; return; }

    val = f - '0';
}

ostream& Card::operator<<(ostream& str, Card &c){
    str << face << suit;
    return str;
}

int main(){
    return 0;
}