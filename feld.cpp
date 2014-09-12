#include<iostream>
#include"feld.h"

using namespace std;

feld::feld(int size): size(size), field(size, vector<stein>(size) ){
}

feld::feld(): size(10), field(10, vector<stein>(10) ){
}

int feld::getSize() const {
	return this->size;
}

stein * feld::getField(int x, int y){
	return &this->field[x][y];
}

stein * feld::getField(pair<int, int> s){
	return &this->field[s.first][s.second];
}

vector<vector<stein> > feld::getField(){
	return this->field;
}

player feld::getPlayer(int x, int y){
	if(x < 0 && y >= this->size || x >= this->size && y < 0) {
		return empty;
	} else if(x < 0 || x >= this->size) {
		return playerTwo;
	} else if(y < 0 || y >= this->size) {
		return playerOne;
	} else {
		return this->field[x][y].getStatus();
	}
}
		
player feld::getPlayer(pair<int, int> s){
	return this->field[s.first][s.second].getStatus();
}

void feld::setzen(int x, int y, player p){
	this->field[x][y].setzen(p);
}

void feld::setzen(pair<int, int> f, player p){
	this->field[f.first][f.second].setzen(p);
}

bool feld::test(int x, int y, player p){
	if (x < 0 || y < 0 || x >= this->size || y >= this->size){
		return false;
	}
	else if (this->getField(x, y)->getCheck()){
		return false;
	}
	else if (this->getField(x, y)->getStatus() != p){
		this->field[x][y].check(true);
		return false;
	}
	else if ((p == playerOne && y + 1 == this->size) || (p == playerTwo && x + 1 == this->size)){
		this->field[x][y].check(true);
		return true;
	}
	else {
		this->field[x][y].check(true);
		return test(x, y - 1, p) || test(x, y + 1, p) || test(x - 1, y, p) || test(x + 1, y, p) || test(x - 1, y + 1, p) || test(x + 1, y - 1, p); // returns True if any of the sub tests returns True
	}
}

bool feld::pruefe(player p){
	for (int x = 0; x < this->size; x++){
		for(int y = 0; y < this->size; y++){
			this->field[x][y].check(false);
		}
	}
	bool res = false;
	for (int i = 0; i < this->size; i++){
		switch (p){
			case playerOne:
				res = res || this->test(i, 0, p);
				break;
			case playerTwo:
				res = res || this->test(0, i, p);
				break;
			default:
				res = false;
		}
		if (res){
			return true;
		}
	}
	for (int x = 0; x < this->size; x++){
		for(int y = 0; y < this->size; y++){
			this->field[x][y].check(false);
		}
	}
	return res;
}

void feld::print(){
	int i;
	for (i = 0; i < this->size; ++i){
		cout << " " << i + 1 << "  ";
	}
	cout << "\n ";
	for (i = 0; i < this->size; ++i){
		cout << "@" << "/ \\"; // füllt die erste zeile der ausgabe mit "/ \" sowie "@"
	}
	cout << "\n";

	for (int y = 0; y < this->size; ++y){
		for (i = 0; i < y; ++i){ // setzt ausreichend leer zeichen vor das erste zeichen
			cout << "  ";              // das das spielfeld richtig zu erkennen ist
		}
		cout << "X| ";
		for (int x = 0; x < this->size; ++x){
			switch(this->field[x][y].getStatus()){ // sorgt dafür das die jeweilige zeile mit steinen ausgegeben wird
				case empty:       // villeicht auch global setzen
					cout << " ";
					break;
				case playerOne:   // setzt das zeichen für player one (villeicht gegen globale variable zu ersetzuen)
					cout << "@";
					break;
				case playerTwo:   // selbige wie player one zu player two
					cout << "X";
					break;
			}
			cout << " | ";
		}
		cout << y + 1 << "\n";
		for (i = 0; i < y; ++i){
			cout << "  ";
		}
		cout << "  ";
		for (i = 0; i < this->size; ++i){
			cout << "\\ / "; // giebt den stuff zwischen den "wichtigen" zeilen aus ;D
		}
		if (i == this->size && y + 1 != this->size){
			cout << "\\";
		}
		cout << "\n";
	}
	cout << "\n";
}
