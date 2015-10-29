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

#include "AuxControlsWidget.hpp"

AuxControlsWidget::AuxControlsWidget(URAL::CPU &ural) :
_controlRegisterPosition(0ul),
_ural(ural)
{
	widget.setupUi(this);
	
	widget.controlRegisterGroup->setId(widget.cra1, 0);
	widget.controlRegisterGroup->setId(widget.cra2, 1);
	widget.controlRegisterGroup->setId(widget.cra3, 2);
	widget.controlRegisterGroup->setId(widget.cra4, 3);
	widget.controlRegisterGroup->setId(widget.cra5, 4);
	widget.controlRegisterGroup->setId(widget.cra6, 5);
	widget.controlRegisterGroup->setId(widget.cra7, 6);
	widget.controlRegisterGroup->setId(widget.cra8, 7);
	widget.controlRegisterGroup->setId(widget.cra9, 8);
	widget.controlRegisterGroup->setId(widget.cra10, 9);
	widget.controlRegisterGroup->setId(widget.cra11, 10);
	widget.controlRegisterGroup->setId(widget.cra12, 11);
}

AuxControlsWidget::~AuxControlsWidget()
{
}

void AuxControlsWidget::on_controlRegisterGroup_buttonClicked(QAbstractButton
    *button)
{
	QCheckBox *sw = qobject_cast<QCheckBox*>(button);
	Q_CHECK_PTR(sw);
	
	if (sw->isChecked())
		_controlRegisterPosition |=
		    1<<widget.controlRegisterGroup->id(button);
	else
		_controlRegisterPosition &=
		    ~(1<<widget.controlRegisterGroup->id(button));
	
	_ural.setControlRegisterAddress(_controlRegisterPosition);
	emit controlRegisterAddressChanged(_controlRegisterPosition);
}
