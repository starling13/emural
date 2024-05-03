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

#ifndef PUNCHDRIVES_HPP
#define PUNCHDRIVES_HPP

#include <unistd.h>

#include "ural.hpp"
#include "qcommon.hpp"

#include <QWidget>
#include <QAbstractTableModel>

namespace Ui {
    class PunchTapeWidget;
} // namespace Ui

class QtPunchDrive : public QWidget, public TapeLoader, public URAL::IExtMemoryDevice
{
	Q_OBJECT

public:

	QtPunchDrive();
	~QtPunchDrive();

	void		searchZone(uint8_t) override;
	URAL::Word_t	readWord() override;
	bool		readHalfWord(URAL::HalfWord_t&) override;

private slots:

	void on_loadTapeButton_clicked();

private:

	Q_DISABLE_COPY(QtPunchDrive)

	class	TapeTableModel;
	friend class	TapeTableModel;

	Ui::PunchTapeWidget	&widget;
	ssize_t			 _tapePosition;
	TapeTableModel		&_tapeModel;
};

class QtPunchDrive::TapeTableModel : public QAbstractTableModel
{
	Q_OBJECT

public:

	TapeTableModel(QtPunchDrive&);

	int rowCount(const QModelIndex&) const override;
	int columnCount(const QModelIndex&) const override;
	QVariant data(const QModelIndex&, int) const override;
	QVariant headerData(int, Qt::Orientation, int) const override;

	void updateData()
	{
		this->beginResetModel();
		this->endResetModel();
	}

private:

	enum Columns_t
	{
		ZONE = 0,
		NUMBER = 1,
	};

	QtPunchDrive	&_owner;
};

#endif // PUNCHDRIVES_HPP
