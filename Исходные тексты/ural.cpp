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
#include "DrumWidget.hpp"

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

URAL::CPU::CPU() :
S(0),
_reg_SCHK(0),
_DSHK(0),
controlRegisterAddress(0),
_powerState(OFF),
_mode(READY)
{
	std::srand(std::time(NULL));

	std::memset(this->commands, 0, sizeof (this->commands));
	this->commands[000] = &CPU::noop_00;
	this->commands[001] = &CPU::sum1_01;
	this->commands[002] = &CPU::sum2_02;
	this->commands[003] = &CPU::sub_03;
	this->commands[016] = &CPU::mov_16;
	this->commands[017] = &CPU::loadR_17;
	this->commands[022] = &CPU::jmp_22;

	S.value = std::rand();
	R.dPrec = std::rand();
	_reg_SCHK = std::rand() & (drumHalfWordsNumber - 1);
	_RGK.data = std::rand();
	
	_addressStopReg._data = 0;
}

void URAL::CPU::reset()
{
	S.value = 0;
	R.dPrec = 0;
	_reg_SCHK = 0;
	_RGK.data = 0;
	_DSHK = 0;
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
	assert(newVal < drumWordsNumber);

	controlRegisterAddress = newVal;
}

void
URAL::CPU::setSupplyVoltage(uint8_t index, float value)
{
	float average;

	assert((index == 1) || (index == 2));

	_supplyVoltage[index - 1] = value;
	average = (_supplyVoltage[0] + _supplyVoltage[1]) / 2.;
	if (average < 110.)
		_powerState = OFF;
	else if (average < 220)
		_powerState = FLOATING;
	else
		_powerState = ON;
}

bool
URAL::CPU::tact()
{
	execute();
	fetch();
	if (_mode == READY)
		return (true);
	else {
		_mode = READY;
		return (false);
	}
}

void
URAL::CPU::execute()
{
	this->_DSHK = this->_RGK.command.opCode;
	if (this->commands[this->_DSHK]) {
		(this->*(this->commands[this->_DSHK]))();
	} else {
		std::cout << u8"Неизвестная операция: " << this->_RGK.
		    command.opCode << std::endl;
		++this->_reg_SCHK;
	}
}

void
URAL::CPU::fetch()
{
	div_t pc;

	assert(this->_reg_SCHK < drumHalfWordsNumber);
	pc = std::div(this->_reg_SCHK, 2);
	this->_RGK = drum[pc.quot][pc.rem + 1];
	if (this->_addressStopReg.value._useBlock)
		if (this->_addressStopReg.value._address ==
		    this->_reg_SCHK)
			this->_mode = STOP;
}

void
URAL::CPU::loadR()
{
	Word_t value;

	value = drum[_RGK.command.address >> 1];
	// Если используется полная ячейка
	if (_RGK.command.addrLength)
		this->R = value;
		// Если используется половинная
	else
		this->R.halfWords.most =
	    value[_RGK.command.address % 2 + 1].data,
	    this->R.halfWords.least = 0;
}

void
URAL::CPU::noop_00()
{
	++this->_reg_SCHK;
}

/**
 * К значению сумматора добавляется значение ячейки a.
 * Значение сохраняется в сумматоре, значение прибавляемого регистра не
 * меняется.
 */
void
URAL::CPU::sum1_01()
{
	loadR();
	this->S.value += this->R.dPrec;
	++this->_reg_SCHK;
}

void
URAL::CPU::sum2_02()
{
	loadR();
	this->S.value = this->R.dPrec;
	++this->_reg_SCHK;
}

void
URAL::CPU::sub_03()
{
	loadR();
	this->S.value -= this->R.dPrec;
	++this->_reg_SCHK;
}

void
URAL::CPU::mov_16()
{
	/**
	 * Значение сумматора в прямом коде
         */
	Word_t adderValue;
	adderValue.dPrec = this->S.value;
	/**
	 * Ссылка на двойную ячейку
         */
	Word_t &drumValue = drum[_RGK.command.address / 2];
	
	// Если используется полная ячейка
	if (_RGK.command.addrLength)
		drumValue.dPrec = adderValue.dPrec;
	// Если используется половинная
	else
		if (_RGK.command.address % 2)
			drumValue.halfWords.least = adderValue.halfWords.most;
		else
			drumValue.halfWords.most = adderValue.halfWords.most;
	
	++this->_reg_SCHK;
}

void
URAL::CPU::loadR_17()
{
	loadR();
	++this->_reg_SCHK;
}

void
URAL::CPU::jmp_22()
{
	this->_reg_SCHK = this->_RGK.command.address;
}
