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

/**
 * Число в прямом коде
 */
class PACKED SignedMagnitude
{
public:
	SignedMagnitude();
		
	SignedMagnitude(base);
private :	
	base	magnitude:bits;
	base	sign:1;

static_assert ((sizeof (base) * 8) >= (bits+1), u8"Неверное число бит");
};

/**
 * ЧИсло в модифицированном обратном коде
 */
class PACKED ModOnesComplement
{
	template <typename base1, size_t bits1>
	friend std::ostream& operator <<(std::ostream&,
	    const typename FixedPointFraction<base1, bits1>::
	    ModOnesComplement&);
public:
	ModOnesComplement();
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
	ModOnesComplement &operator =(base);
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
double
FixedPointFraction<base, bits>::ModOnesComplement::
    floatingPointValue() const
{
	double res;
	
	if (this->sign == 0) {
		res = this->magnitude;
		res /= (1ull << bits);
	} else if (this->sign == 3) {
		res = -double (~this->magnitude);
		res /= (1ull << bits);
	} else {
		res = NAN;
	}
	
	return (res);
}

template <typename base, size_t bits>
std::ostream&
operator <<(std::ostream &stream, const typename FixedPointFraction<base, bits>::
    ModOnesComplement &number)
{
	stream << u8"Обратный модифицированный код, фиксированная точка: " <<
	    number.floatingPointValue() << u8"\n\tпереполнение " << number.carry
	    << ", знак " << std::bitset<2>(number.sign) << u8" модуль " <<
	    std::bitset<bits>(number.magnitude);
	
	return (stream);
}

template <typename base, size_t bits>
typename FixedPointFraction<base, bits>::ModOnesComplement&
FixedPointFraction<base, bits>::ModOnesComplement::operator =(base val)
{
	SignedMagnitude buf(val);
	
	(*this) = buf;
	
	return (*this);
}

template <typename base, size_t bits>
FixedPointFraction<base, bits>::SignedMagnitude::SignedMagnitude() :
magnitude(0),
sign(0)
{
}

template <typename base, size_t bits>
FixedPointFraction<base, bits>::SignedMagnitude::
SignedMagnitude(base val) :
magnitude(std::abs(val))
{
	if (val < 0)
		sign = 1;
	else
		sign = 0;
}

#endif	/* FIXED_CODING_HPP */
