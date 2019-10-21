//CIS554 HW2 Second 
//Due: 11:59PM Tuesday ( October 22 )
/*
-   Implement the functions reverse of the DoublyLinkedList class which is sorted in frequency.
The description of the reverse function is given in the class.
-   In the implementation reverse, you are not allowed to modify values of nodes.
You only can modify pointers of nodes.
-   Again, you are not allowed to create new nodes in your implementation.  No external structures (such as arrays,
linked list, map, etc.) are allowed.  You can use some temporary pointes or variables for your
implementation.
-   In implementaing reverse, you are not allowed to do sorting from scratch.

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
	DoublyLinkedList(const std::initializer_list<int>& V);
	void printForward();
	void printBackward();


	void reverse();
	/*
	Given an already sorted DoublyLinkedList in frequency (i.e., the result of HW1), make
	the numbers with the same frequency be sorted in decending order.
	For example, 4 9 33 7 7 12 12 6 6 6 will be re-arranged into 33 9 4 12 12 7 7 6 6 6
	*/

};


DoublyLinkedList::DoublyLinkedList(const std::initializer_list<int>& V) {
	head = tail = nullptr;
	for (auto& value : V) {
		Node* p1 = new Node(value);
		p1->previous = tail;
		if (tail != nullptr)
			tail->next = p1;
		tail = p1;
		if (head == nullptr)
			head = p1;
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

void DoublyLinkedList::reverse() {
	if (!head || !head->next) return;

	if (head->value == tail->value) return;

	Node* p1 = head;
	Node* p2 = p1;
	Node* passes = head;
	while (passes) {
		while (p1) {
			p2 = p1->next;
			int count1 = 1, count2 = 1;
			while (p2 && p2->value == p1->value) {
				count1++;
				if (p2->next) p2 = p2->next;
				else break;
			}
			//p1 points to first node in freq block, p2 points to first node in next block unless its the tail
			if (p2 != tail) {
				Node* p3 = p2->next;
				while (p3 && p3->value == p2->value) {
					count2++;
					if (p3->next) p3 = p3->next;
					else break;
				}

				if (count1 == 1 && count2 == 1 && p1->value < p2->value) {

					if (p1 == head) {
						p1->next = p2->next;
						p2->next->previous = p1;
						p1->previous = p2;
						p2->next = p1;
						p2->previous = nullptr;
						head = p2;
					}

					else {
						p1->previous->next = p2;
						p2->next->previous = p1;
						p1->next = p2->next;
						p2->previous = p1->previous;
						p1->previous = p2;
						p2->next = p1;
					}
				}

				else if (count1 == count2 && p1->value < p2->value) {
					if (p1 == head && p3 == tail) {
						p2->previous->next = nullptr;
						tail = p2->previous;
						p2->previous = nullptr;
						p3->next = p1;
						p1->previous = p3;
						head = p2;
					}

					else if (p1 == head) {
						p2->previous->next = p3->next;
						p3->next->previous = p2->previous;
						p2->previous = nullptr;
						p3->next = p1;
						p1->previous = p3;
						head = p2;
					}
					else if (p3 == tail) {
						p2->previous->next = nullptr;
						tail = p2->previous;
						p3->next = p1;
						p2->previous = p1->previous;
						p1->previous->next = p2;
						p1->previous = p3;
					}
					else {
						p2->previous->next = p3->next;
						p3->next->previous = p2->previous;
						p1->previous->next = p2;
						p2->previous = p1->previous;
						p3->next = p1;
						p1->previous = p3;
					}
				}
				else p1 = p2;

			}
			//If p2 is the tail then current block is the last one
			
			else if (p1 == head && p2 == tail) {
				p1->next = nullptr;
				p1->previous = p2;
				tail = p1;
				p2->next = p1;
				p2->previous = nullptr;
				head = p2;
				return;
			}
			else break;

		}
		passes = passes->next;
		p1 = head;
	}
	
}

int main() {

	DoublyLinkedList d{ 1,9,15,2,2,8,8,0,0,0,0,3,3,3,3,3,19,19,19,19,19,11,11,11,11,11,11, 4,4,4,4,4,4,4 };
	d.reverse();

	d.printForward();
	d.printBackward();

	DoublyLinkedList d1{ 1,9,9,9 };
	d1.reverse();

	d1.printForward();
	d1.printBackward();

	DoublyLinkedList d2{ 0,0,3,3,3,4,4,4 };
	d2.reverse();

	d2.printForward();
	d2.printBackward();

	DoublyLinkedList d3{ 8,8,9,9,13,13 };
	d3.reverse();

	d3.printForward();
	d3.printBackward();

	DoublyLinkedList d4{ };
	d4.reverse();

	d4.printForward();
	d4.printBackward();

	DoublyLinkedList d5{ 13,13,13,13,13 };
	d5.reverse();

	d5.printForward();
	d5.printBackward();

	getchar();
	getchar();
	return 0;
}