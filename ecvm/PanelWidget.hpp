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

#ifndef _PANELWIDGET_HPP
#define	_PANELWIDGET_HPP

#include "ural_cpu.hpp"

#include <QWidget>

namespace Ui
{
    class PanelWidget;
}

class PanelWidget : public QWidget
{
	Q_OBJECT
	
public slots:
	
	void updateRegisters();
	
	void controlRegisterUpdated();
	
public:
	
	PanelWidget(const URAL::CPU&);
	
	~PanelWidget();
	
private:
	
    Ui::PanelWidget &widget;
	
	const URAL::CPU &_ural;
};

#endif	/* _PANELWIDGET_HPP */
