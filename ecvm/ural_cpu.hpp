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

#ifndef URAL_CPU_HPP
#define URAL_CPU_HPP

#include "ural.hpp"

class URAL::CPU
{
public:

    CPU();

    uint16_t	regSCHK() const
    {
        return (_reg_SCHK);
    }
    void setRegSCHK(uint16_t newVal)
    {
        _reg_SCHK = newVal;
    }
    uint16_t	regDSHK() const
    {
        return (_DSHK);
    }
    void setAddressBlock(uint16_t newVal)
    {
        _addressStopReg._data = newVal;
    }
    bool tact();
    void clearDrum();
    void reset();
    const Word_t	&controlRegister() const;
    void		 setControlRegisterAddress(size_t newVal);
    void setSupplyVoltage(uint8_t, float);
    bool		 omega() const
    {
        return (_statusReg._value._omega);
    }
    bool		 phi() const
    {
        return (_statusReg._value._phi);
    }
    uint8_t		statusRegister() const
    {
        return (_statusReg._data);
    }
    void		setPhiBlock(bool newVal)
    {
        _phiBlock = newVal;
    }
    void		setPhiStop(bool newVal)
    {
        _phiStop = newVal;
    }
    Word_t		R;
    Word_t		drum[drumWordsNumber];
    HalfWord_t	_RGK;

    Adder		S;

private:

    /**
     * Состояние машины по питанию
     */
    enum PowerState_t
    {
        // Не работает
        OFF,
        // Работает неустойчиво
        FLOATING,
        // Работает устойчиво
        ON
    };
    /**
     * Функциональное состояние
     */
    enum State_t
    {
        /**
         * готов к исполнению
         */
        READY,
        /**
         * Остановка
         */
        STOP
    };

    /**
     * Исполнение команды из регистра команд
     */
    void execute();
    /**
     * Загрузка команды в регистр команд
     */
    void fetch();

    void loadReg(Word_t&);

    void multiply();

    //////////////// ОПЕРАЦИИ ////////////////
    void noop_00();
    /**
     * @brief сложение
     */
    void sum1_01();
    /**
     * @brief сложение с нулём (послыка в сумматор)
     */
    void sum2_02();

    void sub1_03();

    void sub2_04();

    void mul1_05();

    void mul2_06();

    void mov_16();

    void loadR_17();

    void jmp_21();

    void jmp_22();

    /**
     * Регистр остановки по адресу
     */
    union PACKED
    {
        uint16_t	_data;
        struct
        {
            uint16_t	_address:11;
            uint16_t	_useBlock:1;
        } value;
    }	_addressStopReg;

    /**
     * Массив указателей на функции-члены операций.
     * Индекс операции в массиве равен её коду
     */
    void (CPU::*commands[32])();

    union PACKED
    {
        uint8_t	_data;
        struct
        {
            uint8_t	_omega:1;
            uint8_t	_phi:1;
        } _value;
    } _statusReg;

    /**
     * Регистр СЧК
     */
    uint16_t	_reg_SCHK:11;
    /**
     * ДШК
     */
    uint16_t	_DSHK:5;
    /*
     * РГМ
     */
    Word_t      _RGM;
    uint16_t    _DRG:6;
    uint16_t    _DSM:7;

    size_t		_controlRegisterAddress;

    PowerState_t		_powerState;

    State_t			_mode;

    // Напряжения питания (В)
    float		_supplyVoltage[2];

    bool		_phiBlock;

    bool		_phiStop;
};

#endif
