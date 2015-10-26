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
#include <iostream>

#include <QtCore/QTimer>
#include <QtGui/QApplication>

#include "DisplayPanel.hpp"
#include "ural.hpp"

using namespace std;

int main(int argc, char** argv)
{
	int		res;
	QApplication	app(argc, argv);
	
	URAL::CPU	ural;
	DisplayPanel	panel(ural);
	QTimer		timer;
	
	std::cout << sizeof (URAL::Word_t) << std::endl;
	
	panel.setFixedSize(640,320);
	panel.setWindowTitle(QString::fromUtf8(u8"Контрольная панель"));
	
	panel.connect(&timer, SIGNAL(timeout()), SLOT(tact()));
	timer.start(10);
	panel.show();
	
	res = app.exec();
	
	timer.stop();
	
	return (res);
}
