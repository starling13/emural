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
#include <QDebug>

#define TACT_SKIP 0

PultWIdget::PultWIdget(URAL::CPU &ural) :
_tactSkip(TACT_SKIP),
_ural(ural)
{
	widget.setupUi(this);
	
	QObject::connect(&_timer, SIGNAL(timeout()), this,
	    SLOT(timerSignaled()));
	
	_commandButtons.push_back(this->widget.addr1group);
	_commandButtons.push_back(this->widget.addr2group);
	_commandButtons.push_back(this->widget.addr3group);
	_commandButtons.push_back(this->widget.addr4group);
	_commandButtons.push_back(this->widget.addr5group);
	_commandButtons.push_back(this->widget.addr6group);
	
	this->widget.addr1group->setId(this->widget.addr1_0button, 0);
	this->widget.addr1group->setId(this->widget.addr1_1button, 1);
	this->widget.addr1group->setId(this->widget.addr1_2button, 2);
	this->widget.addr1group->setId(this->widget.addr1_3button, 3);
	this->widget.addr1group->setId(this->widget.addr1_4button, 4);
	this->widget.addr1group->setId(this->widget.addr1_5button, 5);
	this->widget.addr1group->setId(this->widget.addr1_6button, 6);
	this->widget.addr1group->setId(this->widget.addr1_7button, 7);
	
	this->widget.addr2group->setId(this->widget.addr2_0button, 0);
	this->widget.addr2group->setId(this->widget.addr2_1button, 1);
	this->widget.addr2group->setId(this->widget.addr2_2button, 2);
	this->widget.addr2group->setId(this->widget.addr2_3button, 3);
	this->widget.addr2group->setId(this->widget.addr2_4button, 4);
	this->widget.addr2group->setId(this->widget.addr2_5button, 5);
	this->widget.addr2group->setId(this->widget.addr2_6button, 6);
	this->widget.addr2group->setId(this->widget.addr2_7button, 7);
	
	this->widget.addr3group->setId(this->widget.addr3_0button, 0);
	this->widget.addr3group->setId(this->widget.addr3_1button, 1);
	this->widget.addr3group->setId(this->widget.addr3_2button, 2);
	this->widget.addr3group->setId(this->widget.addr3_3button, 3);
	this->widget.addr3group->setId(this->widget.addr3_4button, 4);
	this->widget.addr3group->setId(this->widget.addr3_5button, 5);
	this->widget.addr3group->setId(this->widget.addr3_6button, 6);
	this->widget.addr3group->setId(this->widget.addr3_7button, 7);
	
	this->widget.addr4group->setId(this->widget.addr4_0button, 0);
	this->widget.addr4group->setId(this->widget.addr4_1button, 1);
	this->widget.addr4group->setId(this->widget.addr4_2button, 2);
	this->widget.addr4group->setId(this->widget.addr4_3button, 3);
	this->widget.addr4group->setId(this->widget.addr4_4button, 4);
	this->widget.addr4group->setId(this->widget.addr4_5button, 5);
	this->widget.addr4group->setId(this->widget.addr4_6button, 6);
	this->widget.addr4group->setId(this->widget.addr4_7button, 7);
	
	this->widget.addr5group->setId(this->widget.addr5_0button, 0);
	this->widget.addr5group->setId(this->widget.addr5_1button, 1);
	this->widget.addr5group->setId(this->widget.addr5_2button, 2);
	this->widget.addr5group->setId(this->widget.addr5_3button, 3);
	this->widget.addr5group->setId(this->widget.addr5_4button, 4);
	this->widget.addr5group->setId(this->widget.addr5_5button, 5);
	this->widget.addr5group->setId(this->widget.addr5_6button, 6);
	this->widget.addr5group->setId(this->widget.addr5_7button, 7);
	
	this->widget.addr6group->setId(this->widget.addr6_0button, 0);
	this->widget.addr6group->setId(this->widget.addr6_1button, 1);
	this->widget.addr6group->setId(this->widget.addr6_2button, 2);
	this->widget.addr6group->setId(this->widget.addr6_3button, 3);
	this->widget.addr6group->setId(this->widget.addr6_4button, 4);
	this->widget.addr6group->setId(this->widget.addr6_5button, 5);
	this->widget.addr6group->setId(this->widget.addr6_6button, 6);
	this->widget.addr6group->setId(this->widget.addr6_7button, 7);
}

PultWIdget::~PultWIdget()
{
}

void PultWIdget::on_singleStepButton_clicked()
{
    _ural.tact();
    emit stopped();
	emit tactFinished();
}

void PultWIdget::on_resetButton_clicked()
{
	_ural.reset();
    emit stopped();
	emit tactFinished();
}

void PultWIdget::on_startButton_clicked()
{
	_timer.start(10);
}

void PultWIdget::on_stopButton_clicked()
{
	_timer.stop();
    emit stopped();
}

void PultWIdget::on_commandResetButton_clicked()
{
	foreach (QButtonGroup *group, this->_commandButtons) {
		QAbstractButton	*button = group->checkedButton();
		if (button) {
			group->setExclusive(false);
			button->setChecked(false);
			group->setExclusive(true);
		}
	}
	this->_commandWord.data = 0ull;
}

void PultWIdget::on_commandSetButton_clicked()
{
	_ural._RGK = this->_commandWord;
	emit tactFinished();
}

void PultWIdget::on_addr1group_buttonClicked(int id)
{
	_commandWord.triplets.t1 = id;
}

void PultWIdget::on_addr2group_buttonClicked(int id)
{
	_commandWord.triplets.t2 = id;
}

void PultWIdget::on_addr3group_buttonClicked(int id)
{
	_commandWord.triplets.t3 = id;
}

void PultWIdget::on_addr4group_buttonClicked(int id)
{
	_commandWord.triplets.t4 = id;
}

void PultWIdget::on_addr5group_buttonClicked(int id)
{
	_commandWord.triplets.t5 = id;
}

void PultWIdget::on_addr6group_buttonClicked(int id)
{
	_commandWord.triplets.t6 = id;
}

void PultWIdget::timerSignaled()
{
	if (!_ural.tact()) {
		_timer.stop();
        emit stopped();
		emit tactFinished();
	}
	if (_tactSkip > 0)
		--_tactSkip;
	else {
		_tactSkip = TACT_SKIP;
		emit tactFinished();
	}
}
