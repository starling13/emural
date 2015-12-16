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
	CPU(IPrintDevice&, IExtMemoryDevice&);
	~CPU();

	void		 printAdder();
	void		 printCommand();

	uint16_t	 regSCHK() const
	{
		return (_reg_SCHK);
	}
	void		 setRegSCHK(uint16_t newVal)
	{
		_reg_SCHK = newVal;
	}

	uint16_t	 regDSHK() const
	{
		return (_DSHK);
	}

	void		 setAddressBlock(uint16_t newVal)
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

	void		 start();

	void		 stop();

	void		 reset();
	/**
	 * @brief выполнить один такт работы
	 * @return признак остановки
	 */
	bool		 tact();
	/**
	 * @brief Однотактный режим
	 */
	void		 singleStep();

	void		 clearDrum();
	const Word_t	&controlRegister() const;
	void		 setControlRegisterAddress(size_t newVal);
	void		 setSupplyVoltage(uint8_t, float);

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

	/**
	 * @brief регистр арифметического устройства
	 */
	Word_t		_RGAU;

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

	// Состояние по групповым операциям
	enum OperationState_t
	{
		// Нет незавершённой операции
		OP_IDLE = 0,
		// Групповая операция началась
		OP_GROUP_START = 1,
		// Групповая операция выбрана
		OP_GROUP_SELECTED = 1,
		OP_NUMBER
	};

	enum TapeMode_t
	{
		TAPE_PUNCH_READ,
		TAPE_MAGNET_READ,
		TAPE_MAGNET_WRITE,
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
	// выбор групповой операции
	void groupTapeRead_01();
	/**
	 * @brief сложение с нулём (послыка в сумматор)
	 */
	void sum2_02();
	/**
	 * @brief вычитание
	 */
	void sub1_03();
	/**
	 * @brief вычитание модулей
	 */
	void sub2_04();
	/**
	 * @brief умножение с подсуммированием
	 */
	void mul1_05();
	/**
	 * @brief умножение
	 */
	void mul2_06();

	void div_07();
	/**
	 * @brief посылка в память
	 */
	void mov_16();
	/**
	 * @brief посылка в регистр
	 */
	void loadR_17();
	/**
	 * @brief посылка адреса в сумматор
	 */
	void load_20();
	/**
	 * @brief условный переход
	 */
	void jmp_21();
	/**
	 * @brief безусловный переход
	 */
	void jmp_22();
	/**
	 * @brief передача управления по ключу
	 */
	void cjmp_23();

	void group_31();

	void print_32();

	void feed_34();

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
	void (CPU::*commands[OP_NUMBER][32])();

	/**
	 * @brief Регистр состояния
	 */
	union PACKED
	{
		uint16_t	_data;
		uint8_t		_bytes[2];
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

	/**
	 * @brief РГЧ
	 */
	uint64_t      _RGCH:36;

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
	IExtMemoryDevice &_punchReader;
	// Состояние по выполнению операций
	OperationState_t	_opState;
	// Тип групповой операции (перфолента/магнитная лента)
	TapeMode_t		_groupMode;
	// Зона ленты
	uint16_t		_tapeZone;
	// Длинная ячейка
	bool			_tapeAddressMode;
	uint16_t		_groupOpStartAddress;
	uint16_t		_groupOpEndAddress;
};

#endif
