/*
 * This file is part of EMURAL - emulator for Ural computer from 1950s
 * Copyright (C) 2015-2024 Andrey V. Skvortsov <starling13@gmail.com>
 *
 * EMURAL is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef URAL_HPP
#define	URAL_HPP

#include <vector>

#include "fixed_coding.hpp"

/**
 * @brief пакет эмулятора Урал
 */
class URAL
{
public:
	/**
	 * @brief Режим печати программы
	 */
	enum PrintMode
	{
		// Отсутствие печати
		PRINT_NONE,
		// Печать I
		PRINT_MODE1,
		// Печать II
		PRINT_MODE2
	};
	/**
	 * @brief Число полных ячеек в барабане
	 */
	static const size_t	drumWordsNumber = 02000;
	/**
	 * @brief Число коротких ячеек
	 */
	static const size_t	drumHalfWordsNumber = drumWordsNumber * 2;
	/**
	 * @brief Бит признака длины ячейки
	 */
	static const size_t	addressLengthBit = 04000;
	/**
	 * @brief Полная ячейка в модифицированном обратном коде (сумматор)
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
	enum Format {BIN = 2, OCT = 8, DEC = 10};
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
			uint64_t	t12:3;
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

	/**
	 * @brief Интерфейс цифрового печатающего устройства
	 */
	class IPrintDevice
	{
	public:

		virtual ~IPrintDevice() = default;

		virtual void printWord(URAL::Word_t) = 0;

		virtual void printCommand(uint16_t, URAL::HalfWord_t) = 0;

		virtual void printResult(URAL::Word_t) = 0;

		virtual void lineFeed() = 0;

	protected:

		IPrintDevice() = default;

	private:

		IPrintDevice(const IPrintDevice&) = delete;
	};

	/**
	 * @brief Число на носителе УВВ (ленте)
	 */
	struct Number
	{
	    Number() :
		data{0,0,0,0,0,0,0,0,0,0,0}
	    {
	    }

	    uint8_t data[11];
	};

	typedef std::vector<Number> Numbers;

	/**
	 * @brief Интерфейс внешнего накопителя
	 */
	class IExtMemoryDevice
	{
	public:

		virtual ~IExtMemoryDevice() = default;

		virtual void searchZone(uint8_t) = 0;

		virtual URAL::Word_t readWord() = 0;

		virtual bool readHalfWord(URAL::HalfWord_t&) = 0;

	protected:

		IExtMemoryDevice() = default;

	private:

		IExtMemoryDevice(const IExtMemoryDevice&) = delete;
	};

	/**
	 * @brief Перфолента
	 */
	class PunchTape
	{
	public:

		PunchTape();

		~PunchTape();

		void		 loadData(const uint8_t*, size_t);

		void		 saveData(uint8_t*, size_t);

		URAL::Numbers	&tapeData()
		{
			return (_data);
		}

	private:

		URAL::Numbers	_data;
	};

	class CPU;
};

#endif	/* URAL_HPP */
