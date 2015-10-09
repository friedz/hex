#ifndef WYBE_H
#define WYBE_H

#include<iostream>
#include<vector>
#include"stein.h"
#include"feld.h"

using namespace std;


struct node {
	vector<pair<int, int> > neigbor;
	pair<int, int> parent;
	pair<int, int> self;
	bool checked;
	int weight;

	node(): checked(false) {}
	node(int selfFirst, int selfSecond):
		self(selfFirst, selfSecond), checked(false) {}

	bool checkDestiny(player p, int size) {
		switch(p) {
			case playerOne:
				if(this->self.second == size - 1) {
					return true;
				} else {
					return false;
				} break;

			case playerTwo:
				if(this->self.first == size - 1) {
					return true;
				} else {
					return false;
				} break;

			default:
				return false;
		}
	}
};

struct priorityNode {
	node * cNode;
	int priority;
	pair<int, int> predecessor;
};

struct compare {
	bool operator() (const priorityNode a, const priorityNode b) const {
		return a.priority > b.priority;
	}
};

class wybe {
	protected:
		feld * game;
		player me; //= playerTwo;
		//player enemy = playerOne;
		vector<vector<node> > graph;

		int myWeight; // = 0;
		pair<int, int> emptyWeight; //= (1, 5);

		player status(int, int);

		void buildGraph(player);

		vector<pair<int, int> > dijkstra(player);

		pair<int, int> crossPoint(vector<pair<int, int> >, vector<pair<int, int> >);

	public:
		wybe(feld * f):
			game(f), myWeight(5), emptyWeight(20, 50) {}
		wybe(feld * f, player p):
			game(f), me(p), myWeight(5), emptyWeight(20, 50) {}

		/*
		void changeWeights(int my, pair<int, int> empty) {
			this->myWeight = my;
			this->emptyWeight = empty;
		}
		void changeWeights(pair<int, int> empty):
			emptyWeight(empty) {}
		void changeWeights(int my):
			myWeight(my) {}
		*/

		void turn();

};

#endif //WYBE_H

