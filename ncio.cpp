#include"ncio.h"

// ncio
// Seter

void ncio::setPlayer(char e, char p1, char p2){
	this.player[0] = e;
	this.player[1] = p1;
	this.player[2] = p2;
}

void ncio::setE(char e){
	this.player[0] = e;
}

void ncio::setP1(char p1){
	this.player[1] = p1;
}

void ncio::setP1(char p1){
	this.player[2] = p2;
}

// Geter

char* ncio::getPlayer(){
	return this.player;
}

char ncio::getE(){
	return this.player[0];
}

char ncio::getP1(){
	return this.player[1];
}

char ncio::getP2(){
	return this.player[2];
}

pair<int, int> ncio::getUr(){
	return this.ur;
}

int ncio::getHeight(){
}

int ncio::getWith(){
}

// ncboard
// Seter

void ncboard::move(pair<int, int>){
}

// Geter

pair<int, int> ncboard::getUr(){
	return ur;
}

int ncboard::getHeight(){
}

int ncboard::getWhith(){
}

// Play

void ncboard::turn(player){
}

void ncboard::printBoard(){
}

ncboard::ncboard(ncio &g) : game(&g) {
}

ncboard::ncboard(ncio &g, pair<int, int> u) : game(&g), ur(u) {
}
