// "Testing.hpp"
#include "Game.hpp"

int main(int argc, char **argv)
{
	try
	{
		Game game;
		game.handleArgs(argc, argv);
		game.run();
	}
	catch (const std::exception &exception)
	{
		std::cerr << exception.what() << '\n';
	}

	return 0;
}