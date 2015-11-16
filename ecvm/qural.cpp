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
