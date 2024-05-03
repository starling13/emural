/*
 * This file is part of EMURAL - emulator for Ural computer from 1950s
 * Copyright (C) 2015-2024 Andrey V. Skvortsov <starling13@gmail.com>
 *
 * EMURAL is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "AuxControlsWidget.hpp"

AuxControlsWidget::AuxControlsWidget(URAL::CPU &ural) :
_controlRegisterPosition(0u),
_addrStopRegister(0u),
_controlSwitchRegister(0),
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
    
    widget.controlSwitchGroup->setId(widget.sw1, 1);
    widget.controlSwitchGroup->setId(widget.sw2, 2);
    widget.controlSwitchGroup->setId(widget.sw3, 3);
    widget.controlSwitchGroup->setId(widget.sw4, 4);
    widget.controlSwitchGroup->setId(widget.sw5, 5);
    widget.controlSwitchGroup->setId(widget.sw6, 6);
    widget.controlSwitchGroup->setId(widget.sw7, 7);
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

void AuxControlsWidget::on_controlSwitchGroup_buttonClicked(QAbstractButton
    *button)
{
	QCheckBox *sw = qobject_cast<QCheckBox*>(button);
	Q_CHECK_PTR(sw);
	
	if (sw->isChecked())
		_controlSwitchRegister |=
            1<<widget.controlSwitchGroup->id(button);
	else
		_controlSwitchRegister &=
		    ~(1<<widget.controlSwitchGroup->id(button));
	
	_ural.setControlSwitchRegister(_controlSwitchRegister);
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
        _ural.setPrintMode(URAL::PRINT_MODE1);
    else
        _ural.setPrintMode(URAL::PRINT_NONE);
}

void AuxControlsWidget::on_printMode2_toggled(bool newVal)
{
    if (newVal)
        _ural.setPrintMode(URAL::PRINT_MODE2);
    else
        _ural.setPrintMode(URAL::PRINT_NONE);
}
