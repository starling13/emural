/*
 *   emural - эмулятор ЭЦВМ семейства "Урал"
 *
 *   Copyright (C) 2015 А.В. Скворцов <starling13@gmail.com>
 *
 *   Данная программа является свободным программным обеспечением. Вы
 *   вправе распространять её и/или модифицировать в соответствии с
 *   условиями версии 2, либо по вашему выбору с условиями более поздней
 *   версии Стандартной Общественной Лицензии GNU, опубликованной Free
 *   Software Foundation.
 *
 *   Мы распространяем данную программу в надежде на то, что она будет
 *   вам полезной, однако НЕ ПРЕДОСТАВЛЯЕМ НА НЕЁ НИКАКИХ ГАРАНТИЙ, в том
 *   числе ГАРАНТИИ ТОВАРНОГО СОСТОЯНИЯ ПРИ ПРОДАЖЕ и ПРИГОДНОСТИ ДЛЯ
 *   ИСПОЛЬЗОВАНИЯ В КОНКРЕТНЫХ ЦЕЛЯХ. Для получения более подробной
 *   информации ознакомьтесь со Стандартной Общественной Лицензией GNU.
 *
 *   Вместе с данной программой вы должны были получить экземпляр
 *   Стандартной Общественной Лицензии GNU. Если вы его не получили,
 *   сообщите об этом в Free Software Foundation, Inc.,
 *   51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
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

    QTimer		_timer;
};

#endif // QURAL_HPP
