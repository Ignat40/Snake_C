#include <iostream>
#include <conio.h>
#include<windows.h>
using namespace std;

bool game_over;
const int width = 20;
const int height = 20;
int x, y,fruit_x, fruit_y,score;
int tail_x[100], tail_y[100];
int nTail;
enum eDireciton{STOP = 0, LEFT, RIGHT, UP, DOWN};
eDireciton dir;


void Setup() {

	game_over = false;	
	dir = STOP;
	x = width / 2;
	y = height / 2;
	fruit_x = rand() % width;
	fruit_y = rand() % height;
	score = 0;

}

void Draw() {

	system("cls");
	for (int i = 0; i < width +2; i++) 
		cout << "#";
	cout << endl;

	for (int i = 0; i < height; i++) {

		for (int j = 0; j < width; j++) {
			if (j == 0)
				cout << "#";
			if (i == y && j == x)
				cout << "O";
			else if (i == fruit_y && j == fruit_x)
				cout << "F";
			else {
				bool print = false;
				for (int k = 0; k < nTail; k++) {
					
					if (tail_x[k] == j && tail_y[k] == i) {
						cout << "o";
						print = true;
					}
					
				}
				if (print);
				cout << " ";
			}
			

			if (j == width - 1)
				cout << "#";
		}
		cout << endl;
	}

	for (int i = 0; i < width+2; i++)
		cout << "#";
	cout << endl;
	cout << "Score: " << score;
}

void Input() {

	if (_kbhit()) {

		switch (_getch()) {
		case 'a':
			dir = LEFT;
				break;
		case 'd':
			dir = RIGHT;
			break;
		case 'w':
			dir = UP;
			break;
		case 's':
			dir = DOWN;
			break;
		case 'x':
			game_over = true;
			break;
		}
		
	}

}

void Logic() {

	int prev_x = tail_x[0];
	int prev_y = tail_y[0];
	int prev2X, prev2Y;
	tail_x[0]=x;
	tail_y[0]= y;
	for (int i = 1; i < nTail; i++) {
		prev2X = tail_x[i];
		prev2Y = tail_y[i];
		tail_x[i] = prev_x;
		tail_y[i] = prev_y;
	}
	switch (dir)
	{
	case LEFT:
		x--;
		break;		
	case RIGHT:
		x++;
		break;
	case UP:
		y--;
		break;
	case DOWN:
		y++;
		break;
	default:
		break;
	}
	/*if (x > width || x < 0 || y > height || y < 0)
		game_over = true;*/
	if (x >= width) x = 0; else if (x < 0) x = width - 1;
	if (y >= height) y = 0; else if (y < 0) y = height - 1;

	for (int i = 0; i < nTail; i++)
		if (tail_x[i] == x && tail_y[i] == y)
			game_over = true;
	if (x == fruit_x && y == fruit_y) {
		score += 10;
		fruit_x = rand() % width;
		fruit_y = rand() % height;
		nTail++;
	}
}



int main() {

	Setup();

	while (!game_over) {
		Draw();
		Input();
		Logic();
		Sleep(50);
	}



	return 0;
}