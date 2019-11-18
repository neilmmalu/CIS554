#include <iostream>
#include <windows.h>
#include <stdlib.h>

using namespace std;

//SetCursorPosition(x,y)

void gotoxy(int x, int y){
	COORD coordinates = {x,y};     // coordinates is declared as COORD
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coordinates);
}

void plot(int n, int x, int y) {
	if(n < 3) return;

	if(n == 3){
		gotoxy(x - 2, y - 2);
		cout << "O   O";
		gotoxy(x - 2, y - 1);
		cout << "|   |";
		gotoxy(x - 2, y);
		cout << "O-O-O";
		gotoxy(x - 2, y + 1);
		cout << "|   |";
		gotoxy(x - 2, y + 2);
		cout << "O   O";
		return;
	}

	if(n % 2 == 0){
		int y_top = y/2;
		int y_bottom = y + y/2 + 1;
		plot(n - 1, x, y_top);
		plot(n - 1, x, y_bottom);
		int start = y_top + 1;
		int end = y_bottom - 1;
		for(int i = start; i <= end; i++){
			gotoxy(x, i);
			if(i == y) cout << "O";
			else cout << "|";
		}
	}
	else{
		int x_left = x/2;
		int x_right = x + x/2 + 1;
		plot(n - 1, x_left, y);
		plot(n - 1, x_right, y);
		int start = x_left + 1;
		int end = x_right - 1;
		for(int i = start; i <= end; i++){
			gotoxy(i, y);
			if(i == x) cout << "O";
			else cout << "-";
		}
	}
}

int main(){

	cout << "Enter size : " << endl;
	int n;
	cin >> n;

	system("CLS");
	
	if (n % 2 == 0) {
		plot(n, n-1, 2 * (n-1) + 1);
	}
	else {
		plot(n, n-1, n-1);
	}

	



    getchar();
    getchar();
    return 0;
}