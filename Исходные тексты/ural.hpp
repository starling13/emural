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

class URAL
{
public:
	
	static const size_t	drumWordsNumber = 1024;
	static const size_t	drumHalfWordsNumber = drumWordsNumber * 2;
	
	class PACKED SignedMagnitudeDouble
	{
	public:
		
		SignedMagnitudeDouble() :
		magnitude(0ll),
		sign(0)
		{
		}
		
		SignedMagnitudeDouble(int64_t val)
		{
			magnitude = std::abs(val);
			if (val < 0)
				sign = 1;
			else
				sign = 0;
		}
		
		uint64_t	magnitude:35;
		uint64_t	sign:1;
	};
	
	class PACKED ModOnesComplementDouble
	{
		friend std::ostream& operator <<(std::ostream&,
		    const ModOnesComplementDouble&);
	public:
		
		ModOnesComplementDouble()
		{
			magnitude = 0ull;
			sign = 0ull;
			carry = 0ull;
		}
		
		ModOnesComplementDouble(SignedMagnitudeDouble);
		
		double floatingPointValue() const;
		
		ModOnesComplementDouble &operator =(int64_t);
		
		ModOnesComplementDouble operator -() const;
		
		ModOnesComplementDouble &operator +=(const ModOnesComplementDouble&);
		
		ModOnesComplementDouble operator +(const ModOnesComplementDouble&) const;
		
		ModOnesComplementDouble &operator -=(const ModOnesComplementDouble&);
		
		uint64_t	magnitude:35;
		uint64_t	sign:2;
		uint64_t	carry:1;
	};
	
	typedef union PACKED HalfWord
	{
	public:
		
		double floatingPointValue() const;
		
		uint64_t	data:18;
		
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
			uint64_t	t6:2;
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
		
		SignedMagnitudeDouble dPrec;
		
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
	
	union Adder
	{
	public:
		
		Adder(ModOnesComplementDouble);
		
		Adder &operator =(const Adder&);
		
		uint64_t	data;
		ModOnesComplementDouble	value;
		struct
		{
			uint64_t	word1:18;
			uint64_t	word2:18;
		};
	};
	
	class CPU
	{
	public:
		
		CPU();
		
		void tact();
		
		Word_t		R;
		Word_t		drum[drumWordsNumber];
		HalfWord_t	commandReg;
		uint16_t	PC;
		Adder		S;
		
	private:
		
		void (CPU::*commands[32])();
		
		void noop_00();
		
		void sum1_01();
		
		void sum2_02();
	};
};

#endif	/* URAL_HPP */
