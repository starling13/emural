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
 * @param bits число значащих бит, не считая згнаковых
 * 
 * ПРЕДУСЛОВИЕ число разрядов, включая знаковые не превышает число бит в базовом
 *     целочисленном типе
 */
template <typename base, size_t bits>
class FixedPointFraction
{
public:
	
typedef typename std::make_signed<base>::type	signed_base;

/**
 * Число в прямом коде
 */
class PACKED SignedMagnitude
{
public:
	SignedMagnitude();
		
	SignedMagnitude(signed_base);
	
	base	magnitude() const
	{
		return (_magnitude);
	}
	
	base	sign() const
	{
		return (_sign);
	}
	
private :	
	base	_magnitude:bits;
	base	_sign:1;

static_assert ((sizeof (base) * 8) >= (bits+1), u8"Неверное число бит");
};

/**
 * ЧИсло в модифицированном обратном коде
 */
class PACKED ModOnesComplement
{
	friend std::ostream& operator <<(std::ostream &stream,
	    const FixedPointFraction::
	    ModOnesComplement &number)
	{
		stream << u8"Обратный модифицированный код, фиксированная точка"
		    u8" (база " << sizeof (base) << u8" байт, количество разрядов "
		    << bits << ", значение " << number.floatingPointValue() <<
		    u8"\n\tпереполнение " << number.carry << ", знак " <<
		    std::bitset<2>(number.sign) << u8" модуль " <<
		    std::bitset<bits>(number.magnitude);
	
		return (stream);
	}
public:
	ModOnesComplement();
	
	ModOnesComplement(SignedMagnitude);
	/**
	 * Получить представление числа в формате с плавающей точкой
         * @return число с плавающей точкой двойной точности
         */
	double floatingPointValue() const;
	/**
	 * Оператор присваивания для базового типа данных
         * @param 
         * @return 
         */
	ModOnesComplement &operator =(signed_base);
	
	ModOnesComplement operator -() const;
		
	ModOnesComplement &operator +=(const ModOnesComplement&);
		
	ModOnesComplement operator +(const ModOnesComplement&) const;
		
	ModOnesComplement &operator -=(const ModOnesComplement&);
private :
	base	magnitude:bits;
	base	sign:2;
	base	carry:1;
	
static_assert ((sizeof (base) * 8) >= (bits+3), u8"Неверное число бит");
};

};

template <typename base, size_t bits>
FixedPointFraction<base, bits>::ModOnesComplement::
    ModOnesComplement() :
magnitude(0),
sign(0),
carry(0)
{
}

template <typename base, size_t bits>
FixedPointFraction<base, bits>::ModOnesComplement::
    ModOnesComplement(FixedPointFraction<base, bits>::SignedMagnitude other)
{
	if (!other.sign()) {
		this->magnitude = other.magnitude();
		this->sign = 0;
	} else {
		this->magnitude = ~other.magnitude();
		this->sign = 3;
	}
	this->carry = 0;
}

template <typename base, size_t bits>
double
FixedPointFraction<base, bits>::ModOnesComplement::
    floatingPointValue() const
{
	double res;
	
	if (this->sign == 0) {
		res = this->magnitude;
		res /= (1ull << bits);
	} else if (this->sign == 3) {
		res = -double ((~this->magnitude) & ((base(1) << bits) - 1));
		res /= (1ull << bits);
	} else {
		res = NAN;
	}
	
	return (res);
}

template <typename base, size_t bits>
typename FixedPointFraction<base, bits>::ModOnesComplement&
FixedPointFraction<base, bits>::ModOnesComplement::operator =(signed_base val)
{
	SignedMagnitude buf(val);
	
	(*this) = buf;
	
	return (*this);
}

template <typename base, size_t bits>
typename FixedPointFraction<base, bits>::ModOnesComplement
FixedPointFraction<base, bits>::ModOnesComplement::operator -() const
{
	ModOnesComplement result;
	
	if (this->sign == 0)
		result.sign = 3;
	else if (this->sign == 3)
		result.sign = 0;
	else
		throw std::overflow_error(u8"Недопустимый знак");
	
	result.magnitude = ~this->magnitude;
	result.carry = 0;
	
	return (result);
}

template <typename base, size_t bits>
typename FixedPointFraction<base, bits>::ModOnesComplement&
FixedPointFraction<base, bits>::ModOnesComplement::operator +=(const
    ModOnesComplement &other)
{
	reinterpret_cast<base&>(*this) += reinterpret_cast<const base&>(
	    other);
	if (this->carry) {
		reinterpret_cast<uint64_t&>(*this) += 1;
		this->carry = 0;
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
FixedPointFraction<base, bits>::SignedMagnitude::SignedMagnitude() :
_magnitude(0),
_sign(0)
{
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
