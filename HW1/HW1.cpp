//HW1 Neil Malu
//SU netID: nemalu SUID: 635692900

//CIS554 HW2
//Due: 11:59PM, Monday ( September 23)
/*
Implement two member functions, merge and remove, of the DoublyLinkedList class of HW1.
The descriptions of the two member functions are given below.
In the implementation of the two member functions, you are not allowed to modify values of nodes.
You only can modify pointers of nodes.
Again, you are not allowed to create new nodes in your implementation.  No external structures (such as arrays,
linked list, map, etc.) are allowed.  You can use some temporary pointes or variables for your
implementation.

When you submit your code, do not modify main function.

Do not introduce new functions
In-place implementation is required.  (This means all operations should directly performed on the list.)
*/

#include <iostream>
using namespace std;

class Node {
public:
	int value;
	Node* next;
	Node* previous;
	Node(int i) { value = i; next = previous = nullptr; }
	Node() { next = previous = nullptr; }
};

class DoublyLinkedList {
public:
	Node* head;
	Node* tail;
	DoublyLinkedList() { head = tail = nullptr; }
	void makeRandomList(int m, int n);
	void printForward();
	void printBackward();

	//inplement the following member functions:

	void sort();//sort all values based on frequency in ascending order.
	 //In case of ties, the smaller values will appear earlier
	//Example:  for list with values  7 6 12 4 33 12 6 6 7
	//sorted results: 4 33 7 7 12 12 6 6 6


	//If your algorithm is inefficient, you might lose points.
	//You will not modify L.

	void merge(const DoublyLinkedList& L);
	/*
	Given an already sorted DoublyLinkedList (using the sort() in HW1), take
	another already sorted list L as function argument, and merge L into the current
	list to form a single DoublyLinkedList.
	You are not allowed to invoke sort() to do merge.
	Merge is a much easier task and you need to develop a new, efficient way to do merge.
	*/

	void remove(int m, int n);
	/*
	Given an already sorted DoublyLinkedList (using the sort() in HW1),
	remove n times of value m from the DoublyLinkedList
	if n is more than the total number of m's in the DoublyLinkedList,
	then remove all m's from the list.
	If m does not exist in the list, then do nothing.
	*/
};

void DoublyLinkedList::sort() {
	if (!head || !head->next) return;

	Node* p1 = head, * p2;

	//Sort initially so that blocks can be moved instead of individual nodes
	//Brute force sorting - only swapping values not nodes
	while (p1) {
		p2 = p1->next;
		while (p2) {
			if (p1->value > p2->value) {
				int temp = p1->value;
				p1->value = p2->value;
				p2->value = temp;
			}
			p2 = p2->next;
		}
		p1 = p1->next;
	}
	
	p1 = head;
	Node* p3;
	Node* passes = head;

	// Swapping nodes not values.
	while (passes) {
		while (p1) {
			//printForward();
			p2 = p1->next;
			int count1 = 1;
			while (p2 && p2->value == p1->value) {
				p2 = p2->next;
				count1++;
			}

			if (!p2) break;

			p3 = p2;
			int count2 = 0;
			while (p3 && p3->value == p2->value) {
				if (p3 == tail) {
					count2++;
					break;
				}
				p3 = p3->next;
				count2++;
			}

			//cout << "p1 = " << p1->value << " p2 = " << p2->value << " p3 = " << p3->value << " count1 = " << count1 << " count2 = " << count2 << endl;
			//cout << "passes " << passes->value << endl;

			// Compare the frequencies. If first one is smaller, advance the pointer without swapping
			if (count1 <= count2) {
				p1 = p2;
			}
			else {
				//swap blocks
				// p1 is the head of the first swap block, p2 is the head of the second swap block
				
				//Edge case if only 2 unique values
				if (p1 == head && p3 == tail) {
					head = p2;
					tail = p2->previous;
					p2->previous->next = nullptr;
					p2->previous = nullptr;
					p3->next = p1;
					p1->previous = p3;
					return;
				}

				//Edge case for head node
				if (p1 == head) {
					Node* p4 = p3->previous;
					p2->previous->next = p3;
					p3->previous->next = p1;
					p3->previous = p2->previous;
					p1->previous = p4;
					p2->previous = nullptr;
					head = p2;
				}

				//Edge case for tail node
				else if (p3 == tail) {
					tail = p2->previous;
					p1->previous->next = p2;
					p2->previous->next = nullptr;
					p2->previous = p1->previous;
					p3->next = p1;
					p1->previous = p3;
				}

				//Swapping consecutive nodes
				else {
					Node* p4 = p3->previous;
					p3->previous->next = p1;
					p2->previous->next = p3;
					p1->previous->next = p2;
					p3->previous = p2->previous;
					p2->previous = p1->previous;
					p1->previous = p4;
				}

			}
		}
		passes = passes->next;
		p1 = head;
	}
	
}

void DoublyLinkedList::merge(const DoublyLinkedList& L) {
	if (!head) {
		head = L.head;
		return;
	}

	if (!L.head) return;

	Node* l1 = head, * l2 = L.head;

	
}

void DoublyLinkedList::remove(int m, int n) {
	if (!head) return;
	if (n == 0) return;

	if (head->value == m) {
		Node* temp = head;
		while (head->value == m && n) {
			head = head->next;
			head->previous = nullptr;
			delete temp;
			temp = head;
			n--;
		}
		return;
	}

	Node* p1 = head;
	while (p1) {
		
		Node* p2 = p1;
		int count = 0;
		if (p1->value == m) {
			while (p2 && p2->value == m) {
				p2 = p2->next;
				count++;
			}

			if (count <= n) {
				p1->previous->next = p2;
				if (p2 != nullptr) p2->previous = p1->previous;
				else tail = p1->previous;
				delete p1;
				return;
			}
			else {
				//Case where you have to re-insert in sorted position
				Node* temp;
				p1->previous->next = p2;
				if (p2 != nullptr) {
					p2->previous->next = nullptr;
					p2->previous = p1->previous;
				}
				else tail = p1->previous;
				while (n) {
					temp = p1;
					p1 = p1->next;
					delete temp;
					n--;
					count--;
				}

				//At this point, p1 points to the block of remaining occ of the number, count is the freq
				temp = head;
				while (temp) {
					p2 = temp;
					int count2 = 0;

					//At the tail
					if (temp == tail) {
						temp->next = p1;
						p1->previous = temp;
						while (p1->next) p1 = p1->next;
						tail = p1;
						return;
					}

					while (p2->value == temp->value) {
						p2 = p2->next;
						count2++;
					}
					
					// Position at which we need to insert p1
					if (count2 > count || (count2 == count && p1->value < temp->value)) {
						Node* p3 = p1;
						while (p3->next) p3 = p3->next;
						//If insert is at head
						if (temp == head) {
							p3->next = temp;
							head = p1;
							p1->previous = nullptr;
							return;
						}
						else {
							p3->next = temp;
							temp->previous->next = p1;
							p1->previous = temp->previous;
							temp->previous = p3;
							return;
						}
					}
					//Continue
					else
						temp = temp->next;
				}
				
			}
		}

		p1 = p1->next;
		
	}

}

void DoublyLinkedList::makeRandomList(int m, int n) {

	for (int i = 0; i < m; i++) {
		Node* p1 = new Node(rand() % n);
		p1->previous = tail;
		if (tail != nullptr) tail->next = p1;
		tail = p1;
		if (head == nullptr) head = p1;
	}
}

void DoublyLinkedList::printForward() {
	cout << endl;
	Node* p1 = head;
	while (p1 != nullptr) {
		cout << p1->value << " ";
		p1 = p1->next;
	}
}

void DoublyLinkedList::printBackward() {
	cout << endl;
	Node* p1 = tail;
	while (p1 != nullptr) {
		cout << p1->value << " ";
		p1 = p1->previous;
	}
}

int main() {
	DoublyLinkedList d1, d2;
	d1.makeRandomList(50, 20);
	//d1.printForward();
	//d1.printBackward();

	d1.sort();
	d1.printForward();
	//d1.printBackward();

	//d2.makeRandomList(50, 20);
	//d2.printForward();
	//d2.printBackward();
	//d2.sort();
	//d2.printForward();
	
	//d1.merge(d2);
	//d1.printForward();
	//d1.printBackward();

	d1.remove(11, 5);
	d1.printForward();
	d1.printBackward();
	getchar();
	getchar();
	return 0;
}