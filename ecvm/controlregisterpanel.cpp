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

#include "controlregisterpanel.hpp"

#include "ui_StopReasonsPanel.h"
#include "ui_DebugPanel.h"

const QPixmap	*LampPanel::_lampPixmaps[2] = {NULL, NULL};

LampPanel::LampPanel(QWidget *parent) :
QWidget(parent)
{
	// Если статические изображения ещё не загружены другим экземпляром панели,
	// загрузить их
	if (!_lampPixmaps[0])
		_lampPixmaps[0] = new QPixmap(QString::fromUtf8(
            u8":/images/lamp_off.png"));
	if (!_lampPixmaps[1])
		_lampPixmaps[1] = new QPixmap(QString::fromUtf8(
            u8":/images/lamp_on.png"));
}

void LampPanel::setValue(uint64_t newValue)
{
	for (int i=0; i<_lamps.size(); ++i) {
		if (newValue & (1ull<<i))
			_lamps[i]->setPixmap(*_lampPixmaps[1]);
		else
			_lamps[i]->setPixmap(*_lampPixmaps[0]);
	}
}

ControlRegisterPanel::ControlRegisterPanel(QWidget *parent) :
LampPanel(parent)
{
	widget.setupUi(this);
	
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

AdderRegisterPanel::AdderRegisterPanel(QWidget *parent) :
LampPanel(parent)
{
	widget.setupUi(this);
	
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
	_lamps.push_back(widget.lamp36);
}

AdderRegisterPanel::~AdderRegisterPanel()
{
}

PCWidget::PCWidget(QWidget *parent) :
LampPanel(parent)
{
	widget.setupUi(this);
	
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
}

PCWidget::~PCWidget()
{
}

ArithmUnitRegisterPanel::ArithmUnitRegisterPanel(QWidget *parent) :
LampPanel(parent)
{
	widget.setupUi(this);
	
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

ArithmUnitRegisterPanel::~ArithmUnitRegisterPanel()
{
}

CommandRegisterPanel::CommandRegisterPanel(QWidget *parent) :
LampPanel(parent)
{
	widget.setupUi(this);
	
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
}

CommandRegisterPanel::~CommandRegisterPanel()
{
}

CommandDecoderWidget::CommandDecoderWidget(QWidget *parent) :
LampPanel(parent)
{
	widget.setupUi(this);
	
	_lamps.push_back(widget.lamp0);
	_lamps.push_back(widget.lamp1);
	_lamps.push_back(widget.lamp2);
	_lamps.push_back(widget.lamp3);
	_lamps.push_back(widget.lamp4);
}

CommandDecoderWidget::~CommandDecoderWidget()
{
}

StatusRegisterPanel::StatusRegisterPanel(QWidget *parent) :
LampPanel(parent)
{
	widget.setupUi(this);
	
	_lamps.push_back(widget.omegaLamp);
	_lamps.push_back(widget.phiLamp);
}

StatusRegisterPanel::~StatusRegisterPanel()
{
}

ModesPanel::ModesPanel(QWidget *parent) :
LampPanel(parent)
{
    widget.setupUi(this);

    _lamps.push_back(widget.lampStop);
    _lamps.push_back(widget.lampPeriodicSend);
    _lamps.push_back(widget.lampPrint2);
    _lamps.push_back(widget.lampPrint1);
    _lamps.push_back(widget.lampPerforating);
    _lamps.push_back(widget.lampPrintResults);
    _lamps.push_back(widget.lampPerfolentRead);
    _lamps.push_back(widget.lampReadMagnetLent);
}

ModesPanel::~ModesPanel()
{
}

StopReasonsPanel::StopReasonsPanel(QWidget *parent) :
LampPanel(parent),
widget(*(new Ui::StopReasonsPanel))
{
    widget.setupUi(this);

    _lamps.push_back(widget.lampPerfRead);
    _lamps.push_back(widget.lampMagnetRead);
    _lamps.push_back(widget.lampPowerFail);
}

StopReasonsPanel::~StopReasonsPanel()
{
    delete &widget;
}

DebugPanel::DebugPanel(QWidget *parent) :
LampPanel(parent),
widget(*(new Ui::DebugPanel))
{
    widget.setupUi(this);

    _lamps.push_back(widget.lampPhi);
    _lamps.push_back(widget.lampDrum);
    _lamps.push_back(widget.lampCommandReg);
    _lamps.push_back(widget.lampMaintenance);
}

DebugPanel::~DebugPanel()
{
    delete &widget;
}
