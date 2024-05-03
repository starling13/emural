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

#ifndef QURAL_HPP
#define QURAL_HPP

#include "ural_cpu.hpp"
#include <QObject>
#include <QTimer>
#include <QDebug>

#ifndef QT_NO_DEBUG_OUTPUT
#define LOG_DEBUG
#else
#define LOG_DEBUG
#endif

class Logger
{
public:
	enum Verbosity_t
	{
		/**
		 * Не выводить информацию
		 */
		NONE = 0,
		/**
		 * Минимальный уровень вывода
		 */
		MINIMAL = 1,
		/**
		 * Средний уровень вывода
		 */
		MEDIUM = 2,
		/**
		 * Значительный уровень вывода
		 */
		MORE = 3,
		/**
		 * Максимальный уровень вывода
		 */
		VERBOSE = 4,

		VERBOSITY_SIZE
	};
private:

	class Log
	{
	public:
		template <typename... Args>
		void log(Verbosity_t verbosity, const Args&... args);
	};

	Q_DISABLE_COPY(Logger)
};

template <typename... Args>
void Logger::Log::log(Verbosity_t verbosity, const Args&... args)
{
	//if ((m_verbosityLevel >= verbosity)) {
	//	assert(Logger::m_lock != NULL);
	//	posix::threads::CriticalSection
	//	    cs(*Logger::m_lock);
	//	posix::time::Timespec currentTime =
	//	    Logger::m_clock.getTime();

	//	_stream << (currentTime -= Logger::_startTime)
	//	    << ":[" << _target << "](" << verbosity
	//	    << ")\t";
	//	__log(args...);
	//}
}

class URALWrapper : public QObject
{
	Q_OBJECT

public:

	URALWrapper(URAL::CPU&);
	~URALWrapper();

signals:

	void stopped();

	void tactFinished();

public slots:

	void singleStep();

	void start();

	void stop();

private slots:

	void timerSignaled();

private:

	URAL::CPU   &_ural;

	QTimer		&_timer;
};

#endif // QURAL_HPP
