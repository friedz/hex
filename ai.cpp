#include<ai.h>
#include<stdlib.h>

using namespace std;

vector<vector<node> > ai::buildGraph(player now) {
	const int size = (this->game).getSize()
	vector<vector<node> > graph[size][size];
	player enemy;
	switch(now) {
		case playerOne:
			enemy = playerTwo;
			break;
		case playerTwo:
			enemy = playerOne;
			break;
	}
	for(int x = 0; x < size; x++) {
		for(int y = 0; y < size; y++) {
			graph[x][y] = node(x, y);

			// neighbor
			if(x - 1 >= 0 && this.status(x, y) != enemy) {
				graph[x][y].neighbor.push_back(pair<int, int>(x - 1, y));
			}
			if(x + 1 >= 0 && this.status(x + 1, y) != enemy) {
				graph[x][y].neighbor.push_back(pair<int, int>(x + 1, y));
			}
			if(x - 1 >= 0 && y + 1 <= size && this.status(x - 1, y + 1) != this.enemy) {
				graph[x][y].neighbor.push_back(pair<int, int>(x - 1, y + 1));
			}
			if(y - 1 >= 0 && this.status(x, y - 1) != enemy) {
				graph[x][y].neighbor.push_back(pair<int, int>(x, y - 1));
			}
			if(y + 1 >= 0 && this.status(x, y + 1) != this.enemy) {
				graph[x][y].neighbor.push_back(pair<int, int>(x, y + 1));
			}
			if(x + 1 <= size && y - 1 >= 0 && this.status(x + 1, y - 1) != this.enemy) {
				graph[x][y].neighbor.push_back(pair<int, int>(x + 1, y - 1));
			}

			// weight
			switch(this.status(x, y) {
				case now:
					graph[x][y].weight = this.meWeight;
					break;
				case empty:
					graph[x][y].weight = rand()
						% (this.emptyWeight.second - this.emptyWeight.first)
						+ this.emptyWeights.first;
					break;
				case enemy:
					graph[x][y].weight = this.emptyWeight.second * 100;
					break;
			}
		}
	}
	return graph;
}

player ai::status(int x, int y) {
	return this->game.getField(x, y)->getStatus();
}
