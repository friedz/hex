#include<iostream>
#include<ncurses.h>
#include<stdlib.h>
#include<string>
#include"stein.h"
#include"feld.h"
#include"wybe.h"
#include<algorithm>
#include<unistd.h>


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
	attron(0 | COLOR_PAIR(playerOne));
	for(int i = 0; i < size; i++){
		mvprintw(urY, urX + i * 4, "  %c", playerChar(playerOne));
	}
	attroff(0 | COLOR_PAIR(playerOne));
	urY++;
	for(int j = 0; j < size; j++){
		int Y = urY + 2 * j;
		int X = urX + 2 * j;
		attron(0 | COLOR_PAIR(playerTwo));
		mvprintw(Y + 1, X, "%c", playerChar(playerTwo));
		mvprintw(Y + 1, X + size * 4 + 4, "%c", playerChar(playerTwo));
		attroff(0 | COLOR_PAIR(playerTwo));
		player p;
		for(int i = 0; i < size; i++){
			p = feld.getPlayer(i, j);
			X = X + 4;

			if(feld.getPlayer(i, j - 1) == p) {
				attron(0 | COLOR_PAIR(p));
			}
			mvprintw(Y, X - 1, "/");
			attroff(0 | COLOR_PAIR(p));

			if(feld.getPlayer(i + 1, j - 1) == p) {
				attron(0 | COLOR_PAIR(p));
			}
			mvprintw(Y, X + 1, "\\");
			attroff(0 | COLOR_PAIR(p));

			if(feld.getPlayer(i - 1, j) == p) {
				attron(0 | COLOR_PAIR(p));
			}
			mvprintw(Y + 1, X - 2, "| ");
			attroff(0 | COLOR_PAIR(p));

			attron(0 | COLOR_PAIR(p));
			mvprintw(Y + 1, X, "%c", playerChar(p));
			attroff(0 | COLOR_PAIR(p));

			if(feld.getPlayer(i + 1, j) == p) {
				attron(0 | COLOR_PAIR(p));
			}
			mvprintw(Y + 1, X + 2, "|");
			attroff(0 | COLOR_PAIR(p));

			if(feld.getPlayer(i - 1, j + 1) == p) {
				attron(0 | COLOR_PAIR(p));
			}
			mvprintw(Y + 2, X - 1, "\\");
			attroff(0 | COLOR_PAIR(p));

			if(feld.getPlayer(i, j + 1) == p) {
				attron(0 | COLOR_PAIR(p));
			}
			mvprintw(Y + 2, X + 1, "/");
			attroff(0 | COLOR_PAIR(p));
		}
	}
	attron(0 | COLOR_PAIR(playerOne));
	for(int i = 0; i < size; i++){
		mvprintw(urY + size * 2 + 1, urX + size * 2 + i * 4, "   %c", playerChar(playerOne));
	}
	attroff(0 | COLOR_PAIR(playerOne));
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

bool isAi(player p, bool * ai) {
	switch(p) {
		case playerOne:
			return ai[0];
			break;
		case playerTwo:
			return ai[1];
			break;
		default:
			return false;
	}
}


int main(int argc, char* argv[]) {

	printf("%c]0;%s%c", '\033', "nchex", '\007');

	int size = 10;
	int uX = 5;
	int uY = 4;
	pair<int, int> ur = make_pair(uY + 2, uX + 2);
	bool ai[] = {false, true};

	
	if(cmdOptionExists(argv, argv+argc, "-n")){
		size = atoi(getCmdOption(argv, argv + argc, "-n"));
	} if(cmdOptionExists(argv, argv+argc, "-ki1")){
		ai[0] = true;
	} if(cmdOptionExists(argv, argv+argc, "-ki2")){
		ai[1] = true;
	} if(cmdOptionExists(argv, argv+argc, "-p1")){
		ai[0] = false;
	} if(cmdOptionExists(argv, argv+argc, "-p2")){
		ai[1] = false;
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
	start_color();

	// player color
	init_pair(playerOne, COLOR_BLUE, COLOR_BLACK);
	init_pair(playerTwo, COLOR_RED, COLOR_BLACK);

	/*
	if (can_change_color()) {
	 mvprintw(30, 5, "Yes you can do Colors");
	}
	*/

	fmake(ur, f);
	refresh();

	wybe box1 = wybe(&f, playerOne);
	wybe box2 = wybe(&f, playerTwo);

	while (winner == empty) {
		player = playerChar(p);
		mvprintw(giveHeight(f) + uY + 2, giveHeight(f) + uX + 2, "Spieler");
		attron(0 | COLOR_PAIR(p));
		mvprintw(giveHeight(f) + uY + 2, giveHeight(f) + uX + 10, "%c", player);
		attroff(0 | COLOR_PAIR(p));
		mvprintw(giveHeight(f) + uY + 2, giveHeight(f) + uX + 12, "ist am Zug");
		refresh();

		/* wenn der grade setzende spieler
		 * die KI ist */
		if(isAi(p, ai)) {
			switch(p) {
				case playerOne:
					box1.turn();
					break;
				case playerTwo:
					box2.turn();
					break;
				default:
					box2.turn();
			}
		} else {

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
						fmake(ur, f);
						moveCursor(-1, 0, position, ur, f);
						break;

					case KEY_DOWN:
					case 'j':
					case 's':
						fmake(ur, f);
						moveCursor(1, 0, position, ur, f);
						break;

					case KEY_LEFT:
					case 'h':
					case 'a':
						fmake(ur, f);
						moveCursor(0, -1, position, ur, f);
						break;

					case KEY_RIGHT:
					case 'l':
					case 'd':
						fmake(ur, f);
						moveCursor(0, 1, position, ur, f);
						break;

					case ' ':
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
		}
		redraw(ur, f);
		//refresh();

		if (f.pruefe(p)){
			winner = p;
		}
		else {
			p = nextTurn(p);
		}
	}
	mvprintw(giveHeight(f) + uY + 2, giveHeight(f) + uX + 2, "Spieler");
	attron(0 | COLOR_PAIR(p));
	mvprintw(giveHeight(f) + uY + 2, giveHeight(f) + uX + 10, "%c", player);
	attroff(0 | COLOR_PAIR(p));
	mvprintw(giveHeight(f) + uY + 2, giveHeight(f) + uX + 12, "hat Gewonnen");
	refresh();

	getch();
	return 0;
}
