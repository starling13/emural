#include "ural_cpu.hpp"

#include <cstdlib>
#include <ctime>
#include <cstring>
#include <cassert>

#include <iostream>

URAL::CPU::CPU() :
S(0),
_reg_SCHK(0),
_DSHK(0),
_controlRegisterAddress(0),
_powerState(OFF),
_mode(READY),
_phiBlock(false),
_phiStop(false)
{
    std::srand(std::time(NULL));

    std::memset(this->commands, 0, sizeof (this->commands));
    this->commands[000] = &CPU::noop_00;
    this->commands[001] = &CPU::sum1_01;
    this->commands[002] = &CPU::sum2_02;
    this->commands[003] = &CPU::sub1_03;
    this->commands[004] = &CPU::sub2_04;
    this->commands[005] = &CPU::mul1_05;
    this->commands[006] = &CPU::mul2_06;
    this->commands[016] = &CPU::mov_16;
    this->commands[017] = &CPU::loadR_17;
    this->commands[021] = &CPU::jmp_21;
    this->commands[022] = &CPU::jmp_22;

    S.value = std::rand();
    R.dPrec = std::rand();
    _reg_SCHK = std::rand() & (drumHalfWordsNumber - 1);
    _RGK.data = std::rand();

    _addressStopReg._data = 0;
    _statusReg._data = 0;
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
    if ((this->S.value.sign() == 3) || (this->S.value.sign() == 0))
        this->_statusReg._value._phi = 0;
    else
        this->_statusReg._value._phi = 1;
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
    // Проверка наличия остановки по адресу
    if (this->_addressStopReg.value._useBlock)
        if (this->_addressStopReg.value._address ==
            this->_reg_SCHK)
            this->_mode = STOP;
    // Проверка реакции на флаг переполнения
    if (!_phiBlock && this->_statusReg._value._phi) {
        if (_phiStop)
            this->_mode = STOP;
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
    //if (_DSM > 040)
    //    S.value += 1;

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
