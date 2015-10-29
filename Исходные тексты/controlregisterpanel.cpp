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

#include "controlregisterpanel.hpp"

ControlRegisterPanel::ControlRegisterPanel(QWidget *parent) :
QWidget(parent)
{
	widget.setupUi(this);
	
	_lampPixmaps[0] = new QPixmap(QString::fromUtf8(":/Изображения/lamp_off.png"));
	_lampPixmaps[1] = new QPixmap(QString::fromUtf8(":/Изображения/lamp_on.png"));
	
	_lamps.push_back(widget.lamp0);
	_lamps.push_back(widget.lamp1);
	_lamps.push_back(widget.lamp2);
	_lamps.push_back(widget.lamp3);
	_lamps.push_back(widget.lamp4);
	_lamps.push_back(widget.lamp5);
	_lamps.push_back(widget.lamp6);
	_lamps.push_back(widget.lamp7);
	_lamps.push_back(widget.lamp8);
	_lamps.push_back(widget.lamp9);
	_lamps.push_back(widget.lamp10);
	_lamps.push_back(widget.lamp11);
	_lamps.push_back(widget.lamp12);
	_lamps.push_back(widget.lamp13);
	_lamps.push_back(widget.lamp14);
	_lamps.push_back(widget.lamp15);
	_lamps.push_back(widget.lamp16);
	_lamps.push_back(widget.lamp17);
	_lamps.push_back(widget.lamp18);
	_lamps.push_back(widget.lamp19);
	_lamps.push_back(widget.lamp20);
	_lamps.push_back(widget.lamp21);
	_lamps.push_back(widget.lamp22);
	_lamps.push_back(widget.lamp23);
	_lamps.push_back(widget.lamp24);
	_lamps.push_back(widget.lamp25);
	_lamps.push_back(widget.lamp26);
	_lamps.push_back(widget.lamp27);
	_lamps.push_back(widget.lamp28);
	_lamps.push_back(widget.lamp29);
	_lamps.push_back(widget.lamp30);
	_lamps.push_back(widget.lamp31);
	_lamps.push_back(widget.lamp32);
	_lamps.push_back(widget.lamp33);
	_lamps.push_back(widget.lamp34);
	_lamps.push_back(widget.lamp35);
}

ControlRegisterPanel::~ControlRegisterPanel()
{
}

void ControlRegisterPanel::setValue(URAL::Word_t newValue)
{
	for (size_t i=0; i<36; ++i) {
		if (newValue.data & (1ull<<i))
			_lamps[i]->setPixmap(*_lampPixmaps[1]);
		else
			_lamps[i]->setPixmap(*_lampPixmaps[0]);
	}
}
