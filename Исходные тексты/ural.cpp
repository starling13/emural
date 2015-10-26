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
#include "ural.hpp"

#include <cassert>

#include <iostream>

URAL::Word::Word(int64_t value)
{
	this->data = 0ull;
	this->dPrec.module = std::abs(value);
	if (value < 0)
		this->dPrec.sign = 1;
	else
		this->dPrec.sign = 0;
}

URAL::HalfWord
URAL::Word::operator[](uint8_t index) const
{
	assert((index > 0) && (index < 3));
	
	URAL::HalfWord	result;
	
	if (index == 1)
		result.data = this->data;
	else
		result.data = this->data >> 18;
	
	return (result);
}

std::ostream&
operator <<(std::ostream &stream, const URAL::Word_t &word)
{
	char sign;
	
	stream << "Данные: " <<
	    std::hex << word.data << '\n' <<
		u8"Слово двойной точности: ";
	if (word.dPrec.sign)
		sign = '-';
	else
		sign = '+';
	stream << sign << word.dPrec.module << '\n' <<
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
operator <<(std::ostream &stream, const URAL::HalfWord_t &word)
{
	char sign;
	
	stream << "Данные: " <<
	    std::hex << word.data << '\n' <<
		u8"Слово обычной точности: ";
	if (word.dPrec.sign)
		sign = '-';
	else
		sign = '+';
	stream << sign << word.dPrec.module << '\n' <<
	    u8"Восьмеричные триплеты: " << std::oct <<
		sign <<
		word.triplets.t6 << ' ' <<
		word.triplets.t5 << ' ' <<
		word.triplets.t4 << ' ' <<
		word.triplets.t3 << ' ' <<
		word.triplets.t2 << ' ' <<
		word.triplets.t1 << '\n';
	
	return (stream);
}
