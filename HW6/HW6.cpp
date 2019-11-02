//CIS554 HW6   Due: 11:59PM, Friday, Nov. 8.
#include <iostream>
#include <memory>
#include <math.h>

using namespace std;

class node {
public:
    int value;
    shared_ptr<node> right;
    shared_ptr<node> l_child;
    shared_ptr<node> r_child;
    node() {}
    node(int i) { value = i; }
};

class tree {
public:
    shared_ptr<node> root;
    int level;
    tree() { level = 0; }

    //Implement all member functions below
    tree(int n);//constructor for n-level tree
    //and initilize values as shown in the diagram; 0, 1, 2, ...
    //Note that root node is at level 1 and its value will be initialized to 0
    
    tree(const tree &T);//copy constructor
    ~tree();//destructor
    tree(tree &&T); //move constructor

    tree(const initializer_list<int> &V);//The first number in V is tree level;
    //the rest are values from top to bottom and from left to right
    //For example, to create the tree with n=3 in the diagram,
    //tree T1 = {3, 0,1,2,3,4,5,6}; //where the first 3 is tree level, and the rest are values

    void operator= (const tree &R);//L-value operator=
    void operator= (tree &&R); //R-value operator=
    

    tree ThreeTimes(); //return a tree with all node value being three times
    friend ostream & operator<<(ostream &str, const tree &T);

    int sum(shared_ptr<node> p);//sum of node values in sub-tree rooted at p
    void delete_level(int i); // Delete nodes at level i. Some nodes at level(s) higher
    //than i will also be deleted accordingly. As described in class.  (Also see the
    //example in the main function.)

    shared_ptr<node> find(int i); //find the first node with value i and return
    //its address; if not found, return nullptr;
};




int main() {
    tree T1(3);

    cout << T1 << endl; //will print 0 1 2 3 4 5 6

    tree T2 = {4, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24 };
    cout << T2 << endl; //will print 10 11 12 13 14 15 16 17 18 19 20 21 22 23 24
    
    tree T3(T2);
    cout << T3 << endl; //will print 10 11 12 13 14 15 16 17 18 19 20 21 22 23 24
    
    tree T4;
    T4 = T3;
    cout << T4 << endl; //will print 10 11 12 13 14 15 16 17 18 19 20 21 22 23 24
    
    T4 = T3.ThreeTimes();
    cout << T4 << endl;//will print 30 33 36 39 42 45 48 51 54 57 60 63 66 69 72
    
    T4.delete_level(3);
    cout << T4 <<endl;//will print 30 33 36 51 57 63 67
      
    cout<<T3.sum(T3.find(12)) << endl; //will print 133
    
    

    getchar();
    getchar();
    return 0;
}