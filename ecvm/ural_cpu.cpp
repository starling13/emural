/*
 *   emural - эмулятор ЭЦВМ семейства "Урал"
 *
 *   Copyright (C) 2015 А.В. Скворцов <starling13@gmail.com>
 *
 *   Данная программа является свободным программным обеспечением. Вы
 *   вправе распространять её и/или модифицировать в соответствии с
 *   условиями версии 2, либо по вашему выбору с условиями более поздней
 *   версии Стандартной Общественной Лицензии GNU, опубликованной Free
 *   Software Foundation.
 *
 *   Мы распространяем данную программу в надежде на то, что она будет
 *   вам полезной, однако НЕ ПРЕДОСТАВЛЯЕМ НА НЕЁ НИКАКИХ ГАРАНТИЙ, в том
 *   числе ГАРАНТИИ ТОВАРНОГО СОСТОЯНИЯ ПРИ ПРОДАЖЕ и ПРИГОДНОСТИ ДЛЯ
 *   ИСПОЛЬЗОВАНИЯ В КОНКРЕТНЫХ ЦЕЛЯХ. Для получения более подробной
 *   информации ознакомьтесь со Стандартной Общественной Лицензией GNU.
 *
 *   Вместе с данной программой вы должны были получить экземпляр
 *   Стандартной Общественной Лицензии GNU. Если вы его не получили,
 *   сообщите об этом в Free Software Foundation, Inc.,
 *   51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
 */

#include "ural_cpu.hpp"

#include <cstdlib>
#include <ctime>
#include <cstring>
#include <cassert>

#include <iostream>

URAL::CPU::CPU(IPrintDevice &pDevice, IExtMemoryDevice &punchReader) :
	S(0),
	_controlSwitchRegister(0),
	_reg_SCHK(0),
	_DSHK(0),
	_controlRegisterAddress(0),
	_powerState(OFF),
	_phiBlock(false),
	_phiStop(false),
	_printMode(PRINT_NONE),
	_printDevice(pDevice),
	_punchReader(punchReader),
	_opState(OP_IDLE)
{
	std::srand(std::time(NULL));

	// Инициализация массива указателей на функции-члены операций
	std::memset(this->commands, 0, sizeof (this->commands));
	this->commands[OP_IDLE][000] = &CPU::noop_00;
	this->commands[OP_IDLE][001] = &CPU::sum1_01;
	this->commands[OP_IDLE][002] = &CPU::sum2_02;
	this->commands[OP_IDLE][003] = &CPU::sub1_03;
	this->commands[OP_IDLE][004] = &CPU::sub2_04;
	this->commands[OP_IDLE][005] = &CPU::mul1_05;
	this->commands[OP_IDLE][006] = &CPU::mul2_06;
	this->commands[OP_IDLE][016] = &CPU::mov_16;
	this->commands[OP_IDLE][017] = &CPU::loadR_17;
	this->commands[OP_IDLE][020] = &CPU::load_20;
	this->commands[OP_IDLE][021] = &CPU::jmp_21;
	this->commands[OP_IDLE][022] = &CPU::jmp_22;
	this->commands[OP_IDLE][023] = &CPU::cjmp_23;
	this->commands[OP_IDLE][032] = &CPU::print_32;
	this->commands[OP_IDLE][034] = &CPU::feed_34;

	this->commands[OP_GROUP_START][001] = &CPU::groupTapeRead_01;

	// Неопределённые значения регистров
	S.value = std::rand();
	R.dPrec = std::rand();
	_reg_SCHK = std::rand() & (drumHalfWordsNumber - 1);
	_RGK.data = std::rand();

	_addressStopReg._data = 0;
	_statusReg._data = 0;
}

URAL::CPU::~CPU()
{
}

void URAL::CPU::printAdder()
{
	URAL::Word_t word;
	word.dPrec = S.value;
	_printDevice.printWord(word);
}

void URAL::CPU::printCommand()
{
	_printDevice.printCommand(_reg_SCHK, _RGK);
}

void URAL::CPU::reset()
{
	S.value = 0;
	R.dPrec = 0;
	_reg_SCHK = 0;
	_RGK.data = 0;
	_DSHK = 0;
	_statusReg._data = 0;
	_statusReg._value._stop = 1;
}

void
URAL::CPU::start()
{
	_statusReg._value._stop = READY;
}

void
URAL::CPU::stop()
{
	_statusReg._value._stop = STOP;
}

void
URAL::CPU::clearDrum()
{
	std::memset(&drum, 0, sizeof (drum));
}

const URAL::Word_t&
URAL::CPU::controlRegister() const
{
	return (drum[_controlRegisterAddress]);
}

void
URAL::CPU::setControlRegisterAddress(size_t newVal)
{
	if (newVal & addressLengthBit)
		newVal = (newVal & ~addressLengthBit);
	newVal >>= 1;
	assert(newVal < drumWordsNumber);

	_controlRegisterAddress = newVal;
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
	if (_printMode > PRINT_MODE1)
		printAdder();
	if ((this->S.value.sign() == 3) || (this->S.value.sign() == 0))
		this->_statusReg._value._phi = 0;
	else
		this->_statusReg._value._phi = 1;
	fetch();
	if (_printMode > PRINT_NONE)
		printCommand();
	if (_statusReg._value._stop == READY)
		return (true);
	else {
		return (false);
	}
}

void
URAL::CPU::singleStep()
{
	this->tact();
	_statusReg._value._stop = STOP;
}

void
URAL::CPU::execute()
{
	this->_DSHK = this->_RGK.command.opCode;

	assert(this->_opState < OP_NUMBER);
	if (this->commands[this->_opState][this->_DSHK]) {
		(this->*(this->commands[this->_opState][this->_DSHK]))();
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
	// Проверка наличия остановки по адресу
	if (this->_addressStopReg.value._useBlock)
		if (this->_addressStopReg.value._address ==
		    this->_reg_SCHK)
			this->_statusReg._value._stop = STOP;
	// Проверка реакции на флаг переполнения
	if (!_phiBlock && this->_statusReg._value._phi) {
		if (_phiStop)
			this->_statusReg._value._stop = STOP;
		else
			++this->_reg_SCHK;
	}
}

void
URAL::CPU::loadReg(Word_t &reg)
{
	Word_t value;

	value = drum[_RGK.command.address >> 1];
	// Если используется полная ячейка
	if (_RGK.command.addrLength)
		reg = value;
	// Если используется половинная
	else
		reg.halfWords.most =
				value[_RGK.command.address % 2 + 1].data,
				reg.halfWords.least = 0;
}

void
URAL::CPU::multiply()
{
	bool sign;

	// Обнуление дополнительного регистра и дополнительного сумматора
	this->_DSM = this->_DRG = 0;
	// Вычисление знака произведения
	sign = _RGM.dPrec.sign() != R.dPrec.sign();
	if (sign)
		R.dPrec._sign = 1;
	else
		R.dPrec._sign = 0;
	for (unsigned i=0; i<35; ++i) {
		std::cout << "СМ " << std::bitset<18>(S.words.word2) << ' ' <<
			     std::bitset<18>(S.words.word1) << std::endl;
		std::cout << "РГАУ " << std::bitset<18>(R.halfWords.most) <<
			     ' ' << std::bitset<18>(R.halfWords.least) << std::endl;
		std::cout << "РГМ " << std::bitset<9>(_RGM.quaters.q4) << std::endl;
		std::cout << "ДРГ " << std::bitset<6>(_DRG) << std::endl;
		std::cout << "ДСМ " << std::bitset<7>(_DSM) << std::endl;
		_DRG >>= 1;
		_DRG |= R.bits.b1 << 5;
		R.dPrec._magnitude >>= 1;
		_RGM.data <<=1;
		if (_RGM.bits.b36) {
			if (sign) {
				_DSM += ~_DRG & 077;
			} else {
				_DSM += _DRG & 077;
			}
			S.value += R.dPrec;
		}
		// Перенос старшего разряда из дополнительного регистра в сумматор
		if (_DSM > 077) {
			S.value._magnitude += 1;
			_DSM &= 077;
		}
	}
	// Округление результата
	if (S.value._sign == 0) {
		if (_DSM >= 040)
			S.value._magnitude += 1;
	} else if (S.value._sign == 3) {
		if (_DSM <= 037)
			S.value._magnitude -= 1;
	}
	this->R.data = 0;
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
	loadReg(this->R);
	this->S.value += this->R.dPrec;
	if (this->S.value.sign() == 3)
		this->_statusReg._value._omega = 1;
	else
		this->_statusReg._value._omega = 0;
	++this->_reg_SCHK;
}

void
URAL::CPU::groupTapeRead_01()
{
	_opState = OP_GROUP_SELECTED;
	_groupMode = TAPE_MAGNET_READ;
	_tapeZone = _RGK.command.address;
	_tapeAddressMode = _RGK.command.addrLength;
	++this->_reg_SCHK;
}

void
URAL::CPU::sum2_02()
{
	loadReg(this->R);
	this->S.value = this->R.dPrec;
	if (this->S.value.sign() == 3)
		this->_statusReg._value._omega = 1;
	else
		this->_statusReg._value._omega = 0;
	++this->_reg_SCHK;
}

void
URAL::CPU::sub1_03()
{
	loadReg(this->R);
	this->S.value -= this->R.dPrec;
	if (this->S.value.sign() == 3)
		this->_statusReg._value._omega = 1;
	else
		this->_statusReg._value._omega = 0;
	++this->_reg_SCHK;
}

void
URAL::CPU::sub2_04()
{
	loadReg(this->R);
	this->S.value = abs(this->S.value) - abs(this->R.dPrec);
	if (this->S.value.sign() == 3)
		this->_statusReg._value._omega = 1;
	else
		this->_statusReg._value._omega = 0;
	++this->_reg_SCHK;
}

void
URAL::CPU::mul1_05()
{
	loadReg(this->_RGM);

	multiply();
	if (this->S.value.sign() == 3)
		this->_statusReg._value._omega = 1;
	else
		this->_statusReg._value._omega = 0;
	++this->_reg_SCHK;
}

void
URAL::CPU::mul2_06()
{
	loadReg(this->_RGM);
	this->R.dPrec = this->S.value;
	this->S.data = 0;

	multiply();
	if (this->S.value.sign() == 3)
		this->_statusReg._value._omega = 1;
	else
		this->_statusReg._value._omega = 0;
	++this->_reg_SCHK;
}

void
URAL::CPU::mov_16()
{
	//Значение сумматора в прямом коде
	Word_t adderValue;
	adderValue.dPrec = this->S.value;
	//Ссылка на двойную ячейку
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

	if (this->S.value.sign() == 3)
		this->_statusReg._value._omega = 1;
	else
		this->_statusReg._value._omega = 0;
	++this->_reg_SCHK;
}

void
URAL::CPU::loadR_17()
{
	loadReg(this->R);
	if (this->R.dPrec.magnitude() == 0)
		this->_statusReg._value._omega = 1;
	else
		this->_statusReg._value._omega = 0;
	++this->_reg_SCHK;
}

void
URAL::CPU::load_20()
{
	if (this->_RGK.command.addrLength == 0) {
		this->S.words.word2 = this->_RGK.command.address;
		this->S.words.word1 = 0;
		this->S.value._sign = 0;
		this->_statusReg._value._omega = 1;
	} else {
		this->S.words.word2 = ~this->_RGK.command.address;
		this->S.words.word1 = 0;
		this->S.value._sign = 3;
		this->_statusReg._value._omega = 0;
	}
	++this->_reg_SCHK;
}

void
URAL::CPU::jmp_21()
{
	if (this->_statusReg._value._omega)
		this->_reg_SCHK = this->_RGK.command.address;
	else
		++this->_reg_SCHK;
}

void
URAL::CPU::jmp_22()
{
	this->_reg_SCHK = this->_RGK.command.address;
}

void
URAL::CPU::cjmp_23()
{
	++this->_reg_SCHK;
	if (_controlSwitchRegister & (1 << this->_RGK.triplets.t1))
		++this->_reg_SCHK;
}

void
URAL::CPU::group_31()
{
	this->_opState = OP_GROUP_START;
	this->_groupOpStartAddress = this->_RGK.command.address;
	++this->_reg_SCHK;
}

void
URAL::CPU::print_32()
{
	this->_printDevice.printResult(this->drum[_RGK.command.address >> 1]);
	++this->_reg_SCHK;
}

void
URAL::CPU::feed_34()
{
	this->_printDevice.lineFeed();
	++this->_reg_SCHK;
}
