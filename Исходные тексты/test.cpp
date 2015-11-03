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

#include <cstdlib>
#include <limits>
#include <iostream>

//#include "ural.hpp"
#include "fixed_coding.hpp"

int main(int argc, char** argv)
{
	std::cout.precision(std::numeric_limits< double >::digits10);
	
	FixedPointFraction<uint64_t, 36>::ModOnesComplement	a;
	FixedPointFraction<uint64_t, 36>::SignedMagnitude	b;
	
	a.setMagnitude(3), b.setMagnitude(6);
	
	std::cout << a << std::endl;
	std::cout << b << std::endl;
	
	a = b;
	b = a;
	
	/*
	ural.drum[0] = 0000001020004;
	ural.drum[1] = 0000003000002;
	ural.drum[2] = 0000005000004;
	ural.drum[3] = 0000007000006;
	ural.drum[4] = 0000011000010;
	ural.drum[5] = 0000013000012;
	
	ural.tact();
	ural.tact();
	ural.tact();
	ural.tact();
	ural.tact();
	ural.tact();
	ural.tact();
	ural.tact();
	ural.tact();
	ural.tact();
	ural.tact();
	ural.tact();
	*/
	return (EXIT_SUCCESS);
}          
