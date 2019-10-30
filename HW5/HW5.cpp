//HW 5 Neil Malu
//SU NetID: nemalu SUID: 635692900
//CIS554 HW4 Due: 11:59PM, Nov. 1 (Friday)

#include <iostream>
#include <list>
#include <map>
using namespace std;

int count(const list<int> &L, bool(*f)(const int i)){
    int count = 0;
    auto it = L.begin();
    while(it != L.end()){
        if(f(*it)) count++;
        it++;
    }
    return count;
}

bool odd(const int i){ return i % 2 == 1; }

bool even(const int i){ return i % 2 == 0; }

class my_comp_class {
public:
	bool operator() (const list<int*>* L1, const list<int*>* L2) const {
		int sum1 = 0, sum2 = 0;
		auto it1 = L1->begin();
        while(it1 != L1->end()){
            sum1 += **it1;
            it1++;
        }

		auto it2 = L2->begin();
        while(it2 != L2->end()){
            sum2 += **it2;
            it2++;
        }
		return sum1 < sum2;
	}
};

class my_comp1_class {
public:
	bool operator() (const list<int>* L1, const list<int>* L2) const {
		int sum1 = 0, sum2 = 0;
        auto it1 = L1->begin();
        while(it1 != L1->end()){
            sum1 += *it1;
            it1++;
        }

        auto it2 = L2->begin();
        while(it2 != L2->end()){
            sum2 += *it2;
            it2++;
        }

        return sum1 < sum2;
	}
};

template<class T, class X> ostream& operator<<(ostream& str, const map<T*, int, X> &M){
	for (auto i : M) {
		str << *(i.first) << " " << i.second << " ";
	}
	return str;
}

template<class T, class X> ostream& operator<<(ostream& str, const map<T, int, X> &M) {
	for (auto i : M) {
		str << i.first << " " << i.second << " ";
	}
	return str;
}

template<class T> ostream& operator<<(ostream& str, const list<T> &L){
    auto it = L.begin();
    while(it != L.end()){
        str << *it << " ";
        it++;
    }
    return str;
}

template<class T> ostream& operator<<(ostream& str, const list<T*> &L){
    auto it = L.begin();
    while(it != L.end()){
        str << **it << " ";
        it++;
    }
    return str;
}


bool my_comp2(const list<list<int*>*>& L1, const list<list<int*>*>& L2) {
	int sum1 = 0, sum2 = 0;
	auto it = L1.begin();
	while (it != L1.end()) {
		auto it2 = (*it)->begin();
		while (it2 != (*it)->end()) {
			sum1 += **it2;
			it2++;
		}
		it++;
	}

	it = L2.begin();
	while (it != L2.end()) {
		auto it2 = (*it)->begin();
		while (it2 != (*it)->end()) {
			sum2 += **it2;
			it2++;
		}
		it++;
	}

	return sum1 < sum2;
}

class list_comp_class{
public:
    bool operator() (const list<list<int*>*> &L1, const list<list<int*>*> &L2) const{
        int sum1 = 0, sum2 = 0;
        auto it = L1.begin();
        while (it != L1.end()) {
            auto it2 = (*it)->begin();
            while (it2 != (*it)->end()) {
                sum1 += **it2;
                it2++;
            }
            it++;
        }

        it = L2.begin();
        while (it != L2.end()) {
            auto it2 = (*it)->begin();
            while (it2 != (*it)->end()) {
                sum2 += **it2;
                it2++;
            }
            it++;
        }

        return sum1 < sum2;
    }
} my_comp3;


int main() {
    //Write 3 functions: count, odd, even.
    //The second argument for count is either function odd or even.
    //It will count either the number of odd element in the list, or 
    //the number of even elements in the list.
    list<int> L0{ 14,7,2,6,9,5,8,2,13 };
    cout << count(L0, odd) << endl;
    cout << count(L0, even) << endl;

    
    //You need to design a class of comparison functions (or functors) to allow map to sort elements.
    //This class is called my_comp_class.  Remember that you need to include const for sorting of map.
    //You also need to overload the needed operator<< to print DB.
    map<list<int*>*, int, my_comp_class> DB{ {new list<int*>{new int{9}, new int{28}, new int{14}}, 7},
    {new list<int*>{new int{19}, new int{18}}, 17} };
    cout << DB << endl;

    //You need to design a class of comparison functions (or functors) to allow map to sort elements.
    //This class is called my_comp1_class. Remember that you need to include const for sorting of map.
    //You also need to overload the needed operator<< to print DB1.
    map<list<int>*, int, my_comp1_class> DB1{ {new list<int>{9, 28,14}, 7},
    {new list<int>{19,18}, 17} };
    cout << DB1 << endl;

    list<list<int*>*> L1{ {new list<int*>{new int{15}, new int{7}, new int{22}}},
    {new list<int*>{new int{4}, new int{8}, new int{12}}} };//sum is 68
    list<list<int*>*> L2{ {new list<int*>{new int{5}, new int{6}, new int{2}, new int{11}}},
    {new list<int*>{new int{2}, new int{7}, new int{10}}} }; //sum is 43
    list<list<int*>*> L3{ {new list<int*>{new int{2}, new int{3}, new int{2}, new int{9}}},
    {new list<int*>{new int{2}, new int{7}, new int{4}, new int(3)}} };//32

    /*
    For the following sort of L4, L5, and L6, compare the sum of all values for L1, L2, and L3.
    For example, the sums of L1, L2, and L3 are 68, 43, and 32, respectively.
    Implement the comparison functions my_comp2, my_comp3, my_comp4 as stated below.
    You also need to overload the needed operator<< to allow the printing.
    */
    
    list< list<list<int*>*>> L4{ L1, L2, L3 };
    cout << L4 << endl;
    L4.sort(my_comp2);//Design the function my_comp2 using regular function implementation.
    cout << L4 << endl;
	
    list< list<list<int*>*>> L5{ L1, L3, L2 };
    cout << L5 << endl;
    L5.sort(my_comp3); //Design my_comp3 using a functor.
    cout << L5 << endl;

    list< list<list<int*>*>> L6{ L2, L1, L3 };
    cout << L6 << endl;
	L6.sort([](const list<list<int*>*> L1, const list<list<int*>*> L2) {
		int sum1 = 0, sum2 = 0;
		auto it = L1.begin();
		while (it != L1.end()) { auto it2 = (*it)->begin(); while (it2 != (*it)->end()) { sum1 += **it2; it2++; } it++; }
		it = L2.begin();
		while (it != L2.end()) { auto it2 = (*it)->begin(); while (it2 != (*it)->end()) { sum2 += **it2; it2++; } it++; }
		return sum1 < sum2;
    }); //Use lambda Expression.
    cout << L6 << endl;
    
    cin.get();
    return 0;
}

//The following is a sample display
/*
4
5
19 18  17 9 28 14  7
19 18  17 9 28 14  7
15 7 22  4 8 12   5 6 2 11  2 7 10   2 3 2 9  2 7 4 3
2 3 2 9  2 7 4 3   5 6 2 11  2 7 10   15 7 22  4 8 12
15 7 22  4 8 12   2 3 2 9  2 7 4 3   5 6 2 11  2 7 10
2 3 2 9  2 7 4 3   5 6 2 11  2 7 10   15 7 22  4 8 12
5 6 2 11  2 7 10   15 7 22  4 8 12   2 3 2 9  2 7 4 3
2 3 2 9  2 7 4 3   5 6 2 11  2 7 10   15 7 22  4 8 12

*/