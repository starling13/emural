#ifndef QCOMMON_HPP
#define QCOMMON_HPP

#include "ural.hpp"

class TapeLoader
{
protected:

	void loadTapeFromFile();

	URAL::PunchTape		 _tape;
};

#endif // QCOMMON_HPP
