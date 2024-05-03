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

#include "qural.hpp"
#include <QThread>
#include <QDebug>

URALWrapper::URALWrapper(URAL::CPU &ural) :
	_ural(ural),
	_timer(*(new QTimer(NULL)))
{
	_timer.start(10);
}

URALWrapper::~URALWrapper()
{
	_timer.stop();
	delete &_timer;
}

void URALWrapper::singleStep()
{
	qDebug() << "Single step" << QThread::currentThreadId();
	_ural.singleStep();
	qDebug() << "end";
	emit tactFinished();
	emit stopped();
}

void URALWrapper::start()
{
	_ural.start();
	QObject::connect(&_timer, SIGNAL(timeout()), this,
	    SLOT(timerSignaled()));
}

void URALWrapper::stop()
{
	QObject::disconnect(&_timer, SIGNAL(timeout()), this,
	    SLOT(timerSignaled()));
	_ural.stop();
	emit stopped();
}

void URALWrapper::timerSignaled()
{
	QObject::disconnect(&_timer, SIGNAL(timeout()), this,
	    SLOT(timerSignaled()));
	if (!_ural.tact()) {
		emit tactFinished();
		emit stopped();
	} else {
		emit tactFinished();
		QObject::connect(&_timer, SIGNAL(timeout()), this,
		    SLOT(timerSignaled()));
	}
}
