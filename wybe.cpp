#include"wybe.h"
#include<queue>
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

void wybe::buildGraph(player now) {
	const unsigned long size = (this->game)->getSize();
	this->graph = vector<vector<node> >(size, vector<node>(size));
	player enemy = notThisOne(now);
	srand(time(NULL));
	for(unsigned long x = 0; x < size; x++) {
		for(unsigned long y = 0; y < size; y++) {
			this->graph[x][y] = node(x, y);

			// neighbor
			if(x > 0 && this->status(x, y) != enemy) {
				this->graph[x][y].neigbor.push_back(pair<int, int>(x - 1, y));
			}
			if(x + 1 < size && this->status(x + 1, y) != enemy) {
				this->graph[x][y].neigbor.push_back(pair<int, int>(x + 1, y));
			}
			if(x > 0 && y + 1 < size && this->status(x - 1, y + 1) != enemy) {
				this->graph[x][y].neigbor.push_back(pair<int, int>(x - 1, y + 1));
			}
			if(y > 0 && this->status(x, y - 1) != enemy) {
				this->graph[x][y].neigbor.push_back(pair<int, int>(x, y - 1));
			}
			if(y + 1 < size && this->status(x, y + 1) != enemy) {
				this->graph[x][y].neigbor.push_back(pair<int, int>(x, y + 1));
			}
			if(x + 1 < size && y > 0 && this->status(x + 1, y - 1) != enemy) {
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
}


player wybe::status(int x, int y) {
	return this->game->getField(x, y)->getStatus();
}


vector<pair<int, int> > wybe::dijkstra(player now) {
	priority_queue<priorityNode, vector<priorityNode>, compare> queue;

	pair<int, int> last (0, 0);
	priorityNode cuNode;
	node *nodeNow;
	for(unsigned long i = 0; i < this->graph.size(); i++) {
		switch(now) {
			case playerOne:
				nodeNow = &this->graph[i][0];
				break;
			case playerTwo:
				nodeNow = &this->graph[0][i];
				break;
			default:
				nodeNow = &this->graph[0][i];
		}
		cuNode.cNode = nodeNow;
		cuNode.predecessor = nodeNow->self;
		cuNode.priority = nodeNow->weight;

		queue.push(cuNode);
	}

	while(!queue.empty()) {
		cuNode = queue.top();
		queue.pop();

		if(cuNode.cNode->checked) {
			continue;
		}
		cuNode.cNode->parent = cuNode.predecessor;
		cuNode.cNode->checked = true;

		if(cuNode.cNode->checkDestiny(now, this->graph.size())) {
			last = cuNode.cNode->self;
			break;
		}
		vector<pair<int, int> > neigbors = cuNode.cNode->neigbor;
		priorityNode nextNeigbor;
		for(unsigned long i = 0; i < neigbors.size(); i++) {
			node *nowNeigbor = &this->graph[neigbors[i].first][neigbors[i].second];
			if(!nowNeigbor->checked) {
				nextNeigbor.cNode = nowNeigbor;
				nextNeigbor.priority = nowNeigbor->weight;
				nextNeigbor.priority += cuNode.priority;
				nextNeigbor.predecessor = cuNode.cNode->self;

				queue.push(nextNeigbor);
			}
		}
	}


	vector<pair<int, int> > path;
	path.push_back(last);

	if(last == pair<int, int>(0, 0)) {
		return path;
	}

	// just needs to be something other than 0
	int significantCoordinate = 5;
	pair<int, int> parent;
	while(significantCoordinate != 0) {
		parent = this->graph[path.back().first][path.back().second].parent;
		path.push_back(parent);
		switch(now) {
			case playerOne:
				significantCoordinate = path.back().second;
				break;
			case playerTwo:
				significantCoordinate = path.back().first;
				break;
			default:
				significantCoordinate = path.back().second;
		}
	}
	return path;
}


pair<int, int> wybe::crossPoint(vector<pair<int, int> > myPath, vector<pair<int, int> > enemyPath) {
	for(unsigned long i = 0; i < myPath.size(); i++) {
		for(unsigned long j = 0; j < enemyPath.size(); j++) {
			if(myPath[i] == enemyPath[j]) {
				return myPath[i];
			}
		}
	}
	return myPath[myPath.size() / 2];
}



void wybe::turn() {
	this->buildGraph(this->me);
	vector<pair<int, int> > myPath = dijkstra(this->me);
	this->buildGraph(notThisOne(this->me));
	vector<pair<int, int> > enemyPath = dijkstra(notThisOne(this->me));
	pair<int, int> desiredField = crossPoint(myPath, enemyPath);
	this->game->setzen(desiredField, this->me);
}
