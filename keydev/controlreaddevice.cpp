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

#include "controlreaddevice.hpp"
#include "ui_controlreaddevice.h"

#include <cstring>
#include <string>
#include <cassert>

#include <QDebug>
#include <QFileDialog>
#include <QContextMenuEvent>

PunchTapeViewWidget::PunchTapeViewWidget(QWidget *parent) :
	QWidget(parent),
	_tape(NULL)
{
}

PunchTapeViewWidget::~PunchTapeViewWidget()
{
}

void PunchTapeViewWidget::setTape(URAL::PunchTape *newVal)
{
	_tape = newVal;
	_position = 0;
	this->update();
}

void PunchTapeViewWidget::paintEvent(QPaintEvent*)
{
	if (_tape == NULL)
		return;

	double ratio = double (height()) / double (width());
	double frameTop = 0;

	_painter.begin(this);

	_painter.scale(width() / 400.0, height() / (ratio * 400.0));
	_painter.setBrush(Qt::white);

	size_t frameCounter = 0;
	int scaledHeight = 400.0 * ratio;
	while (frameTop < scaledHeight) {
		if (_tape->tapeData().size() > _position+frameCounter)
			drawFrame(frameCounter++);
		else
			break;
		frameTop += 190.0;
	}

	_painter.end();
}

void PunchTapeViewWidget::drawFrame(size_t number)
{
	Q_CHECK_PTR(_tape);
	Q_ASSERT(_tape->tapeData().size() >= _position+number);

	qDebug() << __PRETTY_FUNCTION__;

	unsigned hShift = 50.0;
	unsigned shift = 190.0 * number;
	_painter.fillRect(0, shift, hShift, 190.0, Qt::white);
	_painter.setPen(Qt::black);
	_painter.drawLine(0,shift,hShift,shift);
	_painter.setFont(QFont("Sans", 17.0));
	_painter.drawText(0.0, shift+10.0, hShift, 50.0, 0, QString::number(_position+number));

	_painter.setPen(Qt::NoPen);
	_painter.fillRect(hShift, shift, 350.0, 190.0, Qt::black);

	for (int i=0; i<4; ++i) {
		_painter.drawRect(hShift+20.150, shift + 13.85 + 47.5*i, 28.0, 19.8);
		_painter.drawRect(hShift+301.85, shift + 13.85 + 47.5*i, 28.0, 19.8);

		for (int j=0; j<11; ++j) {
			char digit = _tape->tapeData().at(_position+number).data[j];
			if (digit & (1<<(3-i)))
				_painter.drawRect(hShift+53.0 + 23.0*j, shift + 9.0 + 47.5*i, 12.0, 30.0);
		}
	}
}

ControlReadDevice::ControlReadDevice(QWidget *parent) :
	QWidget(parent),
	ui(*(new Ui::ControlReadDevice))
{
	ui.setupUi(this);

	ui.stretchViewWidget->setTape(&_tape);

	_contextMenu.addAction(QString::fromUtf8(u8"Новая"), this, SLOT(newTape()));
	_contextMenu.addAction(QString::fromUtf8(u8"Загрузить"), this, SLOT(loadTape()));
	_contextMenu.addAction(QString::fromUtf8(u8"Сохранить"), this, SLOT(saveTape()));

	QObject::connect(this->ui.scrollBar, SIGNAL(valueChanged(int)),
	    this->ui.stretchViewWidget, SLOT(setPosition(int)));
}

ControlReadDevice::~ControlReadDevice()
{
	delete &ui;
}

void ControlReadDevice::punchNumber(URAL::Number newVal)
{
	if (_tape.tapeData().size() < ui.scrollBar->value()+3u)
		_tape.tapeData().resize(ui.scrollBar->value()+3);
	ui.scrollBar->setMaximum(_tape.tapeData().size()-1);
	ui.scrollBar->setValue(ui.scrollBar->value()+1);
	_tape.tapeData().operator [](ui.scrollBar->value()+1) = newVal;
}

void ControlReadDevice::newTape()
{
	_tape.tapeData().clear();
	ui.scrollBar->setMaximum(0);
	ui.stretchViewWidget->update();
}

void ControlReadDevice::contextMenuEvent(QContextMenuEvent *event)
{
	_contextMenu.popup(event->globalPos());
}

void ControlReadDevice::loadTape()
{
	this->loadTapeFromFile();
	if (_tape.tapeData().size() > 1)
		ui.scrollBar->setMaximum(_tape.tapeData().size()-1);
	ui.stretchViewWidget->update();
}

void ControlReadDevice::saveTape()
{
	QString fileName;

	fileName = QFileDialog::getSaveFileName(this, QString::fromUtf8(
	    u8"ыбор файла перфоленты для загрузки"),QDir::homePath(), "*.upt");
	if (!fileName.isEmpty()) {
		QFile file(fileName);
		if (file.open(QFile::WriteOnly)) {
			QByteArray ba(_tape.tapeData().size()*11, Qt::Uninitialized);
			QByteArray buf(_tape.tapeData().size()*12, Qt::Uninitialized);
			buf.resize(0);
			_tape.saveData((uint8_t*)ba.data(), ba.size());
			for (int i=0; i<ba.size(); i+=11) {
				for (int j=0; j<11; ++j)
					buf.push_back(QString::number(ba[i+j]).at(0).toAscii());
				buf.push_back('\n');
			}
			file.write(buf);
		} else
			qWarning() << QString::fromUtf8(u8"евозможно открыть файл") << fileName;
	}
}
