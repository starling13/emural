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

#ifndef FIXED_CODING_HPP
#define	FIXED_CODING_HPP

#include <bitset>
#include <ostream>
#include <cmath>
#include <stdexcept>

#ifndef PACKED
#define PACKED __attribute__ ((__packed__))
#endif

/**
 * Шаблонный пакет вещественных чисел с фиксированной перед дробной частью
 * точкой
 * 
 * @param base базовый целочисленный тип данных
 * @param bits число значащих бит, не считая знаковых
 * 
 * ПРЕДУСЛОВИЕ число разрядов, включая знаковые не превышает число бит в базовом
 *     целочисленном типе
 */
template <typename base, size_t bits>
class FixedPointFraction
{
public:

/**
 * Целочисленный элементарный тип данных, равный по числу байт базовому,
 * но гарантированно являющийся знаковым
 */
typedef typename std::make_signed<base>::type	signed_base;

class ModOnesComplement;

/**
 * Число в прямом коде
 */
class PACKED SignedMagnitude
{
	friend std::ostream& operator <<(std::ostream &stream,
	    const FixedPointFraction::SignedMagnitude &number)
	{
		stream << u8"Прямой код, фиксированная точка"
		    u8" (база " << sizeof (base) << u8" байт, количество разрядов "
		    << bits << ") значение " << double(number) <<
		    "\n\t знак " << bool(number._sign) << u8" модуль " <<
		    std::bitset<bits>(number._magnitude);
	
		return (stream);
	}
	
	friend FixedPointFraction::SignedMagnitude
	abs(const FixedPointFraction::SignedMagnitude &number)
	{
		FixedPointFraction::SignedMagnitude	result(number);
		
		result._sign = 0;
		
		return (result);
	}
	
public:
	
	SignedMagnitude();
	
	SignedMagnitude(const SignedMagnitude&) = default;
	
	SignedMagnitude& operator =(const SignedMagnitude&) = default;
	
	SignedMagnitude(const ModOnesComplement&);
		
	SignedMagnitude(signed_base);
	
	base	magnitude() const
	{
		return (_magnitude);
	}
	void	setMagnitude(base newVal)
	{
		_magnitude = newVal;
	}
	
	base	sign() const
	{
		return (_sign);
	}
	void	setSign(base newVal)
	{
		_sign = newVal;
	}
	
	operator double() const;

	bool	signEquals(const ModOnesComplement&) const;
	
	/**
	 * @brief модуль
	 */
	base	_magnitude:bits;

	/**
	 * @brief знак
	 */
	base	_sign:1;

private :

static_assert ((sizeof (base) * 8) >= (bits+2), u8"Неверное число бит");
};

/**
 * Число в модифицированном обратном коде
 */
class PACKED ModOnesComplement
{
	friend std::ostream& operator <<(std::ostream &stream,
	    const FixedPointFraction::ModOnesComplement &number)
	{
		stream << u8"Обратный модифицированный код, фиксированная точка"
		    u8" (база " << sizeof (base) << u8" байт, количество разрядов "
		    << bits << ") значение " << double(number) <<
		    u8"\n\tпереполнение " << number._carry << ", знак " <<
		    std::bitset<2>(number._sign) << u8" модуль " <<
		    std::bitset<bits>(number._magnitude);
	
		return (stream);
	}
	
	friend FixedPointFraction::ModOnesComplement
	abs(const FixedPointFraction::ModOnesComplement &number)
	{
		FixedPointFraction::ModOnesComplement	result(number);
		
		if (result._sign == 0)
			return (result);
		else
			return (-result);
	}
	
public:
	
	ModOnesComplement();
	
	ModOnesComplement(const ModOnesComplement&) = default;
	
	ModOnesComplement& operator =(const ModOnesComplement&) = default;
	
	ModOnesComplement(const SignedMagnitude&);
	
	ModOnesComplement(signed_base);
	
	/**
	 * Получить представление числа в формате с плавающей точкой
         * @return число с плавающей точкой двойной точности
         */
	operator double() const;
	
	base	magnitude() const
	{
		return (_magnitude);
	}
	void	setMagnitude(base newVal)
	{
		_magnitude = newVal;
	}
	
	base	sign() const
	{
		return (_sign);
	}
	void	setSign(base newVal)
	{
		_sign = newVal;
	}
	/**
	 * Оператор присваивания для базового типа данных
         * @param 
         * @return 
         */
	//ModOnesComplement &operator =(signed_base);
	
	ModOnesComplement operator -() const;
		
	ModOnesComplement &operator +=(const ModOnesComplement&);
		
	ModOnesComplement operator +(const ModOnesComplement&) const;
		
	ModOnesComplement &operator -=(const ModOnesComplement&);

	ModOnesComplement operator -(const ModOnesComplement&) const;

	ModOnesComplement &lshift(size_t);

	base	_magnitude:bits;
	base	_sign:2;
	base	_carry:1;
private :
	
static_assert ((sizeof (base) * 8) >= (bits+4), u8"Неверное число бит");
};

};

template <typename base, size_t bits>
FixedPointFraction<base, bits>::ModOnesComplement::
    ModOnesComplement() :
_magnitude(0),
_sign(0),
_carry(0)
{
}

template <typename base, size_t bits>
FixedPointFraction<base, bits>::ModOnesComplement::
    ModOnesComplement(const FixedPointFraction<base, bits>::SignedMagnitude &other)
{
	if (!other.sign()) {
		this->_magnitude = other.magnitude();
		this->_sign = 0;
	} else {
		this->_magnitude = ~other.magnitude();
		this->_sign = 3;
	}
	this->_carry = 0;
}

template <typename base, size_t bits>
FixedPointFraction<base, bits>::ModOnesComplement::
    operator double() const
{
	double res;
	
	if (this->_sign == 0) {
		res = this->_magnitude;
		res /= (1ull << bits);
	} else if (this->_sign == 3) {
		res = -double ((~this->_magnitude) & ((base(1) << bits) - 1));
		res /= (1ull << bits);
	} else {
		res = NAN;
	}
	
	return (res);
}

template <typename base, size_t bits>
FixedPointFraction<base, bits>::SignedMagnitude::
    operator double() const
{
	double res;
	
	if (this->_sign == 0)
		res = double(this->_magnitude) / (1ull << bits);
	else if (this->_sign == 3)
		res = -double(this->_magnitude) / (1ull << bits);
	else
		res = NAN;
	
	return (res);
}
/*
template <typename base, size_t bits>
typename FixedPointFraction<base, bits>::ModOnesComplement&
FixedPointFraction<base, bits>::ModOnesComplement::operator =(signed_base val)
{
	SignedMagnitude buf(val);
	
	(*this) = buf;
	
	return (*this);
}
*/
template <typename base, size_t bits>
typename FixedPointFraction<base, bits>::ModOnesComplement
FixedPointFraction<base, bits>::ModOnesComplement::operator -() const
{
	ModOnesComplement result;
	
	if (this->_sign == 0)
		result._sign = 3;
	else if (this->_sign == 3)
		result._sign = 0;
	else
		throw std::overflow_error(u8"Недопустимый знак");
	
	result._magnitude = ~this->_magnitude;
	result._carry = 0;
	
	return (result);
}

template <typename base, size_t bits>
typename FixedPointFraction<base, bits>::ModOnesComplement&
FixedPointFraction<base, bits>::ModOnesComplement::operator +=(const
    ModOnesComplement &other)
{
	reinterpret_cast<base&>(*this) += reinterpret_cast<const base&>(
	    other);
	if (this->_carry) {
		reinterpret_cast<uint64_t&>(*this) += 1;
		this->_carry = 0;
	}
	
	return (*this);
}

template <typename base, size_t bits>
typename FixedPointFraction<base, bits>::ModOnesComplement
FixedPointFraction<base, bits>::ModOnesComplement::operator +(const
    ModOnesComplement &other) const
{
	ModOnesComplement res = (*this);
	
	res += other;
	
	return (res);
}

template <typename base, size_t bits>
typename FixedPointFraction<base, bits>::ModOnesComplement&
FixedPointFraction<base, bits>::ModOnesComplement::operator -=(const
    ModOnesComplement &other)
{
	(*this) += -other;
	
	return (*this);
}

template <typename base, size_t bits>
typename FixedPointFraction<base, bits>::ModOnesComplement&
FixedPointFraction<base, bits>::ModOnesComplement::lshift(size_t count)
{
	bool carry = this->_magnitude & (base(1)<<(bits-1));

	this->_magnitude <<= count;
	if (carry)
		this->_magnitude |= 1;

	return (*this);
}

template <typename base, size_t bits>
typename FixedPointFraction<base, bits>::ModOnesComplement
FixedPointFraction<base, bits>::ModOnesComplement::operator -(const
    ModOnesComplement &other) const
{
	ModOnesComplement res = (*this);

	res -= other;

	return (res);
}

template <typename base, size_t bits>
FixedPointFraction<base, bits>::SignedMagnitude::SignedMagnitude() :
_magnitude(0),
_sign(0)
{
	_magnitude = 0;
}

template <typename base, size_t bits>
FixedPointFraction<base, bits>::SignedMagnitude::SignedMagnitude(
    const ModOnesComplement &other)
{
	if (other.sign() == 0) {
		this->_sign = 0;
		this->_magnitude = other.magnitude();
	} else if (other.sign() == 3) {
		this->_sign = 1;
		this->_magnitude = ~other.magnitude();
	}
}

template <typename base, size_t bits>
bool
FixedPointFraction<base, bits>::SignedMagnitude::signEquals(const ModOnesComplement &other) const
{
	if (((other.sign() == 0) && (this->_sign == 0)) ||
	    ((other.sign() == 3) && (this->_sign == 1))) {
		return (true);
	} else
		return (false);
}

template <typename base, size_t bits>
FixedPointFraction<base, bits>::ModOnesComplement::
ModOnesComplement(signed_base val) :
_carry(0)
{
	if (val < 0)
		val = -val;

	_magnitude = base(val);
	if (val < 0)
		_sign = 3;
	else
		_sign = 0;
}

template <typename base, size_t bits>
FixedPointFraction<base, bits>::SignedMagnitude::
SignedMagnitude(signed_base val) :
_magnitude(std::abs(val))
{
	if (val < 0)
		_sign = 1;
	else
		_sign = 0;
}

#endif	/* FIXED_CODING_HPP */
