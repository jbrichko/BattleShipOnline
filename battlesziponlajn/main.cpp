// "Testing.hpp"
#include "Game.hpp"

int main(int argc, char **argv)
{
	Game game;
	if (!game.handleArgs(argc, argv))
		return 0;
	game.run();

	return 0;
}