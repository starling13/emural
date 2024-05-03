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

#include "PanelWidget.hpp"
#include "ui_PanelWidget.h"

PanelWidget::PanelWidget(const URAL::CPU &ural) :
widget(*(new Ui::PanelWidget)),
_ural(ural)
{
	widget.setupUi(this);
	
	this->updateRegisters();
}

PanelWidget::~PanelWidget()
{
	delete &widget;
}

void PanelWidget::controlRegisterUpdated()
{
	this->widget.controlRegisterPanel->setValue(_ural.controlRegister().data);
}

void PanelWidget::updateRegisters()
{
	this->widget.controlRegisterPanel->setValue(_ural.controlRegister().data);
	this->widget.adderRegisterPanel->setValue(_ural.S.data);
	this->widget.programCounterPanel->setValue(_ural.regSCHK());
	this->widget.arithmUnitRegisterPanel->setValue(_ural._RGAU.data);
	this->widget.commandRegisterPanel->setValue(_ural._RGK.data);
	this->widget.commandDecoderPanel->setValue(_ural.regDSHK());
	this->widget.statusRegisterPanel->setValue(_ural.statusRegister());
	this->widget.modesPanel->setValue(_ural.statusRegister() >> 8);
}
