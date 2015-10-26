#include <cstdlib>

#include <iostream>

#include "ural.hpp"

int main(int argc, char** argv)
{
	URAL::Word_t	word(255);
	URAL::Word_t	word1(-255);
	
	std::cout << word << '\n' << word1 << std::endl;
	std::cout << word1[1] << '\n' << word1[2] << std::endl;
	
	return (EXIT_SUCCESS);
}
