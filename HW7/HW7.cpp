#include <iostream>\

using namespace std;



void H_layout(int i){

    if(i == 1){
        cout << "O" << endl;
        return;
    }

    if(i % 2 == 0){
        H_layout(i - 1);
        for(int j = 0; j < i/2; j++) cout << "|" << endl;
        cout << "O" << endl;
        for(int j = 0; j < i/2; j++) cout << "|" << endl;
        H_layout(i - 1);
        return;
    }

    H_layout(i - 1);
    for(int j = 0; j <= i/2; j++) cout << "\eA";
    for(int j = 0; j < i/2; j++) cout << "-";
    cout << "O";
    for(int j = 0; j < i/2; j++) cout << "-";
    for(int j = 0; j < i/2; j++) cout << endl; 
    H_layout(i - 1);



}

int main(){

    for(int i = 1; i < 4; i++){
        H_layout(i);
    }
    getchar();
    getchar();
    return 0;
}