/*
 * This file is part of EMURAL - emulator for Ural computer from 1950s
 * Copyright (C) 2015-2024 Andrey V. Skvortsov <starling13@gmail.com>
 *
 * EMURAL is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include <cstdlib>
#include <cassert>
#include <cstring>
#include <ctime>

#include <iostream>
#include <bitset>
#include <stdexcept>

#include "ural.hpp"

URAL::Word::Word(int64_t value) :
dPrec(value)
{
}

URAL::HalfWord
URAL::Word::operator[](uint8_t index) const
{
	assert((index > 0) && (index < 3));

	URAL::HalfWord result;

	if (index == 1)
		result.data = this->halfWords.most;
	else
		result.data = this->halfWords.least;

	return (result);
}

std::ostream&
operator<<(std::ostream &stream, const URAL::Word_t &word)
{
	char sign;

	stream << "Данные: " <<
	    std::hex << word.data << '\n' <<
	    u8"Слово двойной точности: ";
	if (word.dPrec.sign())
		sign = '-';
	else
		sign = '+';
	stream << sign << word.dPrec.magnitude() << '\n' <<
	    u8"Восьмеричные триплеты: " << std::oct <<
	    sign <<
        word.triplets.t12 << ' ' <<
	    word.triplets.t11 << ' ' <<
	    word.triplets.t10 << ' ' <<
	    word.triplets.t9 << ' ' <<
	    word.triplets.t8 << ' ' <<
	    word.triplets.t7 << ' ' <<
	    word.triplets.t6 << ' ' <<
	    word.triplets.t5 << ' ' <<
	    word.triplets.t4 << ' ' <<
	    word.triplets.t3 << ' ' <<
	    word.triplets.t2 << ' ' <<
	    word.triplets.t1 << '\n' <<
	    u8"Десятичные квартеты: " << std::dec <<
	    sign <<
	    word.quartets.q8 << ' ' <<
	    word.quartets.q7 << ' ' <<
	    word.quartets.q6 << ' ' <<
	    word.quartets.q5 << ' ' <<
	    word.quartets.q4 << ' ' <<
	    word.quartets.q3 << ' ' <<
	    word.quartets.q2 << ' ' <<
	    (word.quartets.q1 << 1) << ' ' << '\n';

	return (stream);
}

std::ostream&
operator<<(std::ostream &stream, const URAL::HalfWord_t &word)
{
	char sign;

	stream << "Данные: " <<
	    std::hex << word.data << '\n' <<
	    u8"Слово обычной точности: ";
	if (word.value.sign)
		sign = '-';
	else
		sign = '+';
	stream << sign << word.value.module << '(' << double(word.sPrec) << ')' << '\n' <<
	    u8"Восьмеричные триплеты: " << std::oct <<
	    word.triplets.t6 << ' ' <<
	    word.triplets.t5 << ' ' <<
	    word.triplets.t4 << ' ' <<
	    word.triplets.t3 << ' ' <<
	    word.triplets.t2 << ' ' <<
	    word.triplets.t1 << '\n' <<
	    u8"Команда:\n" << u8"\tпризнак переадресации: " << word.command.indexFlag <<
	    u8" код операции: " << word.command.opCode << u8" признак длины ячейки: " <<
	    word.command.addrLength << u8" адрес: " << word.command.address;

	return (stream);
}

URAL::Adder::Adder(AdderWord val) :
value(val)
{
}

URAL::Adder&
    URAL::Adder::operator=(const Adder &other)
{
	this->data = other.data;

	return (*this);
}


URAL::PunchTape::PunchTape()
{
}

URAL::PunchTape::~PunchTape()
{
}

void
URAL::PunchTape::loadData(const uint8_t *data, size_t size)
{
	URAL::Number  buffer;
	size_t position;

	_data.clear();
	position = 0;
	while (size >= position+11) {
		for (int i=0; i<11; ++i)
			buffer.data[i] = data[position+i];
		_data.push_back(buffer);
		position += 11;
	}
}

void
URAL::PunchTape::saveData(uint8_t *data, size_t size)
{
	int position;

	position = 0;
	for (URAL::Number &number : _data) {
		for (unsigned i=0; i<11; ++i) {
			assert(position+i < size);
			data[position+i] = number.data[i];
		}
		position += 11;
	}
}
