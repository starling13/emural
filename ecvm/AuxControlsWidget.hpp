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

#ifndef _AUXCONTROLSWIDGET_HPP
#define	_AUXCONTROLSWIDGET_HPP

#include "ural_cpu.hpp"

#include "ui_AuxControlsWidget.h"

class AuxControlsWidget : public QWidget
{
	Q_OBJECT

signals:	
	
	void controlRegisterAddressChanged(size_t);

    void printMode(bool);

public:
	
	AuxControlsWidget(URAL::CPU&);
	
	~AuxControlsWidget();
	
private slots:
	
	void on_controlRegisterGroup_buttonClicked(QAbstractButton*);
	
	void on_addressBlockGroup_buttonClicked(QAbstractButton*);
    
    void on_controlSwitchGroup_buttonClicked(QAbstractButton*);
	
	void on_blockPhiBtn_toggled(bool);
	
	void on_stopOnPhiBtn_toggled(bool);

    void on_prinAdderBtn_clicked();

    void on_printModeSwitch_toggled(bool);

    void on_printMode1_toggled(bool);

    void on_printMode2_toggled(bool);
	
private:
	
	Ui::AuxControlsWidget	 widget;
	
	uint16_t		_controlRegisterPosition;
	
	uint16_t		_addrStopRegister;
    
    uint8_t        _controlSwitchRegister;
	
	URAL::CPU		&_ural;
};

#endif	/* _AUXCONTROLSWIDGET_HPP */
