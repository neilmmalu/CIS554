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