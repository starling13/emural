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

#ifndef _DRUMWIDGET_HPP
#define	_DRUMWIDGET_HPP

#include "ui_DrumWidget.h"

#include "ural.hpp"

class DrumWidget : public QWidget
{
	Q_OBJECT
public:
	
	DrumWidget(URAL::Word_t (&drum)[URAL::drumWordsNumber]);
	
	~DrumWidget();
	
	void resizeEvent(QResizeEvent*) override;

public slots:
	
	void setPosition(int);

    void updateView();
	
private slots:
	
	void on_drumScroll_valueChanged(int);
	
	void on_formatGroup_buttonClicked(int);
	
	void on_drumView_cellChanged(int, int);
	
	void on_clearButton_clicked();

private:

    QString formatValue(quint64);
	
    URAL::Format	_format;
	
	URAL::Word_t (&_drum)[URAL::drumWordsNumber];
	
	size_t _position;
	
	Ui::DrumWidget widget;
};

#endif	/* _DRUMWIDGET_HPP */
