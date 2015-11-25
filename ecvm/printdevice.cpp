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

#include "printdevice.hpp"
#include "ui_printdevice.h"

#include <unistd.h>

#include <QDebug>

QtPrintDevice::Worker::Worker(QtPrintDevice &owner) :
	_owner(owner)
{
}

void QtPrintDevice::Worker::run()
{
	while (true) {
		QMutexLocker    locker(&_owner._cpuLock);

		while (_owner._buffer.isEmpty())
			_owner._cpuCondition.wait(&_owner._cpuLock);
		_owner._startTime.start();
		emit print(_owner._buffer);

		int elapsed = _owner._startTime.elapsed();
		if (elapsed < 640)
			QThread::msleep(640-elapsed);
		_owner._buffer = "";
		_owner._uralCondition.wakeAll();
	}
}

QtPrintDevice::QtPrintDevice(QWidget *parent) :
	QWidget(parent),
	ui(*(new Ui::PrintDevice)),
	_mode(URAL::DEC),
	_counter(0),
	_worker(*(new Worker(*this))),
	_groupCount(false)
{
	ui.setupUi(this);

	QObject::connect(&_worker, SIGNAL(print(QString)), this, SLOT(printBuffer(QString)),
	   Qt::QueuedConnection);
}

QtPrintDevice::~QtPrintDevice()
{
	_worker.terminate();
	while (_worker.isRunning());

	delete &_worker;
	delete &ui;
}

void QtPrintDevice::start()
{
	_worker.start();
}

void QtPrintDevice::setMode(bool newVal)
{
	if (newVal)
		_mode = URAL::OCT;
	else
		_mode = URAL::DEC;
}

void QtPrintDevice::printBuffer(QString buffer)
{
	QString str = QString("<p><strong>").append(buffer).append("</strong></p>");
	qDebug() << str;
	ui.textArea->append(str);
}

void QtPrintDevice::on_addCommentButton_clicked()
{
	ui.textArea->append(QString("<p><em>").append(ui.commentLine->text()).append(
	    "</em></p>"));
}

void QtPrintDevice::on_counterResetButton_clicked()
{
	_counter = 0;
}

void QtPrintDevice::on_groupModeSwitch_toggled(bool newVal)
{
	_groupCount = newVal;
}

void QtPrintDevice::printWord(URAL::Word_t word)
{
	QMutexLocker    locker(&_cpuLock);

	while (!_buffer.isEmpty())
		_uralCondition.wait(&_cpuLock);
	_buffer = QString("&nbsp;&nbsp;&nbsp;&nbsp;").append(wordToString(word));
	_cpuCondition.wakeAll();
}

void QtPrintDevice::printCommand(quint16 addr, URAL::HalfWord_t command)
{
	QMutexLocker    locker(&_cpuLock);

	while (!_buffer.isEmpty())
		_uralCondition.wait(&_cpuLock);
	for (int i=9; i>=0; i-=3)
		_buffer.append(QString::number((addr >> i)&7));
	_buffer.append("&nbsp;&nbsp;&nbsp;&nbsp;").append(commandToString(command));
	_cpuCondition.wakeAll();
}

void QtPrintDevice::printResult(URAL::Word_t word)
{
	QMutexLocker    locker(&_cpuLock);

	while (!_buffer.isEmpty())
		_uralCondition.wait(&_cpuLock);
	if (!_groupCount) {
		++_counter;
		_buffer = QString::number(_counter);
		while (_buffer.size() < 4)
			_buffer.prepend('0');
	} else
		_buffer = QString("&nbsp;&nbsp;&nbsp;&nbsp;");
	_buffer.append(QString("&nbsp;&nbsp;&nbsp;&nbsp;").
	    append(wordToString(word)));
	_cpuCondition.wakeAll();
}

void QtPrintDevice::lineFeed()
{
	QMutexLocker    locker(&_cpuLock);

	while (!_buffer.isEmpty())
		_uralCondition.wait(&_cpuLock);
	if (_groupCount) {
		++_counter;
		_buffer = QString::number(_counter);
		while (_buffer.size() < 4)
			_buffer.prepend('0');
	} else
		_buffer = ' ';
	_cpuCondition.wakeAll();
}

QString QtPrintDevice::wordToString(URAL::Word_t word)
{
	QString         buf;

	if (_mode == URAL::OCT) {
		buf.append(QString::number(word.triplets.t12));
		buf.append(QString::number(word.triplets.t11));
		buf.append(QString::number(word.triplets.t10));
		buf.append(QString::number(word.triplets.t9));
		buf.append(QString::number(word.triplets.t8));
		buf.append(QString::number(word.triplets.t7));
		buf.append(' ');
		buf.append(QString::number(word.triplets.t6));
		buf.append(QString::number(word.triplets.t5));
		buf.append(QString::number(word.triplets.t4));
		buf.append(QString::number(word.triplets.t3));
		buf.append(QString::number(word.triplets.t2));
		buf.append(QString::number(word.triplets.t1));
	} else {
		if (word.dPrec.sign())
			buf.append('-');
		else
			buf.append(' ');
		buf.append(QString::number(word.quartets.q9 % 10));
		buf.append(QString::number(word.quartets.q8 % 10));
		buf.append(QString::number(word.quartets.q7 % 10));
		buf.append(QString::number(word.quartets.q6 % 10));
		buf.append(QString::number(word.quartets.q5 % 10));
		buf.append(QString::number(word.quartets.q4 % 10));
		buf.append(QString::number(word.quartets.q3 % 10));
		buf.append(QString::number(word.quartets.q2 % 10));
		buf.append(QString::number(word.quartets.q1 * 2 % 10));
	}

	return (buf);
}

QString QtPrintDevice::commandToString(URAL::HalfWord_t command)
{
	QString buf;

	if (command.command.indexFlag)
		buf.append('-');
	else
		buf.append(' ');

	buf.append(QString::number((command.command.opCode >> 3) & 7));
	buf.append(QString::number(command.command.opCode & 7));
	buf.append(' ');
	buf.append(QString::number(command.triplets.t4 & 3));
	buf.append(QString::number(command.triplets.t3));
	buf.append(QString::number(command.triplets.t2));
	buf.append(QString::number(command.triplets.t1));

	return (buf);
}
