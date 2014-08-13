#ifndef AI_H
#define AI_H

#include<vector>
#include"stein.h"
#include"feld.h"
#include<iostream>

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
};

struct compare {
	bool operator() (const node a, const node b) const {
		return a.weight < b.weight;
	}
};

class ai {
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
		/* need switch what player is checkt */
		pair<int, int> crossPoint(vector<pair<int, int> >, vector<pair<int, int> >);

	public:
		// ai(); // propably not a good idea
		ai(feld * f) : game(f), myWeight(0), emptyWeight(1, 5) {}
		ai(feld * f, player p) : game(f), me(p), myWeight(0), emptyWeight(1, 5) {}

		void changeWeights(int, pair<int, int>);

		void turn();

};

#endif //AI_H

