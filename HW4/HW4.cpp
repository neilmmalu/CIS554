//HW4: Due Sunday (Oct. 13) at 11:59PM
//Implement functions of class linked_list, class node,  class bag, class item
//All member functions listed need to be implemented.
//You will also need to implement initializer_list, and the needed overloaded operators
//If a class needs destructor, then you need to implement destructor, copy constructor, move constructor, Lvalue operator= and Rvalue operator= for the class
//You will also need to overload operator<< for vector, bag, linked_list, ThreeD using tempalte
//See the sample output for formats when implementing operator<< for all classes
#include <iostream>
#include <stdlib.h>
#include <string>
#include <list>
#include <vector>
using namespace std;

template <class T> class ThreeD {
public:
    T ht;
    T wid;
    T dep;
    ThreeD() { ht = wid = dep = 0; }
    ThreeD(T i) { ht = wid = dep = i; }
    ThreeD(T a, T b, T c) { ht = a; wid = b; dep = c; }
    T getVol(){return ht*wid*dep;}
    //two objects are equal if their getVol() return the same value.
    bool operator==(const ThreeD<T> &t){ return getVol() == t.getVol(); }
};

template <class T> class node {
public:
    T value;
    node<T> * next;
    node<T> * previous;
    node<T>() { next = nullptr; previous = nullptr; }
    node<T>(T v) { value = v; next = nullptr; previous = nullptr; }
};
template <class T> class linked_list {
public:
    node<T> * head; //position of first node
    node<T> * tail; //position of last node
    linked_list() {  head = tail = nullptr; }
    void push_front(T t);
    void push_back(T t);
	void insert_empty(T t);
    linked_list(const initializer_list<T> &I);

};

/*
*
*LINKEDLIST MEMBER FUNCTIONS
*
*/
template<class T> void linked_list<T>::push_front(T t) {
    if(!head) { insert_empty(t); return; }

    node<T> newNode = new node<T>(t);
	newNode->previous = nullptr;
	newNode->next = head;
	head->previous = newNode;
	head = newNode;
}

template<class T> void linked_list<T>::push_back(T t) {
    if(!head) { insert_empty(t); return; }

    node<T> newNode = new node<T>(t);
	newNode->next = nullptr;
	newNode->previous = tail;
	tail->next = newNode;
	tail = newNode;
}

template<class T> void linked_list<T>::insert_empty(T t){
    head = new node<T>(t);
    tail = head;
}

template<class T> linked_list<T>::linked_list(const initializer_list<T> &I){
    auto it = I.end() - 1; 

    while (it != I.begin() - 1) {
        Node<T> * p = new Node<T>(*it);
        p->next = head;
        if(!head) tail = head;
        else head->previous = p;
        head = p;
        it--;
    }
}



template <class X>
class item {
public:
    X data;
    item<X> *next;
    item<X> *previous;
    item<X>(X d) { data = d; next = nullptr; previous = nullptr; }
    // bool operator==(const item<X> &I){ return (I.data == data) && (I.next == next) && (I.previous == previous); }
};

template <class X>
class bag {
public:
    item<X> *first; //position of first item
    item<X> *last; //positon of last item
    int num_items;
    int size() { return num_items; }
    bag() { first = nullptr; last = nullptr; num_items = 0; } 
    void push_back(X d);  //insert an item with data d to the back of the bag
    void push_front(X d); //insert an item with data d to the front of the bag

    void insert_empty(X d); //helper function to add to empty bag

    void pop_back(); //delete the last item in the bag
    void pop_front(); //delete the first item in the bag
    X &operator[](int i); //Access bag item with index. 
    X front();   //it returns the data of the first item in the bag.
                 //if (num_items == 0) do nothing;
                 //else return first->data;
    
    X back();  //it returns the data of the last item in the bag
               /*
               if (num_items == 0) do nothing;
               else return last->data;
               */

        
    
    void clear(); //Delete all items in the bag
    item<X> * find(X d); //return nullptr if no match for find or if the bag is empty.
                         //else, return the position of the matched item

    void erase(int index);
    void erase(item<X> * p);
    item<X> * insert(item<X> *p, X d); //insert data d to the position before p and return the position of the inserted item
    bag(const initializer_list<X> &I);
};


/*
*
*BAG MEMBER FUNCTIONS
*
*/

template<class X> void bag<X>::push_back(X d) {
    if(size() == 0) { insert_empty(d); return; }

    item<X> newItem = new item<X>(d);
    newItem->previous = last;
    newItem->next = nullptr;
    last->next = newItem;
    last = newItem;
    num_items++;
}

template<class X> void bag<X>::push_front(X d){
    if(size() == 0) { insert_empty(d); return; }

    item<X> newItem = new item<X>(d);
    newItem->previous = nullptr;
    newItem->next = first;
	first->previous = newItem;
    first = newItem;
    num_items++;
}

template<class X> void bag<X>::insert_empty(X d){
    first = new item<X>(d);
    last = first;
    num_items++;
}

template<class X> void bag<X>::pop_back() {
    if(size() == 0) return;

	item<X>* temp = last;
	last = last->previous;
	last->next = nullptr;
	temp->previous = nullptr;
	delete temp;
	num_items--;
}

template<class X> void bag<X>::pop_front() {
    if(size() == 0) return;

	item<X>* temp = first;
	first = first->next;
	first->previous = nullptr;
	temp->next = nullptr;
	delete temp;
	num_items--;
}

template<class X> X& bag<X>::operator[](int i) {
	if (i < 0 || i >= size()) return nullptr;

	item<X>* temp = first;
	while (i) {
		temp = temp->next;
		i--;
	}

	return &(temp->data);
}

template<class X> X bag<X>::front() {
	if (size() == 0) return nullptr;

	return first->data;
}

template<class X> X bag<X>::back() {
	if (size() == 0) return nullptr;

	return last->data;
}

template<class X> void bag<X>::clear(){
    if (size() == 0) return;
    
    item<X>* temp = first;
    while(temp){
        first = temp->next;
        temp->next = nullptr;
        temp->previous = nullptr;
        delete temp;
        if(first) first->previous = nullptr;
        temp = first;
    }
    num_items = 0;
}

template<class X> item<X>* bag<X>::find(X d){
    if(size() == 0) return nullptr;

    item<X>* temp = first;
    while(temp){
        if(temp->data == d) return temp;
        temp = temp->next;
    }
    return nullptr;
}

template<class X> void bag<X>::erase(int index){
    if(index == 0) { pop_front(); return; }
    if(index == size() - 1) { pop_back(); return; }
    if(index < 0 || index >= size()) return;

    item<X>* temp = first;

    while(index){
        temp = temp->next;
        index--;
    }

    if(temp){
        temp->previous->next = temp->next;
        temp->next->previous = temp->previous;
        temp->previous = nullptr;
        temp->next = nullptr;
        delete temp;
        num_items--;
    }
}

template<class X> void bag<X>::erase(item<X>* p){
    if(!p || size() == 0) return;
    if(p == first) { pop_front(); return; }
    if(p == last) { pop_back(); return; }

    p->previous->next = p->next;
    p->next->previous = p->previous;
    p->previous = nullptr;
    p->next = nullptr;
    delete p;
    num_items--;
}

template<class X> item<X>* bag<X>::insert(item<X>* p, X d){
    if(p == first){ push_front(d); return first; }
    if(!p) { push_back(d); return last; }

    item<X>* newItem = new item<X>(d);
    newItem->next = p;
    p->previous->next = newItem;
    newItem->previous = p->previous;
    p->previous = newItem;
    num_items++;
    return newItem;
}

template<class X> bag<X>::bag(const initializer_list<X> &I){
    auto it = I.end() - 1; 

    while (it != I.begin() - 1) {
        item<X> * p = new item<T>(*it);
        p->next = first;
        if(!first) last = first;
        else first->previous = p;
        first = p;
        it--;
    }
}


/*
*
*OPERATOR OVERLOADS
*
*/

//Operator overloading for BAG
template<class X> ostream& operator<<(ostream& str, const bag<X> &B){
    auto p = B.first;
    while(p){
        str << p << " ";
        p = p->next;
    }
    return str;
}

//Operator overloading for ThreeD
template<class T> ostream& operator<<(ostream& str, const ThreeD<T> &T) {
	str << "( " << T.ht << ", " << T.wid << ", " << T.dep << " )";
	return str;
}

//Operator overloading for LinkedList
template<class T> ostream& operator<<(ostream& str, const linked_list<T>& L) {
	node<T>* temp = L.head;
	if (!temp) return str;
	while (!temp) {
		str << temp->value << " ";
	}
	return str;
}

//Operator overloading for VECTOR
template<class T> ostream& operator<<(ostream& str, const vector<T>& V) {
	auto it = V.begin();
	str << "[ ";
	while (it != V.end()) {
		str << *it;
		it++;
		if (it != V.end()) str << ", ";
	}
	str << "]";
	return str;
}

//Operator overloading for LIST
template<class T> ostream& operator<<(ostream& str, const list<T>& L) {
	auto it = L.begin();
	str << "[ ";
	while (it != L.end()) {
		str << *it;
		it++;
		if (it != L.end()) str << ", ";
	}
	str << "]";
	return str;
}


int main() {
    bag<double> bag_d;
    bag_d.push_back(5.5);
    bag_d.push_back(6.6);
    bag_d.push_front(4.4);
    bag_d.push_front(3.3);
    bag_d.pop_front();
    bag_d.pop_back();
    cout << bag_d << endl;;
    bag<int> bag_i;
    bag_i.push_back(5);
    bag_i.push_back(6);
    bag_i.push_front(4);
    bag_i.push_front(3);
    bag_i.pop_front();
    bag_i.pop_back();
    cout << bag_i << endl;

    ThreeD<int> td3(3), td4(4), td5(5), td6(6), td7(100, 200, 300);
    bag<ThreeD<int>> bag_3D;
    bag_3D.push_back(td5);
    bag_3D.push_back(td6);
    bag_3D.push_front(td4);
    bag_3D.push_front(td3);
    bag_3D.pop_front();
    bag_3D.pop_back();
    cout << bag_3D << endl;;
    cout << bag_3D.front() << bag_3D.back();
    cout << bag_3D[0] << " " << bag_3D[1] << endl;
    bag_3D[1] = td7;
    cout << bag_3D[0] << " " << bag_3D[1] << endl;
    bag_3D.clear();
    cout << bag_3D << endl;;
    cout << bag_3D.size() << endl;
    linked_list<string>ls_1;
    ls_1.push_front("David");
    ls_1.push_front("John");
    ls_1.push_front("Pat");
    ls_1.push_front("Ben");
    ls_1.push_front("Jeff");
    cout << ls_1 << endl;

    linked_list<string>ls_2;
    ls_2.push_front("Wendy");
    ls_2.push_front("Mary");
    ls_2.push_front("Nancy");
    ls_2.push_front("Jennifer");
    cout << ls_2 << endl;

    bag<linked_list<string>> bag_string;

    bag_string.push_back(ls_1);

    bag_string.push_back(ls_2);

    cout << bag_string << endl;
    cout << bag_string[1] << endl;
    
    
    ThreeD<double> t10(3.2, 7.4, 8.9), t11(5.6, 7.7, 2.987), t12(4.6, 7.5, 3.1416), t13(55.6, 66.8, 333.45);
    linked_list<ThreeD<double>> LTD1;
    LTD1.push_front(t10);

    LTD1.push_front(t11);
    linked_list<ThreeD<double>> LTD2;
    LTD2.push_front(t13);
    LTD2.push_front(t12);
    LTD2.push_front(t10);
    LTD2.push_front(t11);

    bag<linked_list<ThreeD<double> > > BLTD;
    BLTD.push_back(LTD1);
    BLTD.push_back(LTD2);
    cout << BLTD << endl;

    item<linked_list<ThreeD<double>>> * p2;

    p2 = BLTD.find(LTD1);
    BLTD.erase(p2);
    cout << BLTD << endl;
    BLTD.push_back(LTD1);
    cout << BLTD << endl;
    BLTD.erase(0);
    cout << BLTD << endl;

    vector<ThreeD<int>> V1 = { { 1,2,3 },{ 4,5,6 },{ 7,8,9 } };
    cout << V1 << endl;
    bag<bag<int>> V2 = { {1,2,3}, {4,5,6}, {7,8,9} };
    vector<bag<ThreeD<int>>> V2 = { { { 1,2,3 },{ 4,5,6 },{ 7,8,9 } },{ { 20,30,40 },{ 11,22, 33 } } };
    cout << V2 << endl;

    list<bag<linked_list<int>>> V3 = { { { 1, 2, 3 },{ 4, 5 } },{ { 6,7 },{ 8, 9, 10 } } };
    cout << V3 << endl;

    bag<int> B10 = { 1,2,3,4,5 };
    bag<int> B11 = B10, B12;
    B12 = B10;
    cout << B10 << endl;
    B10.first->data = 1000;
    cout << B10 << endl;
    cout << B11 << endl;
    cout << B12 << endl;

    bag<list<linked_list<ThreeD<int>>>> B13 = { { { { 1,2,3 },{ 4,5,6 } },{ { 7,8,9 },{ 10,11,12 },{ 13,14,15 } } },{ { { 16,17,18 },{ 19,20,21 },{ 22,23,24 } },{ { 25,26,27 },{ 28,29,30 } },{ { 31,32,33 },{ 34,35,36 },{ 37,38,39 },{ 40,41,42 } } } };
    cout << B13 << endl;

    bag<bag<bag<ThreeD<int>>>> B14 = { { { { 1,2,3 },{ 4,5,6 } },{ { 7,8,9 },{ 10,11,12 },{ 13,14,15 } } },{ { { 16,17,18 },{ 19,20,21 },{ 22,23,24 } },{ { 25,26,27 },{ 28,29,30 } },{ { 31,32,33 },{ 34,35,36 },{ 37,38,39 },{ 40,41,42 } } } };
    cout << B14 << endl;

    bag<linked_list<int>> * p10 = new bag<linked_list<int>>({ { 1,2,3,4 },{ 5,6,7 } });
    cout << *p10 << endl;
    delete p10;
    bag<list<linked_list<ThreeD<int>>>> B15 = { { { { 1,2,3 },{ 4,5,6 } },{ { 7,8,9 },{ 10,11,12 },{ 13,14,15 } } },{ { { 16,17,18 },{ 19,20,21 },{ 22,23,24 } },{ { 25,26,27 },{ 28,29,30 } },{ { 31,32,33 },{ 34,35,36 },{ 37,38,39 },{ 40,41,42 } } } };
    cout << B15 << endl;
    B15.erase(1);
    cout << B15 << endl;
    bag<list<linked_list<ThreeD<int>>>> B16 = { { { { 1,2,3 },{ 4,5,6 } },{ { 7,8,9 },{ 10,11,12 },{ 13,14,15 } } },{ { { 16,17,18 },{ 19,20,21 },{ 22,23,24 } },{ { 25,26,27 },{ 28,29,30 } },{ { 31,32,33 },{ 34,35,36 },{ 37,38,39 },{ 40,41,42 } } } };
    list<linked_list<ThreeD<int>>> V4 = { { { 6,1,1 },{ 2,5,12 } },{ { 9,8,7 },{ 11,10,12 },{ 26,7,15 } } };
    list<linked_list<ThreeD<int>>> V5 = { { { 6,1,1 },{ 2,5,12 } },{ { 9,8,7 },{ 11,10,12 },{ 26,7,5 } },{ { 6,1,1 },{ 2,5,12 } } };
    B16.insert(B16.first, V5);
    cout << B16.front().size() << endl;
    item<list<linked_list<ThreeD<int>>> > * p20=  B16.find(V4);
    if (p20 != nullptr) cout << (p20->data).size() << endl;
    getchar();
    getchar();
    return 0;
}

//The following is a screenshot of a sample output
/*
4.4 5.5
4 5
( 4, 4, 4 ) ( 5, 5, 5 )
( 4, 4, 4 )( 5, 5, 5 )( 4, 4, 4 ) ( 5, 5, 5 )
( 4, 4, 4 ) ( 100, 200, 300 )
0
Jeff Ben Pat John David
Jennifer Nancy Mary Wendy
Jeff Ben Pat John David  Jennifer Nancy Mary Wendy
Jennifer Nancy Mary Wendy
( 5.6, 7.7, 2.987 ) ( 3.2, 7.4, 8.9 )  ( 5.6, 7.7, 2.987 ) ( 3.2, 7.4, 8.9 ) ( 4.6, 7.5, 3.1416 ) ( 55.6, 66.8, 333.45 )
( 5.6, 7.7, 2.987 ) ( 3.2, 7.4, 8.9 ) ( 4.6, 7.5, 3.1416 ) ( 55.6, 66.8, 333.45 )
( 5.6, 7.7, 2.987 ) ( 3.2, 7.4, 8.9 ) ( 4.6, 7.5, 3.1416 ) ( 55.6, 66.8, 333.45 )  ( 5.6, 7.7, 2.987 ) ( 3.2, 7.4, 8.9 )
( 5.6, 7.7, 2.987 ) ( 3.2, 7.4, 8.9 )
[( 1, 2, 3 ), ( 4, 5, 6 ), ( 7, 8, 9 )]
[( 1, 2, 3 ) ( 4, 5, 6 ) ( 7, 8, 9 ) , ( 20, 30, 40 ) ( 11, 22, 33 ) ]
[1 2 3  4 5  , 6 7  8 9 10  ]
1 2 3 4 5
1000 2 3 4 5
1 2 3 4 5
1 2 3 4 5
[( 1, 2, 3 ) ( 4, 5, 6 ) , ( 7, 8, 9 ) ( 10, 11, 12 ) ( 13, 14, 15 ) ] [( 16, 17, 18 ) ( 19, 20, 21 ) ( 22, 23, 24 ) , ( 25, 26, 27 ) ( 28, 29, 30 ) , ( 31, 32, 33 ) ( 34, 35, 36 ) ( 37, 38, 39 ) ( 40, 41, 42 ) ]
( 1, 2, 3 ) ( 4, 5, 6 )  ( 7, 8, 9 ) ( 10, 11, 12 ) ( 13, 14, 15 )   ( 16, 17, 18 ) ( 19, 20, 21 ) ( 22, 23, 24 )  ( 25, 26, 27 ) ( 28, 29, 30 )  ( 31, 32, 33 ) ( 34, 35, 36 ) ( 37, 38, 39 ) ( 40, 41, 42 )
1 2 3 4  5 6 7
[( 1, 2, 3 ) ( 4, 5, 6 ) , ( 7, 8, 9 ) ( 10, 11, 12 ) ( 13, 14, 15 ) ] [( 16, 17, 18 ) ( 19, 20, 21 ) ( 22, 23, 24 ) , ( 25, 26, 27 ) ( 28, 29, 30 ) , ( 31, 32, 33 ) ( 34, 35, 36 ) ( 37, 38, 39 ) ( 40, 41, 42 ) ]
[( 1, 2, 3 ) ( 4, 5, 6 ) , ( 7, 8, 9 ) ( 10, 11, 12 ) ( 13, 14, 15 ) ]
3
2
*/