#include"stein.h"

player stein::getStatus() const {
	return this->status;
}

void stein::check(bool c){
	this->checked = c;
}

void stein::setzen(player stat){
	this->status = stat;
}

stein::stein(){
	this->status = empty;
	this->checked = false;
}

stein::stein(player stat): status(stat){
	this->checked = false;
}

bool stein::getCheck() const {
	return this->checked;
}
