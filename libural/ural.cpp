/*
 *   Данная программа является свободным программным обеспечением. Вы
 *   вправе распространять её и/или модифицировать в соответствии с
 *   условиями версии 2, либо по вашему выбору с условиями более поздней
 *   версии Стандартной Общественной Лицензии GNU, опубликованной Free
 *   Software Foundation.

 *   Мы распространяем данную программу в надежде на то, что она будет
 *   вам полезной, однако НЕ ПРЕДОСТАВЛЯЕМ НА НЕЁ НИКАКИХ ГАРАНТИЙ, в том
 *   числе ГАРАНТИИ ТОВАРНОГО СОСТОЯНИЯ ПРИ ПРОДАЖЕ и ПРИГОДНОСТИ ДЛЯ
 *   ИСПОЛЬЗОВАНИЯ В КОНКРЕТНЫХ ЦЕЛЯХ. Для получения более подробной
 *   информации ознакомьтесь со Стандартной Общественной Лицензией GNU.

 *   Вместе с данной программой вы должны были получить экземпляр
 *   Стандартной Общественной Лицензии GNU. Если вы его не получили,
 *   сообщите об этом в Free Software Foundation, Inc.,
 *   51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
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
