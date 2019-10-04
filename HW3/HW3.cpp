//HW3 Neil Malu
//SU NetID: nemalu SUID: 635692900

//HW3
//Due: Thursday (10/3) at 11:59PM


#include <iostream>
#include <list>
#include <map>
#include <string>
using namespace std;

class course {
public:
    string name;
    int section;
    int credits;
    course() {}
    course(string n, int s, int c) { name = n; section = s; credits = c; }
    //Add additional needed member functions and implement them.
    //You also need to implement some needed functions for overloading operator<< .
	friend ostream& operator<<(ostream& str, const course& C);
    friend ostream& operator<<(ostream& str, const list<course *> &L);
    friend ostream& operator<<(ostream& str, const map<int, list<course*>*> &M);
    friend ostream& operator<<(ostream& str, const map<int, map<int, list<course*>*>> &DB);

    bool operator<(course c) { return (name < c.name); }
    bool operator==(course c) { return (name == c.name); }
};
//Implement the following functions

void add_student(map<int, map<int, list<course*>* > >& DB, int id);
void remove_student(map<int, map<int, list<course*>* > >& DB, int id);
void add_course(map<int, map<int, list<course*>* > >& DB, int semester, int id, course c); //20171 Spring semester of 2017; 20172: Fall semester of 2017

void drop_course(map<int, map<int, list<course*>* > >& DB, int semester, int id, course c);
void print_student_semester_courses(map<int, map<int, list<course*>* > >& DB, int semester, int id);
void print_student_all_courses(map<int, map<int, list<course*>* > >& DB, int id);
void print_DB(map<int, map<int, list<course*>* > >& DB);

//For the print funcitons, you need to add more fucntions to overload operator<<.
//for example print_DB is simply cout << DB;
//Courses in a semeste are sorted alphabetically.


int main() {
    //Do not change code for main function
    map<int, map<int, list <course*>*> > DB;
    add_student(DB, 11111);
    course C1("CIS554", 1, 3), C2("CSE674", 1, 3), C3("MAT296", 8, 4), C4("WRT205", 5, 3);

    add_course(DB, 20171, 11111, C1);
    add_course(DB, 20171, 11111, C4);
    add_course(DB, 20171, 11111, C3);
    add_course(DB, 20171, 11111, C2);
    print_student_semester_courses(DB, 20171, 11111);

    drop_course(DB, 20171, 11111, C1);
    print_student_semester_courses(DB, 20171, 11111);

    add_course(DB, 20172, 11111, C2);
    add_course(DB, 20172, 11111, C4);
    add_course(DB, 20172, 11111, C3);
    add_course(DB, 20172, 11111, C1);
    print_student_all_courses(DB, 11111);

    add_student(DB, 11112);
    add_course(DB, 20171, 11112, C2);
    add_course(DB, 20171, 11112, C4);
    add_course(DB, 20171, 11112, C3);
    add_course(DB, 20171, 11112, C1);
    print_student_semester_courses(DB, 20171, 11112);

    add_course(DB, 20172, 11112, C2);
    add_course(DB, 20172, 11112, C4);
    add_course(DB, 20172, 11112, C3);
    add_course(DB, 20172, 11112, C1);
    print_student_semester_courses(DB, 20172, 11112);
    print_student_all_courses(DB, 11112);
    print_DB(DB);
    remove_student(DB, 11111);
    print_DB(DB);
    getchar();
    getchar();
    return 0;
}

void add_student(map<int, map<int, list<course*>* >>& DB, int id) { 
    if(DB.find(id) == DB.end()) {
        map<int, list<course*>*> sem;
        DB[id] = sem;
    }
}

void remove_student(map<int, map<int, list<course*>* >>& DB, int id) {
    //If student does not exist
    if(DB.find(id) == DB.end()) return;

    //delete the outer map last
    auto it1 = DB.find(id);
    
    auto it2 = DB[id].begin();
    //Inner map
    while(it2 != DB[id].end()){

        for(auto x : DB[id]){
            //it3 is a list iterator
            auto it3 = x.second->begin();
            while(it3 != x.second->end()){
                x.second->erase(it3);
                it3 = x.second->begin();
            }
        }
        // DB[id].erase(it2); //seg faulting. Mem leak here?
        it2++;
    }

    DB.erase(it1);

}


void add_course(map<int, map<int, list<course*>* >>& DB, int semester, int id, course c) {
    //if student does not exist
    if(DB.find(id) == DB.end()) return;

    course* x = new course(c.name, c.section, c.credits);
    //if semester does not exist, create semester
    if(DB[id].find(semester) == DB[id].end()){
        DB[id][semester] = new list<course*>();
        DB[id][semester]->push_back(x);
    }

    //if semester exists, insert course at the sorted positon in the list
    else{
        auto it = DB[id][semester]->begin();
        while(it != DB[id][semester]->end() && **it < *x) it++;

        DB[id][semester]->insert(it, x);
    }
}

void drop_course(map<int, map<int, list<course*>* >>& DB, int semester, int id, course c) {
    //If course does not exist
    if(DB.find(id) == DB.end()) return;

    //If semester does not exist
    if(DB[id].find(semester) == DB[id].end()) return;

    auto i = DB[id][semester]->begin();
    while(i != DB[id][semester]->end()){
        //compare the courses. == has been overloaded in class
        if(**i == c) {
            DB[id][semester]->erase(i); 
            return;
        }
        i++;
    }
}

void print_student_semester_courses(map<int, map<int, list<course*>* >>& DB, int semester, int id) {
    cout << "student id = " << id << endl;
    cout << "semester = " << semester << endl;
    cout << *DB[id][semester] << endl;
}
void print_student_all_courses(map<int, map<int, list<course*>* >>& DB, int id) {
    cout << "student id = " << id << endl;
    cout << DB[id] << endl;
}

void print_DB(map<int, map<int, list<course*>* >>& DB) {
    cout << DB;
}

//Some additional functions for overloading operator<<

//pointer to the list
ostream& operator<<(ostream& str, const map<int, list<course*>*> &M){
	for (auto i : M) {
        str << "semester = " << i.first << endl;
		str << *i.second;
	}
    return str;
}

//DB
ostream& operator<<(ostream& str, const map<int, map<int, list<course*>*>> &DB){
    for (auto i : DB) { 
        str << "student id = " << i.first << endl;
        for(auto j : i.second){
            str << "semester = " << j.first << endl;
            str << *j.second;
        }
    }
    str << endl;
    return str;
}

ostream& operator<<(ostream& str, const list<course *> &L){
    for(auto c : L){
        str << *c << " ";
    }
    str << endl;
    return str;
}

ostream& operator<<(ostream& str, const course& C) {
	str << C.name << " " << C.section << " " << C.credits << " ";
	return str;
}


/*
//Your output needs to keep the identical format
//Sample Screenshot
student id = 11111
semester = 20171
CIS554 1 3  CSE674 1 3  MAT296 8 4  WRT205 5 3

student id = 11111
semester = 20171
CSE674 1 3  MAT296 8 4  WRT205 5 3

student id = 11111
semester = 20171
CSE674 1 3  MAT296 8 4  WRT205 5 3
semester = 20172
CIS554 1 3  CSE674 1 3  MAT296 8 4  WRT205 5 3

student id = 11112
semester = 20171
CIS554 1 3  CSE674 1 3   MAT296 8 4  WRT205 5 3

student id = 11112
semester = 20172
CIS554 1 3  CSE674 1 3  MAT296 8 4  WRT205 5 3

student id = 11112
semester = 20171
CIS554 1 3  CSE674 1 3  MAT296 8 4  WRT205 5 3
semester = 20172
CIS554 1 3  CSE674 1 3  MAT296 8 4  WRT205 5 3

student id = 11111
semester = 20171
CSE674 1 3  MAT296 8 4  WRT205 5 3
semester = 20172
CIS554 1 3  CSE674 1 3  MAT296 8 4  WRT205 5 3
student id = 11112
semester = 20171
CIS554 1 3  CSE674 1 3  MAT296 8 4  WRT205 5 3
semester = 20172
CIS554 1 3  CSE674 1 3  MAT296 8 4  WRT205 5 3

student id = 11112
semester = 20171
CIS554 1 3  CSE674 1 3  MAT296 8 4  WRT205 5 3
semester = 20172
CIS554 1 3  CSE674 1 3  MAT296 8 4  WRT205 5 3
*/
