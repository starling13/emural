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

#ifndef PRINTDEVICE_HPP
#define PRINTDEVICE_HPP

#include "ural_cpu.hpp"

#include <QWidget>
#include <QMetaType>
#include <QThread>
#include <QMutex>
#include <QWaitCondition>
#include <QTime>

Q_DECLARE_METATYPE(URAL::Word_t);
Q_DECLARE_METATYPE(URAL::HalfWord_t);

namespace Ui {
class PrintDevice;
}

/**
 * @brief Qt4-реализация цифрового печатающего устройства
 */
class QtPrintDevice : public QWidget, public URAL::IPrintDevice
{
	Q_OBJECT

public:

	QtPrintDevice(QWidget *parent = 0);
	~QtPrintDevice();

	void start();
	void printWord(URAL::Word_t) override;
	void printCommand(quint16, URAL::HalfWord_t) override;
	void printResult(URAL::Word_t) override;
	void lineFeed() override;

public slots:

	void setMode(bool);

private slots:

	void printBuffer(QString);
	void on_addCommentButton_clicked();
	void on_groupModeSwitch_toggled(bool);
	void on_counterResetButton_clicked();

private:

	QString wordToString(URAL::Word_t);
	QString commandToString(URAL::HalfWord_t);

	class Worker;
	friend class Worker;

	QMutex		 _cpuLock;
	QWaitCondition	 _uralCondition, _cpuCondition;
	Ui::PrintDevice	&ui;
	URAL::Format	 _mode;
	quint16		 _counter;
	Worker		&_worker;
	QTime		 _startTime;
	QString		 _buffer;
	bool		 _groupCount;
};

class QtPrintDevice::Worker : public QThread
{
	Q_OBJECT

signals:

	void print(QString);

public:

	Worker(QtPrintDevice&);

protected:

	void run() override;

private:

	QtPrintDevice   &_owner;

};

#endif // PRINTDEVICE_HPP
