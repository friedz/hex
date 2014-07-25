#ifndef NCIO_H
#define NCIO_H

#include<iostream>
#include<ncurses.h>
#include<stdlib.h>
//#include<string>
#include"stein.h"
#include"feld.h"

using namespace std;

class ncio : public feld {
	protected:
		char[3] player = {' ', '@', 'X'};

	public:
		void setPlayer(char, char, char);
		void setE(char);
		void setP1(char);
		void setP2(char);

		char * getPlayer();
		char getE();
		char getP1();
		char getP2();

		void putToken();
		void putToken(pair<int, int>);

		ncio();
		ncio(int);
		ncio(char*);
		ncio(int, char*);

};

class ncboard {
	private:
		pair<int, int> ur;
		ncio &game;
		WINDOW * board;

	public:
		void move(pair<int, int>);

		pair<int, int> getUr();
		int getHeight();
		int getWith();

		void turn(player);

		void printBoard();

		ncboard(ncio&);
		ncboard(ncio&, pair<int, int>);

};

class ncstatus {
	private:
		pair<int, int> ur;
		ncio &game;
		WINDOW * status;

	public:
		void move(pair<int, int>);

		pair<int, int> getUr();
		int getHeight();
		int getWith();

		void printStatus();

		ncstatus(ncio);
		ncstatus(ncio, pair<int, int>);

};

#endif //NCIO_H
