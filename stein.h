#ifndef STEIN_H
#define STEIN_H

enum player {
	empty,
	playerOne,
	playerTwo,
};

class stein {
	private:
		player status;
		bool checked;

	public:
		player getStatus() const;
		void check(bool);
		bool getCheck() const;

		void setzen(player);

		stein();
		stein(player);

		~stein(){};
};

#endif //STEIN_H
