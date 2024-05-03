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

#include "DrumWidget.hpp"

#include <cstring>

#include <QResizeEvent>
#include <QDebug>
#include <QMessageBox>

#include "delegates.hpp"

DrumWidget::DrumWidget(URAL::Word_t (&drum)[URAL::drumWordsNumber]) :
_format(URAL::OCT),
_drum(drum),
_position(0ul)
{
	widget.setupUi(this);
	
	widget.formatGroup->setId(widget.octSwitch, URAL::OCT);
	widget.formatGroup->setId(widget.binSwitch, URAL::BIN);

	widget.drumView->setItemDelegate(new NumberDelegate(18, _format, this));
}

DrumWidget::~DrumWidget()
{
}

void DrumWidget::resizeEvent(QResizeEvent *event)
{
	QWidget::resizeEvent(event);
	updateView();
}

void DrumWidget::setPosition(int newVal)
{
	qDebug() << __PRETTY_FUNCTION__ << newVal;
	this->_position = newVal;
	this->updateView();
}

void DrumWidget::on_drumScroll_valueChanged(int value)
{
	qDebug() << __PRETTY_FUNCTION__ << value;
	this->setPosition(value);
}

void DrumWidget::on_formatGroup_buttonClicked(int newVal)
{
	Q_ASSERT((newVal == URAL::OCT) || (newVal == URAL::BIN));
	
	this->_format = URAL::Format(newVal);
	widget.drumView->setItemDelegate(new NumberDelegate(18, _format, this));
	this->updateView();
}

void DrumWidget::on_drumView_cellChanged(int row, int col)
{
	bool	ok;
	uint	data;
	size_t	wordNumber;
	
	data = this->widget.drumView->item(row, col)->text().toUInt(&ok,
	    int(this->_format));
	wordNumber = this->_position / 2 + row;
	
	if (col == 0)
		this->_drum[wordNumber].halfWords.most = data;
	else if (col == 1)
		this->_drum[wordNumber].halfWords.least = data;
	else
		qWarning() << u8"Недопустимый номер столбца" << col;
}

void DrumWidget::on_clearButton_clicked()
{
	if (QMessageBox::question(this, QString::fromUtf8(u8"Очистка ОЗУ"),
	    QString::fromUtf8(u8"Очистить все ячейки магнитного барабана?"),
	    QString::fromUtf8(u8"Да"), QString::fromUtf8(u8"Нет")) == 0) {
		std::memset(&this->_drum, 0, sizeof (this->_drum));
		this->updateView();
	}
}

void DrumWidget::updateView()
{
	size_t			 rowCount;
	QTableWidgetItem	*item;
	
	this->widget.drumView->blockSignals(true);
	
	this->widget.drumView->setRowCount(1);	
	rowCount = this->widget.drumView->height() /
	    this->widget.drumView->rowHeight(0) - 1;

	if (this->_position + 2*rowCount > 2046)
		rowCount = (2048-this->_position) / 2;
	
	this->widget.drumView->setRowCount(rowCount);
	for (size_t i=0; i<rowCount; ++i) {
		size_t wordIndex = _position / 2 + i;
		
		item = new QTableWidgetItem(QString("0").append(
		    QString::number(this->_position + 2*i, 8)));
		this->widget.drumView->setVerticalHeaderItem(i, item);

        item = new QTableWidgetItem(formatValue(_drum[wordIndex][1].data));
		this->widget.drumView->setItem(i, 0, item);
		
        item = new QTableWidgetItem(formatValue(_drum[wordIndex][2].data));
		this->widget.drumView->setItem(i, 1, item);
	}
	
	this->widget.drumView->blockSignals(false);
}

QString DrumWidget::formatValue(quint64 val)
{
    QString result = QString::number(val, int(this->_format));
    switch (this->_format) {
    case URAL::BIN:
        while (result.length() < 18)
            result.prepend('0');
        break;
    case URAL::OCT:
        while (result.length() < 6)
            result.prepend('0');
        break;
    default:
	    break;
    }
    return (result);
}
