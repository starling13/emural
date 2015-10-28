/*
 * File:   DrumWidget.cpp
 * Author: starling13
 *
 * Created on 27 Октябрь 2015 г., 16:40
 */

#include "DrumWidget.hpp"

#include <QResizeEvent>
#include <QDebug>

DrumWidget::DrumWidget(URAL::Word_t (&drum)[1024]) :
_format(OCT),
_drum(drum),
_position(0ul)
{
	widget.setupUi(this);
	
	widget.formatGroup->setId(widget.octSwitch, OCT);
	widget.formatGroup->setId(widget.binSwitch, BIN);
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
	Q_ASSERT((newVal == OCT) || (newVal == BIN));
	
	this->_format = Format(newVal);
	this->updateView();
}

void DrumWidget::on_drumView_cellChanged(int row, int col)
{
	uint	data = this->widget.drumView->item(row, col)->text().toUInt();
	size_t	wordNumber = this->_position / 2 + row;
	
	if (col == 1)
		this->_drum[wordNumber].halfWords.most = data;
	else if (col == 2)
		this->_drum[wordNumber].halfWords.least = data;
}

void DrumWidget::updateView()
{
	size_t			 rowCount;
	QTableWidgetItem	*item[2];
	
	this->widget.drumView->blockSignals(true);
	
	this->widget.drumView->setRowCount(1);	
	rowCount = this->widget.drumView->height() /
	    this->widget.drumView->rowHeight(0) - 1;

	if (this->_position + rowCount > 2046)
		rowCount = (2048-this->_position) / 2;
	
	this->widget.drumView->setRowCount(rowCount);
	for (size_t i=0; i<rowCount; ++i) {
		size_t wordIndex = _position / 2 + i;
		item[0] = new QTableWidgetItem(QString("0").append(
		    QString::number(this->_position + 2*i, 8)));
		this->widget.drumView->setItem(i, 0, item[0]);
		switch (this->_format) {
		case OCT:
			item[0] = new QTableWidgetItem(QString::number(
			    _drum[wordIndex][1].data, 8));
			item[1] = new QTableWidgetItem(QString::number(
			    _drum[wordIndex][2].data, 8));
			break;
		case BIN:
			item[0] = new QTableWidgetItem(QString::number(
			    _drum[_position + 2*i][2].data, 2));
			item[1] = new QTableWidgetItem(QString::number(
			    _drum[_position + 2*i][1].data, 2));
			break;
		}
		this->widget.drumView->setItem(i, 1, item[0]);
		this->widget.drumView->setItem(i, 2, item[1]);
	}
	
	this->widget.drumView->blockSignals(false);
}
