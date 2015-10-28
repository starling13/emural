#include "controls.hpp"

#include <QPaintEvent>
#include <QMouseEvent>
#include <qt4/QtCore/qnamespace.h>

BlackButton::BlackButton(QWidget* parent) :
QWidget(parent),
_state(false)
{
	_solid.setColor(Qt::black);
	_solid.setStyle(Qt::SolidPattern);
}

void BlackButton::paintEvent(QPaintEvent *event)
{
	uint border = this->width() / 6;
	
	_painter.begin(this);
	
	_painter.setBrush(_solid);
	_painter.setPen(Qt::NoPen);
	_painter.drawEllipse(this->rect());
	
	if (!_state) {
		_gradient.setCenter(2*border, 2*border);
		_gradient.setRadius(3*border);
	} else {
		_gradient.setCenter(border, border);
		_gradient.setRadius(3*border);
	}
	_gradient.setColorAt(0, Qt::white);
	_gradient.setColorAt(1, Qt::black);
	
	_painter.setBrush(_gradient);
	_painter.drawEllipse(border, border, this->width()-2*border,
	    this->height()-2*border);
	
	_painter.end();
}

void BlackButton::mousePressEvent(QMouseEvent *event)
{
	if (event->buttons() & Qt::LeftButton)
		this->setState(!_state);
}

void BlackButton::mouseReleaseEvent(QMouseEvent *event)
{

}

void BlackButton::setState(bool newVal)
{
	_state = newVal;
	this->repaint();
	emit toggled(_state);
}

void BlackButton::setChecked(bool value)
{
	_state = value;
	this->repaint();
}

void BlackButton::setUnckecked(bool value)
{
	_state = !value;
	this->repaint();	
}
