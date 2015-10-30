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

#include <cstdlib>
#include <cassert>
#include <cstring>
#include <ctime>

#include <iostream>
#include <bitset>
#include <stdexcept>

URAL::Word::Word(int64_t value) :
dPrec(value)
{
}

URAL::HalfWord
URAL::Word::operator[](uint8_t index) const
{
	assert((index > 0) && (index < 3));
	
	URAL::HalfWord	result;
	
	if (index == 1)
		result.data = this->halfWords.least;
	else
		result.data = this->halfWords.most;
	
	return (result);
}

std::ostream&
operator <<(std::ostream &stream, const URAL::Word_t &word)
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

double
URAL::HalfWord::floatingPointValue() const
{
	double res;
	
	res = double (this->value.module) *  (1.0 / double (1 << 17));
	if (this->value.sign)
		res = 0.0 - res;
	
	return (res);
}

std::ostream&
operator <<(std::ostream &stream, const URAL::HalfWord_t &word)
{
	char sign;
	
	stream << "Данные: " <<
	    std::hex << word.data << '\n' <<
		u8"Слово обычной точности: ";
	if (word.value.sign)
		sign = '-';
	else
		sign = '+';
	stream << sign << word.value.module << '(' << word.floatingPointValue() << ')' << '\n' <<
	    u8"Восьмеричные триплеты: " << std::oct <<
		sign <<
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

URAL::CPU::CPU() :
S(AdderWord(0)),
controlRegisterAddress(0),
_state(OFF)
{
	std::srand(std::time(NULL));
	
	std::memset(this->commands, 0, sizeof (this->commands));
	this->commands[0] = &CPU::noop_00;
	this->commands[1] = &CPU::sum1_01;
	this->commands[2] = &CPU::sum2_02;
	this->commands[022] = &CPU::jmp_22;
	
	S.value = std::rand();
	R.dPrec = std::rand();
	PC = std::rand() & (drumHalfWordsNumber-1);
	commandReg.data = std::rand();
}

void URAL::CPU::reset()
{
	S.value = 0;
	R.dPrec = 0;
	PC = 0;
	commandReg.data = 0;
}

void
URAL::CPU::clearDrum()
{
	std::memset(&drum, 0, sizeof (drum));
}

const URAL::Word_t&
URAL::CPU::controlRegister() const
{
	return (drum[controlRegisterAddress]);
}

void
URAL::CPU::setControlRegisterAddress(size_t newVal)
{
	if (newVal & addressLengthBit)
		newVal = (newVal & ~addressLengthBit);
	newVal >>= 1;
	assert (newVal < drumWordsNumber);

	controlRegisterAddress = newVal;
}

void
URAL::CPU::setSupplyVoltage(uint8_t index, float value)
{
	float average;
	
	assert ((index == 1) || (index == 2));
	
	_supplyVoltage[index-1] = value;
	average = (_supplyVoltage[0] + _supplyVoltage[1]) / 2.;
	if (average < 110.)
		_state = OFF;
	else if (average < 220)
		_state = FLOATING;
	else
		_state = ON;
}

void
URAL::CPU::tact()
{
	div_t	pc;
	
	assert(this->PC < drumHalfWordsNumber);
	std::cout << u8"----------ТАКТ----------\n";
	pc = std::div(this->PC, 2);
	this->commandReg = drum[pc.quot][pc.rem+1];
	std::cout << u8"Счётчик команд: " << this->PC <<
	    '\n' << this->commandReg << std::endl;
	if (this->commands[this->commandReg.command.opCode]) {
		(this->*(this->commands[this->commandReg.command.opCode]))();
	} else {
		std::cout << u8"Неизвестная операция: " << this->commandReg.
		    command.opCode << std::endl;
		++this->PC;
	}	
}

bool
URAL::CPU::doNextCommand()
{
	return (true);
}

void
URAL::CPU::noop_00()
{
	std::cout << u8"Пустая операция" << std::endl;
	++this->PC;
}

void
URAL::CPU::sum1_01()
{
	std::cout << u8"Сложение 1" << std::endl;
	
	this->S.value += drum[commandReg.command.address >> 1].dPrec;
	++this->PC;
}

void
URAL::CPU::sum2_02()
{
	std::cout << u8"Сложение 2" << std::endl;
	
	this->S.value = drum[commandReg.command.address >> 1].dPrec;
	++this->PC;
}

void
URAL::CPU::jmp_22()
{
	std::cout << u8"Безусловный переход" << std::endl;
	
	this->PC = drum[commandReg.command.address >> 1].dPrec.magnitude() &
	    (addressLengthBit-1);
}
