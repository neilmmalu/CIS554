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


}

void remove_student(map<int, map<int, list<course*>* >>& DB, int id) {

}


void add_course(map<int, map<int, list<course*>* >>& DB, int semester, int id, course c) {

}

void drop_course(map<int, map<int, list<course*>* >>& DB, int semester, int id, course c) {

}

void print_student_semester_courses(map<int, map<int, list<course*>* >>& DB, int semester, int id) {

}
void print_student_all_courses(map<int, map<int, list<course*>* >>& DB, int id) {

}

void print_DB(map<int, map<int, list<course*>* >>& DB) {

}
//Some additional functions for overloading operator<<


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