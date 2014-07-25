#include<iostream>
#include<ncurses.h>
#include<stdlib.h>
#include<string>
#include"stein.h"
#include"feld.h"
#include<algorithm>


using namespace std;

void quit(){
	endwin();
}

char playerChar(player p){
	switch (p){
		case playerOne:
			return '@';
			break;
		case playerTwo:
			return 'X';
			break;
		case empty:
			return ' ';
		default:
			return ' ';
	}
}

void fmake(pair<int, int> ur, feld feld){
	int size = feld.getSize();
	int urY = ur.first - 2;
	int urX = ur.second - 4;
	for(int i = 0; i < size; i++){
		mvprintw(urY, urX + i * 4, "  %c", playerChar(playerOne));
	}
	urY++;
	for(int j = 0; j < size; j++){
		int Y = urY + 2 * j;
		int X = urX + 2 * j;
		mvprintw(Y + 1, X, "%c", playerChar(playerTwo));
		mvprintw(Y + 1, X + size * 4 + 4, "%c", playerChar(playerTwo));
		for(int i = 0; i < size; i++){
			X = X + 4;
			mvprintw(Y, X - 1, "/ \\");
			mvprintw(Y + 1, X - 2, "| %c |", playerChar(feld.getPlayer(i, j)));
			mvprintw(Y + 2, X - 1, "\\ /");
		}
	}
	for(int i = 0; i < size; i++){
		mvprintw(urY + size * 2 + 1, urX + size * 2 + i * 4, "   %c", playerChar(playerOne));
	}
}

int giveHeight(feld feld){
	return feld.getSize() * 2 + 3;
}

pair<int, int> getPosition(int y, int x, pair<int, int> ur){
	y -= ur.first;
	x -= ur.second;
	y /= 2;
	x -= y * 2;
	x /= 4;
	return make_pair(x, y);
}

pair<int, int> makePosition(pair<int, int> koordinate){
	int x = koordinate.first;
	int y = koordinate.second;

	x *= 4;
	y *= 2;
	x += y;

	return make_pair(x, y);
}

void moveCursor(int y, int x, pair<int, int> &position, pair<int, int> ur, feld feld){
	int size = feld.getSize();
	while (y < 0){
		y += size;
	}
	while (x < 0){
		x += size;
	}

	position.first += x;
	position.second += y;

	position.first %= size;
	position.second %= size;

	x = position.first;
	y = position.second;

	x *= 4;
	y *= 2;
	x += y;

	y += ur.first;
	x += ur.second;

	move(y, x);
}

bool turn(pair<int, int> position, player p, feld &f){
	if (f.getField(position)->getStatus() == empty){
		f.setzen(position, p);
		return true;
	}
	else {
		return false;
	}
}

player nextTurn(player p){
	switch (p){
		case playerOne:
			p = playerTwo;
			break;
		case playerTwo:
			p = playerOne;
			break;
		case empty:
			p = playerOne;
			break;
	}
	return p;
}

void lastPrintw(pair<int, int> ur, feld feld, char* text){
	int size = feld.getSize();
	size *= 2;
	size += 3;
	mvprintw(ur.first + size, ur.second + size, text);
}

void redraw(pair<int, int> ur, feld feld){
	clear();
	fmake(ur, feld);
	refresh();
}

char* getCmdOption(char ** begin, char ** end, const string option){
	char ** itr = find(begin, end, option);
	if (itr != end && ++itr != end){
		return *itr;
	}
	return 0;
}

bool cmdOptionExists(char** begin, char** end, const string& option){
	return find(begin, end, option) != end;
}

int main(int argc, char* argv[]){

	//printf("%c]0;%s%c", '\033', "nchex", '\007');

	int size = 10;
	int uX = 5;
	int uY = 4;
	pair<int, int> ur = make_pair(uY + 2, uX + 2);

	if(cmdOptionExists(argv, argv+argc, "-n")){
		size = atoi(getCmdOption(argv, argv + argc, "-n"));
	}

	feld f = feld(size);
	player winner = empty;
	player p = playerOne;
	char player;

	initscr();
	noecho();
	keypad(stdscr, true);
	atexit(quit);
	curs_set(0);

	/*
	 if (can_change_color()) {
	 mvprintw(30, 5, "Yes you can");
	 }
	 */

	fmake(ur, f);
	refresh();

	while (winner == empty){
		player = playerChar(p);
		mvprintw(giveHeight(f) + uY + 2, giveHeight(f) + uX + 2, "Spieler %c ist am Zug", player);
		refresh();

		//if p interaktiv

		move(ur.first, ur.second);
		pair<int, int> position = make_pair(0, 0);
		bool m = false;
		int ch;
		while (!m){
			int a, b;
			getyx(stdscr, a, b);
			mvprintw(1, 4, "X: %d  Y: %d  ", position.first, position.second);
			move(a, b);
			curs_set(1);
			ch = getch();
			switch(ch){
				case KEY_UP:
				case 'k':
				case 'w':
					//redraw(ur, f);
					fmake(ur, f);
					moveCursor(-1, 0, position, ur, f);
					break;

				case KEY_DOWN:
				case 'j':
				case 's':
					//redraw(ur, f);
					fmake(ur, f);
					moveCursor(1, 0, position, ur, f);
					break;

				case KEY_LEFT:
				case 'h':
				case 'a':
					//redraw(ur, f);
					fmake(ur, f);
					moveCursor(0, -1, position, ur, f);
					break;

				case KEY_RIGHT:
				case 'l':
				case 'd':
					//redraw(ur, f);
					fmake(ur, f);
					moveCursor(0, 1, position, ur, f);
					break;

				case ' ':
					//redraw(ur, f);
					fmake(ur, f);
					m = turn(position, p, f);
					if (m){
						addch(player | A_BOLD);
					}
					break;
			}
			refresh();
		}
		curs_set(0);
		move(ur.first, ur.second);
		//fmake(ur, f);
		redraw(ur, f);
		//refresh();

		if (f.pruefe(p)){
			winner = p;
		}
		else {
			p = nextTurn(p);
		}
	}
	mvprintw(giveHeight(f) + uY + 2, giveHeight(f) + uX + 2, "Spieler %c hat Gewonnen", player);

	getch();
	return 0;
}

