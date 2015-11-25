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
