#include "DisplayPanel.hpp"

#include <QtGui/QPaintEvent>
#include <qt4/QtGui/qframe.h>

DisplayPanel::DisplayPanel(const URAL::CPU &ural):
_ural(ural),
_clock(this),
_S(ural.S, QString::fromUtf8(u8"С        У        М        М        А        Т"
    u8"        О        Р"), this)
{
	_clock.setGeometry(270, 200, 100, 100);
	_S.setGeometry(0,0,640,50);
}

DisplayPanel::~DisplayPanel()
{
}

void DisplayPanel::tact()
{
	this->_clock.setTime(QTime::currentTime());
	this->repaint();
}
/*
void DisplayPanel::paintEvent(QPaintEvent *event)
{	
	_painter.begin(this);
	
	QBrush	brush(Qt::darkGray, Qt::SolidPattern);
	QPen	pen(Qt::white);
	_painter.setBrush(brush);
	_painter.setPen(pen);
	
	_painter.fillRect(this->rect(), _painter.brush());
	
	_painter.end();
	
	//QFrame::paintEvent(event);
}
*/
LampArray::LampArray(const URAL::Word_t &val, const QString &label,
    QWidget *parent) :
QWidget(parent),
_value(val),
_label(label)
{
}

void LampArray::paintEvent(QPaintEvent *event)
{
	int x = 625;
	_painter.begin(this);
	
	QBrush	brush(Qt::darkGray, Qt::SolidPattern);
	QPen	pen(Qt::white);
	_painter.setBrush(brush);
	_painter.setPen(pen);
	
	_painter.fillRect(this->rect(), _painter.brush());
	_painter.drawText(0,20, _label);
	for (size_t i = 0; i<36; ++i) {
		x -= 15;
		if (!(i % 3)) x-=5;
		_painter.drawEllipse(x, 25, 13, 13);
	}
	_painter.end();
}
