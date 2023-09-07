#include "Testing.hpp"
#include "Game.hpp"

#include <iostream>
#include <string>


int main(int argc, char** argv)
{
    Testing testing(argc, argv);
	testing.shootingOverNetScenario();
	//testing.newRandomScenario(); 

	return 0;
}