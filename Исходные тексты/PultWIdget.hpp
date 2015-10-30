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

#ifndef _PULTWIDGET_HPP
#define	_PULTWIDGET_HPP

#include "ui_PultWIdget.h"

#include "controls.hpp"
#include "ural.hpp"

class PultWIdget : public QWidget
{
	Q_OBJECT
	
signals:

	void tactFinished();
	
public:
	
	PultWIdget(URAL::CPU&);
	
	~PultWIdget();
	
private slots:
	
	void on_singleStepButton_clicked();
	
	void on_resetButton_clicked();
	
private:
	
	Ui::PultWIdget widget;
	
	URAL::CPU	&_ural;
};

#endif	/* _PULTWIDGET_HPP */
