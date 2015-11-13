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
_controlRegisterPosition(0u),
_addrStopRegister(0u),
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
	
	widget.addressBlockGroup->setId(widget.ab1, 0);
	widget.addressBlockGroup->setId(widget.ab2, 1);
	widget.addressBlockGroup->setId(widget.ab3, 2);
	widget.addressBlockGroup->setId(widget.ab4, 3);
	widget.addressBlockGroup->setId(widget.ab5, 4);
	widget.addressBlockGroup->setId(widget.ab6, 5);
	widget.addressBlockGroup->setId(widget.ab7, 6);
	widget.addressBlockGroup->setId(widget.ab8, 7);
	widget.addressBlockGroup->setId(widget.ab9, 8);
	widget.addressBlockGroup->setId(widget.ab10, 9);
	widget.addressBlockGroup->setId(widget.ab11, 10);
	widget.addressBlockGroup->setId(widget.abUse, 11);
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

void AuxControlsWidget::on_addressBlockGroup_buttonClicked(QAbstractButton
    *button)
{
	QCheckBox *sw = qobject_cast<QCheckBox*>(button);
	Q_CHECK_PTR(sw);
	
	if (sw->isChecked())
		_addrStopRegister |=
		    1<<widget.addressBlockGroup->id(button);
	else
		_addrStopRegister &=
		    ~(1<<widget.addressBlockGroup->id(button));
	
	_ural.setAddressBlock(_addrStopRegister);
}

void AuxControlsWidget::on_blockPhiBtn_toggled(bool newVal)
{
	_ural.setPhiBlock(newVal);
}

void AuxControlsWidget::on_stopOnPhiBtn_toggled(bool newVal)
{
	_ural.setPhiStop(newVal);
}

void AuxControlsWidget::on_prinAdderBtn_clicked()
{
    _ural.printAdder();
}

void AuxControlsWidget::on_printModeSwitch_toggled(bool newVal)
{
    emit printMode(newVal);
}

void AuxControlsWidget::on_printMode1_toggled(bool newVal)
{
    if (newVal)
        _ural.setPrintMode(URAL::CPU::PRINT_MODE1);
    else
        _ural.setPrintMode(URAL::CPU::PRINT_NONE);
}

void AuxControlsWidget::on_printMode2_toggled(bool newVal)
{
    if (newVal)
        _ural.setPrintMode(URAL::CPU::PRINT_MODE2);
    else
        _ural.setPrintMode(URAL::CPU::PRINT_NONE);
}
