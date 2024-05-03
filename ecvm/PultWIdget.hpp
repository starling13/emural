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

#ifndef _PULTWIDGET_HPP
#define	_PULTWIDGET_HPP

#include "ui_PultWIdget.h"

#include "controls.hpp"
#include "ural_cpu.hpp"

class PultWIdget : public QWidget
{
	Q_OBJECT
	
signals:

    void start();

    void stop();

    void singleStep();

    void regsUpdated();
	
public:
	
	PultWIdget(URAL::CPU&);
	
	~PultWIdget();
	
private slots:
	
	void on_singleStepButton_clicked();
	
	void on_resetButton_clicked();
	
	void on_startButton_clicked();
	
	void on_stopButton_clicked();
	
	void on_commandResetButton_clicked();
	
	void on_commandSetButton_clicked();
	
	void on_addr1group_buttonClicked(int);
	void on_addr2group_buttonClicked(int);
	void on_addr3group_buttonClicked(int);
	void on_addr4group_buttonClicked(int);
	void on_addr5group_buttonClicked(int);
	void on_addr6group_buttonClicked(int);

    void on_reg1group_buttonClicked(int);
    void on_reg2group_buttonClicked(int);
    void on_reg3group_buttonClicked(int);
    void on_reg4group_buttonClicked(int);
    void on_reg5group_buttonClicked(int);
    void on_reg6group_buttonClicked(int);
    void on_reg7group_buttonClicked(int);
    void on_reg8group_buttonClicked(int);
    void on_reg9group_buttonClicked(int);
    void on_reg10group_buttonClicked(int);
    void on_reg11group_buttonClicked(int);
    void on_reg12group_buttonClicked(int);

    void on_adderSetButton_clicked();

    void on_adderResetButton_clicked();
	
private:
	
	uint8_t _tactSkip;
	
	Ui::PultWIdget widget;
	
	URAL::CPU	&_ural;
	
	URAL::HalfWord_t	_commandWord;

    URAL::Word_t        _adderWord;
	
	QVector<QButtonGroup*>	_commandButtons;

    QVector<QButtonGroup*>	_adderButtons;
};

#endif	/* _PULTWIDGET_HPP */
