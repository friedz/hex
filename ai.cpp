#include"ai.h"
#include<stdlib.h>

using namespace std;

player notThisOne(player thisOne) {
	switch(thisOne) {
		case playerOne:
			return playerTwo;

		case playerTwo:
			return playerOne;

		default:
			return empty;
	}
}

void ai::buildGraph(player now) {
	const int size = (this->game)->getSize();
	this->graph = vector<vector<node> >(size, vector<node>(size));
	player enemy = notThisOne(now);
	srand(time(NULL));
	for(int x = 0; x < size; x++) {
		for(int y = 0; y < size; y++) {
			this->graph[x][y] = node(x, y);

			// neighbor
			if(x - 1 >= 0 && this->status(x, y) != enemy) {
				this->graph[x][y].neigbor.push_back(pair<int, int>(x - 1, y));
			}
			if(x + 1 < size && this->status(x + 1, y) != enemy) {
				this->graph[x][y].neigbor.push_back(pair<int, int>(x + 1, y));
			}
			if(x - 1 >= 0 && y + 1 < size && this->status(x - 1, y + 1) != enemy) {
				this->graph[x][y].neigbor.push_back(pair<int, int>(x - 1, y + 1));
			}
			if(y - 1 >= 0 && this->status(x, y - 1) != enemy) {
				this->graph[x][y].neigbor.push_back(pair<int, int>(x, y - 1));
			}
			if(y + 1 < size && this->status(x, y + 1) != enemy) {
				this->graph[x][y].neigbor.push_back(pair<int, int>(x, y + 1));
			}
			if(x + 1 < size && y - 1 >= 0 && this->status(x + 1, y - 1) != enemy) {
				this->graph[x][y].neigbor.push_back(pair<int, int>(x + 1, y - 1));
			}

			// weight
			if(this->status(x, y) == now) {
				this->graph[x][y].weight = this->myWeight;
			} else if(this->status(x, y) == empty) {
				this->graph[x][y].weight = rand()
					% (this->emptyWeight.second - this->emptyWeight.first)
					+ this->emptyWeight.first;
			} else {
				this->graph[x][y].weight = this->emptyWeight.second * 100;
			}
		}
	}
	// return graph;
}


player ai::status(int x, int y) {
	return this->game->getField(x, y)->getStatus();
}


vector<pair<int, int> > ai::dijkstra(player now) {

}


void ai::turn() {
	this->buildGraph(this->me);
	for(int i = 0; i < this->graph.size(); i++) {
		for(int j = 0; j < this->graph.size(); j++) {
			cout << this->graph[i][j].weight << ' ';
		}
		cout << '\n';
	}
	//vector<pair<int, int> > myPath = dijkstra(this.me);
	this->buildGraph(notThisOne(this->me));
	for(int i = 0; i < this->graph.size(); i++) {
		for(int j = 0; j < this->graph.size(); j++) {
			cout << this->graph[i][j].weight << ' ';
		}
		cout << '\n';
	}
	//vector<pair<int, int> > enemyPath = dijkstra(notThisOne(this.me));
	//pair<int, int> desiredField = crossPoint(myPath, enemyPath);
	//this->game.setzen(desiredField, this.me);
}
