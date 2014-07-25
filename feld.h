#ifndef FELD_H
#define FELD_H

#include"stein.h"
#include<vector>

using namespace std;

class feld {
	protected:
		const int size;
		vector<vector<stein> > field;

		bool test(int, int, player);

	public:
		void print();
		int getSize() const;
		void setzen(int, int, player);
		void setzen(pair<int, int>, player);
		bool pruefe(player);
		vector<vector<stein> > getField();
		stein * getField(int, int);
		stein * getField(pair<int, int>);

		player getPlayer(int, int);
		player getPlayer(pair<int, int>);

		feld();
		feld(int);

		~feld(){};
};

#endif //FELD_H
