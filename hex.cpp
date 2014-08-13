#include<iostream>
#include"stein.h"
#include"feld.h"
#include<string>
#include"ai.h"

using namespace std;

int getNumber(string text){
	cout << text << " ";
	int i;
	cin >> i;
	return --i;
}

bool outOfBorder(int i, feld f){
	if (i < 0){
		cout << "  Die Koordinate ist zu Klein und liegt auserhalb des Feldes";
		return true;
	}
	else if (i > f.getSize()){
		cout << "  Die Koordinate ist zu Groß und liegt auserhab des Feldes";
		return true;
	}
	else 
		return false;
}

void input(player p, feld &f){
	string tX = "Gib die X-Koordinate ein:";
	string tY = "Gib die Y-Koordinate ein:";
	int x = -1;
	int y = -1;
	do {
		x = getNumber(tX);
		while (outOfBorder(x, f)){
			x = getNumber(tX);
		}
		y = getNumber(tY);
		while (outOfBorder(y, f)){
			y = getNumber(tY);
		}
		if ((f.getField(x, y)->getStatus()) != empty){
			cout << "Dieses Feld ist bereits Belegt" << endl;
			x = -1;
			y = -1;
		}
	} while (x == -1 && y == -1);
	f.setzen(x, y, p);
}

player nextTurn(player p){
	cout << "Player: ";
	switch (p){
		case playerOne:
			p = playerTwo;
			cout << "\"X\" ";
			break;
		case playerTwo:
			p = playerOne;
			cout << "\"@\" ";
			break;
		default:
			p = playerOne;
	}
	cout << "ist am zug" << endl;

	return p;
}

int main(){
	feld f;
	ai bolle = ai(&f, playerTwo);
	player winner = empty;
	f.print();
	player p = playerOne;
	cout << "Player: \"@\" ist am zug" << endl;
	while (winner == empty){
		switch(p) {
			case playerOne:
				input(p, f);
				break;

			case playerTwo:
				bolle.turn();
				break;
		}
			
		f.print();
		if (f.pruefe(p)){
			winner = p;
		}
		else {
			p = nextTurn(p);
		}
	}
	cout << "Spieler ";
	switch(winner){
		case playerOne:
			cout << "@ ";
			break;
		case playerTwo:
			cout << "X ";
			break;
	}
	cout << "hat Gewonnen" << endl;

	return 0;
}
