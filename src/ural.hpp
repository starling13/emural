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

#ifndef URAL_HPP
#define	URAL_HPP

#include "fixed_coding.hpp"
#include "controlregisterpanel.hpp"

/**
 * @brief пакет эмулятора Урал
 */
class URAL
{
public:
    /*
     * Число полных ячеек в барабане
     */
	static const size_t	drumWordsNumber = 02000;
    /*
     * Число коротких ячеек
     */
	static const size_t	drumHalfWordsNumber = drumWordsNumber * 2;
    /*
     * Бит признака длины ячейки
     */
	static const size_t	addressLengthBit = 04000;
    /*
     * Полная ячейка в модифицированном обратном коде (сумматор)
     */
	typedef	FixedPointFraction<uint64_t, 35>::ModOnesComplement
		AdderWord;
    /*
     * Полная ячейка в прямом коде (регистр АУ, барабан)
     */
	typedef	FixedPointFraction<uint64_t, 35>::SignedMagnitude
		DoubleCell;
    /*
     * Короткая ячейка в прямом коде (регистр АУ, барабан)
     */
	typedef	FixedPointFraction<uint64_t, 17>::SignedMagnitude
		Cell;
    /*
     * Формат ввода-вывода
     */
    enum Format { BIN = 2, OCT = 8};
    /*
     * Расширеный тип короткой ячейки
     */
	typedef union PACKED HalfWord
	{
	public:
		
		HalfWord() :
		sPrec(0)
		{
		}
		
		uint64_t	data:18;
		
		Cell		sPrec;
		
		struct
		{
			uint64_t	module:17;
			uint64_t	sign:1;
		} value;
		
		struct
		{
			uint64_t	t1:3;
			uint64_t	t2:3;
			uint64_t	t3:3;
			uint64_t	t4:3;
			uint64_t	t5:3;
			uint64_t	t6:3;
		} triplets;
		
		struct
		{
			uint64_t	b1:1;
			uint64_t	b2:1;
			uint64_t	b3:1;
			uint64_t	b4:1;
			uint64_t	b5:1;
			uint64_t	b6:1;
			uint64_t	b7:1;
			uint64_t	b8:1;
			uint64_t	b9:1;
			uint64_t	b10:1;
			uint64_t	b11:1;
			uint64_t	b12:1;
			uint64_t	b13:1;
			uint64_t	b14:1;
			uint64_t	b15:1;
			uint64_t	b16:1;
			uint64_t	b17:1;
			uint64_t	b18:1;
		} bits;
		
		struct
		{
			uint64_t	address:11;
			uint64_t	addrLength:1;
			uint64_t	opCode:5;
			uint64_t	indexFlag:1;
		} command;
	} HalfWord_t;
	static_assert (sizeof (HalfWord_t) <= sizeof (uint64_t),
	    "Неверный размер");
	
	friend std::ostream &operator <<(std::ostream&, const HalfWord_t&);
	
	/**
	 * Машинное слово (36 бит)
	 */
	typedef union PACKED Word
	{
	public:
		Word() :
		dPrec(0)
		{
		}
		Word(int64_t);
		HalfWord operator [](uint8_t) const;
		uint64_t	data:36;
		struct
		{
			uint64_t	least:18;
			uint64_t	most:18;
		} halfWords;
        struct
        {
            uint64_t	q1:9;
            uint64_t	q2:9;
            uint64_t	q3:9;
            uint64_t	q4:9;
        } quaters;
		DoubleCell		dPrec;
		struct
		{
			uint64_t	t1:3;
			uint64_t	t2:3;
			uint64_t	t3:3;
			uint64_t	t4:3;
			uint64_t	t5:3;
			uint64_t	t6:3;
			uint64_t	t7:3;
			uint64_t	t8:3;
			uint64_t	t9:3;
			uint64_t	t10:3;
			uint64_t	t11:3;
			uint64_t	t12:2;
		} triplets;
		struct
		{
			uint64_t	q1:3;
			uint64_t	q2:4;
			uint64_t	q3:4;
			uint64_t	q4:4;
			uint64_t	q5:4;
			uint64_t	q6:4;
			uint64_t	q7:4;
			uint64_t	q8:4;
			uint64_t	q9:4;
		} quartets;
		struct
		{
			uint64_t	b1:1;
			uint64_t	b2:1;
			uint64_t	b3:1;
			uint64_t	b4:1;
			uint64_t	b5:1;
			uint64_t	b6:1;
			uint64_t	b7:1;
			uint64_t	b8:1;
			uint64_t	b9:1;
			uint64_t	b10:1;
			uint64_t	b11:1;
			uint64_t	b12:1;
			uint64_t	b13:1;
			uint64_t	b14:1;
			uint64_t	b15:1;
			uint64_t	b16:1;
			uint64_t	b17:1;
			uint64_t	b18:1;
			uint64_t	b19:1;
			uint64_t	b20:1;
			uint64_t	b21:1;
			uint64_t	b22:1;
			uint64_t	b23:1;
			uint64_t	b24:1;
			uint64_t	b25:1;
			uint64_t	b26:1;
			uint64_t	b27:1;
			uint64_t	b28:1;
			uint64_t	b29:1;
			uint64_t	b30:1;
			uint64_t	b31:1;
			uint64_t	b32:1;
			uint64_t	b33:1;
			uint64_t	b34:1;
			uint64_t	b35:1;
			uint64_t	b36:1;
		} bits;
	} Word_t;

	friend std::ostream &operator <<(std::ostream&, const Word_t&);

	union PACKED Adder
	{
	public:
		Adder(AdderWord);
		Adder &operator =(const Adder&);
		uint64_t	data;
		AdderWord	value;
		struct
		{
            uint64_t	word1:18;
			uint64_t	word2:18;
        } words;
	};

	class CPU
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
		
		void loadR();
		
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

        void mul2_06();
		
		void mov_16();
		
		void loadR_17();
		
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
		
        size_t		_controlRegisterAddress;
		
		PowerState_t		_powerState;
		
		State_t			_mode;
		
		// Напряжения питания (В)
		float		_supplyVoltage[2];
		
		bool		_phiBlock;
		
		bool		_phiStop;
	};
};

#endif	/* URAL_HPP */