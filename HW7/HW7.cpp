#include <iostream>
#include <windows.h>
#include <stdlib.h>

using namespace std;

//SetCursorPosition(x,y)

void gotoxy(double x, double y){
	COORD coordinates;     // coordinates is declared as COORD
	coordinates.X = x;     // defining x-axis
	coordinates.Y = y;     //defining  y-axis
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coordinates);
}

void connectTrees(int n, double x, double y, double size) {
	double x1 = x - size / 2;
	double x2 = x + size / 2;
	double y1 = y - size / 2;
	double y2 = y + size / 2;

	cout << "x : " << x << " y: " << y << endl;

	gotoxy(x1, y + 1);
	SetCursorPos(x1, y + 1);
	cout << "LOL";
	
}

void plot(int n, double x, double y, double size) {
	if (n < 3) return;

	if (n == 3) {
		cout << "O   O" << endl;
		cout << "|   |" << endl;
		cout << "O-O-O" << endl;
		cout << "|   |" << endl;
		cout << "O   O" << endl;
		return;
	}

	connectTrees(n, x, y, size);

	double x1 = x - size / 2;
	double x2 = x + size / 2;
	double y1 = y - size / 2;
	double y2 = y + size / 2;

	if (n % 2 == 0) {
		plot(n - 1, x1, y1, size / 2);
		plot(n - 1, x1, y2, size / 2);
	}
	else {
		plot(n - 1, x2, y1, size / 2);
		plot(n - 1, x2, y2, size / 2);
	}
	


}

int main(){

	cout << "Enter size : " << endl;
	int n;
	cin >> n;

	system("CLS");
	

	double x = n;
	double y = n;
	double size = n;
	plot(n, x, y, size);



    getchar();
    getchar();
    return 0;
}