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

#include "PultWIdget.hpp"

#define TACT_SKIP 0

PultWIdget::PultWIdget(URAL::CPU &ural) :
_tactSkip(TACT_SKIP),
_ural(ural)
{
	widget.setupUi(this);
	
	QObject::connect(&_timer, SIGNAL(timeout()), this, SLOT(timerSignaled()));
}

PultWIdget::~PultWIdget()
{
}

void PultWIdget::on_singleStepButton_clicked()
{
	_ural.tact();
	emit tactFinished();
}

void PultWIdget::on_resetButton_clicked()
{
	_ural.reset();
	emit tactFinished();
}

void PultWIdget::on_startButton_clicked()
{
	_timer.start(10);
}

void PultWIdget::on_stopButton_clicked()
{
	_timer.stop();
}

void PultWIdget::timerSignaled()
{
	_ural.tact();
	if (_tactSkip > 0)
		--_tactSkip;
	else {
		_tactSkip = TACT_SKIP;
		emit tactFinished();
	}
}
