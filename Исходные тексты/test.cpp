#include <cstdlib>

#include <iostream>
#include <limits>

#include "ural.hpp"

int main(int argc, char** argv)
{
	std::cout.precision(std::numeric_limits< double >::digits10);
	
	std::cout << URAL::ModOnesComplementDouble(0) << '\n' <<
	    URAL::ModOnesComplementDouble(0100000000000) << '\n' <<
	    URAL::ModOnesComplementDouble(0200000000000) << '\n' <<
	    URAL::ModOnesComplementDouble(0300000000000) << std::endl;
	
	std::cout << URAL::ModOnesComplementDouble(0) << '\n' <<
	    URAL::ModOnesComplementDouble(-0100000000000) << '\n' <<
	    URAL::ModOnesComplementDouble(-0200000000000) << '\n' <<
	    URAL::ModOnesComplementDouble(-0300000000000) << std::endl;
	
	 URAL::ModOnesComplementDouble	a(0200000000000);
	 std::cout << a+(-a) << std::endl;
	
	//for (uint64_t i=1; i<0377777777777ull; i+=65535ull)
	//	std::cout << URAL::ModOnesComplementDouble(i).floatingPointValue() << '\n';
	
	URAL::CPU	ural;
	
	ural.drum[0] = 0000001020004;
	ural.drum[1] = 0000003000002;
	ural.drum[2] = 0000005000004;
	ural.drum[3] = 0000007000006;
	ural.drum[4] = 0000011000010;
	ural.drum[5] = 0000013000012;
	
	ural.tact();
	ural.tact();
	ural.tact();
	ural.tact();
	ural.tact();
	ural.tact();
	ural.tact();
	ural.tact();
	ural.tact();
	ural.tact();
	ural.tact();
	ural.tact();
	
	return (EXIT_SUCCESS);
}          
