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

#ifndef CONTROLREADDEVICE_HPP
#define CONTROLREADDEVICE_HPP

#include <QWidget>
#include <QMenu>
#include <QPainter>

#include "ural.hpp"
#include "qcommon.hpp"

namespace Ui {
class ControlReadDevice;
}

/**
 * @brief Виджет просмотра перфоленты
 */
class PunchTapeViewWidget : public QWidget
{
	Q_OBJECT

public:

	PunchTapeViewWidget(QWidget *parent = NULL);
	~PunchTapeViewWidget();

	void setTape(URAL::PunchTape*);

public slots:

	void setPosition(int newVal)
	{
		_position = newVal;
		this->update();
	}

protected:

	void paintEvent(QPaintEvent*) override;

private:

	void	drawFrame(size_t);

	URAL::PunchTape	*_tape;
	QPainter	 _painter;
	size_t		 _position;
};

/**
 * @brief Виджет контрольно-считывающего устройства
 */
class ControlReadDevice : public QWidget, public TapeLoader
{
	Q_OBJECT

public:

	ControlReadDevice(QWidget *parent = NULL);

	~ControlReadDevice();

	void punchNumber(URAL::Number);

protected:

	void contextMenuEvent(QContextMenuEvent*) override;

private slots:

	void newTape();
	void loadTape();
	void saveTape();

private:

	Ui::ControlReadDevice	&ui;

	QMenu			 _contextMenu;
};

#endif // CONTROLREADDEVICE_HPP
