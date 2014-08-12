#ifndef AI_H
#define AI_H

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
};

struct compare {
	bool operator() (const node a, const node b) const {
		return a.weight < b.weight;
	}
};

class ai {
	protected:
		feld * game;
		player me = playerTwo;
		player enemy = playerOne;
		vector<vector<node> > graph;

		int myWeight = 0;
		pair<int, int> emptyWeight = (1, 5);

		player status(int, int);

		/* builds the graph with weights
		 * selected for a given player */
		vector<vector<node> > buildGraph(player);

		vector<pair<int, int> > dijkstra(player);
		/* need switch what player is checkt */

	puplic:
		// ai(); // propably not a good idea
		ai(feld);
		ai(feld, player);

};

#endif //AI_H

