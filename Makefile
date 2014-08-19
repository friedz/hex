all: nchex
	@echo "is equivalent to 'make nchex'"
	@echo "because you want the ncurses version"

nchex: nchex.cpp stein.cpp feld.cpp wybe.cpp
	g++ -o nchex nchex.cpp stein.cpp feld.cpp wybe.cpp -lncurses -Wall -Wformat -Wextra

hex: hex.cpp stein.cpp feld.cpp
	g++ -o hex hex.cpp stein.cpp feld.cpp wybe.cpp -Wall -Wformat -Wextra

nop: hex.cpp stein.cpp feld.cpp wybe.cpp
	g++ -O0 -g3 -o hexai hex.cpp stein.cpp feld.cpp wybe.cpp
