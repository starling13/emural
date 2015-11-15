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

/**
 * @brief Процессор Урал-1 (АУ и УУ)
 */
class URAL::CPU
{
public:
    /**
     * @brief Конструктор
     * @param printDevice ссылка на экземпляр реализации ЦПУ
     */
    CPU(IPrintDevice&);
    ~CPU();

    void printAdder();
    void printCommand();

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

    bool		 omega() const
    {
        return (_statusReg._value._omega);
    }
    bool		 phi() const
    {
        return (_statusReg._value._phi);
    }
    uint16_t		statusRegister() const
    {
        return (_statusReg._data);
    }

    bool tact();

    void clearDrum();
    void reset();
    const Word_t	&controlRegister() const;
    void		 setControlRegisterAddress(size_t newVal);
    void setSupplyVoltage(uint8_t, float);

    void		setPhiBlock(bool newVal)
    {
        _phiBlock = newVal;
    }
    void		setPhiStop(bool newVal)
    {
        _phiStop = newVal;
    }
    void setPrintMode(PrintMode newVal)
    {
        _printMode = newVal;
    }
    void setControlSwitchRegister(uint8_t newVal)
    {
        _controlSwitchRegister = newVal;
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
        READY = 0,
        /**
         * Остановка
         */
        STOP = 1
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

    void cjmp_23();

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

    /**
     * @brief Регистр состояния
     */
    union PACKED
    {
        uint16_t	_data;
        uint8_t	_bytes[2];
        struct
        {
            // Флаг омега
            uint16_t	_omega:1;
            // Флаг фи
            uint16_t	_phi:1;
            uint16_t    __padding:6;
            // Остановка
            uint16_t    _stop:1;
        } _value;
    } _statusReg;
    
    uint8_t     _controlSwitchRegister;

    /**
     * Регистр СЧК
     */
    uint16_t	_reg_SCHK:11;
    /**
     * ДШК
     */
    uint16_t	_DSHK:5;
    /**
     * @brief РГМ
     */
    Word_t      _RGM;
    // Дополнительный регистр
    uint16_t    _DRG:6;
    // Дополнительный сумматор
    uint16_t    _DSM:7;

    // Адрес контрольного регистра
    size_t		_controlRegisterAddress;
    // Состояние по питанию
    PowerState_t		_powerState;
    // Напряжения питания (В)
    float		_supplyVoltage[2];
    // Флаг блокировки фи
    bool		_phiBlock;
    // Флаг остановки по фи
    bool		_phiStop;
    // Режим вывода на печать, устанавливаемый с пульта
    PrintMode   _printMode;
    // Ссылка на реализацию ЦПУ
    IPrintDevice    &_printDevice;
};

#endif
