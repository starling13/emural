#include <cstdlib>

#include <iostream>

#include "ural.hpp"

int main(int argc, char** argv)
{
	URAL::CPU	ural;
	
	ural.drum[0] = 0x12345678;
	
	ural.tact();
	ural.tact();
	ural.tact();
	
	return (EXIT_SUCCESS);
}          
