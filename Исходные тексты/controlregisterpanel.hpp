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

#ifndef _CONTROLREGISTERPANEL_HPP
#define	_CONTROLREGISTERPANEL_HPP

#include "ui_ControlRegisterPanel.h"

#include "ural.hpp"

class ControlRegisterPanel : public QWidget
{
	Q_OBJECT
	
public:
	ControlRegisterPanel(QWidget *parent = 0);
	
	~ControlRegisterPanel();
	
	void setValue(URAL::Word_t);
	
private:
	
	Ui::ControlRegisterPanel widget;
	
	URAL::Word_t	_value;
	
	QPixmap		*_lampPixmaps[2];
	
	QVector<QLabel*>	_lamps;
};

#endif	/* _CONTROLREGISTERPANEL_HPP */
