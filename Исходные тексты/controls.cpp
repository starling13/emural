#include "controls.hpp"

#include <QPaintEvent>
#include <QMouseEvent>
#include <qt4/QtCore/qnamespace.h>
#include <qt4/QtGui/qradiobutton.h>
#include <qt4/QtGui/qpushbutton.h>

AbstractSwitch::AbstractSwitch(QWidget* parent) :
QWidget(parent),
_state(false)
{
}

void BlackButton::paintEvent(QPaintEvent *event)
{
	uint border = this->width() / 6;
	
	_painter.begin(this);
	
	_painter.setBrush(_solid);
	_painter.setPen(Qt::NoPen);
	_painter.drawEllipse(this->rect());
	
	if (!this->isChecked()) {
		_gradient.setCenter(2*border, 2*border);
		_gradient.setRadius(5*border);
	} else {
		_gradient.setCenter(border, border);
		_gradient.setRadius(4*border);
	}
	_gradient.setColorAt(0, Qt::gray);
	_gradient.setColorAt(1, Qt::black);
	
	_painter.setBrush(_gradient);
	_painter.drawEllipse(border, border, this->width()-2*border,
	    this->height()-2*border);
	
	_painter.end();
}

void AbstractSwitch::mousePressEvent(QMouseEvent *event)
{
	if (event->buttons() & Qt::LeftButton)
		this->setState(!_state);
}

void AbstractSwitch::mouseReleaseEvent(QMouseEvent *event)
{

}

void AbstractSwitch::setState(bool newVal)
{
	_state = newVal;
	this->repaint();
	emit toggled(_state);
}

void AbstractSwitch::setChecked(bool value)
{
	_state = value;
	this->repaint();
}

void AbstractSwitch::setUnckecked(bool value)
{
	_state = !value;
	this->repaint();	
}

BlackButton::BlackButton(QWidget* parent) :
QRadioButton(parent)
{
	_solid.setColor(Qt::black);
	_solid.setStyle(Qt::SolidPattern);
}

BlackPushButton::BlackPushButton(QWidget* parent) :
QPushButton(parent)
{
}

void BlackPushButton::paintEvent(QPaintEvent *event)
{
	uint border = this->width() / 6;
	
	_painter.begin(this);
	_painter.setPen(Qt::black);
	
	if (!this->isDown()) {
		_gradient.setCenter(2*border, 2*border);
		_gradient.setRadius(3*border);
	} else {
		_gradient.setCenter(border, border);
		_gradient.setRadius(3*border);
	}
	_gradient.setColorAt(0, Qt::gray);
	_gradient.setColorAt(1, Qt::black);
	
	_painter.setBrush(_gradient);
	_painter.drawEllipse(0,0, this->width()-1, this->height()-1);
	
	_painter.end();
}

bool BlackPushButton::hitButton(const QPoint& pos) const
{
	return (true);
}

Switch::Switch(QWidget* parent) :
QCheckBox(parent)
{
}

void Switch::paintEvent(QPaintEvent *event)
{
	float chord = this->width() / 8;
	
	_painter.begin(this);
	
	_painter.setBrush(Qt::lightGray);
	_painter.drawConvexPolygon(_poly);
	_painter.drawEllipse(2*chord, 2*chord, 4*chord, 4*chord);
	_painter.setBrush(Qt::white);
	_painter.setPen(Qt::NoPen);
	if (this->isChecked()) {
		_painter.drawRect(3.5*chord, 0, chord, 4*chord);
		_painter.drawEllipse(3*chord, 0, 2*chord, 2*chord);
	} else {
		_painter.drawRect(3.5*chord, 4*chord, chord, 4*chord);
		_painter.drawEllipse(3*chord, 6*chord, 2*chord, 2*chord);
	}
	
	_painter.end();
}

void Switch::resizeEvent(QResizeEvent *event)
{
	QCheckBox::resizeEvent(event);
	
	uint chord = this->width() / 6;
	
	_poly.clear();
	_poly.append(QPoint(2*chord, chord));
	_poly.append(QPoint(4*chord, chord));
	_poly.append(QPoint(5*chord, 3*chord));
	_poly.append(QPoint(4*chord, 5*chord));
	_poly.append(QPoint(2*chord, 5*chord));
	_poly.append(QPoint(chord, 3*chord));
}

bool Switch::hitButton(const QPoint&) const
{
	return (true);
}

DigitButton::DigitButton(QWidget* parent) :
QRadioButton(parent)
{
}

void DigitButton::paintEvent(QPaintEvent*)
{
	uint border = this->width() / 6;
	
	_painter.begin(this);
	
	QFontMetrics met(this->font());
	uint horizontalMargin = (this->width()-met.width(this->text()))/2;
	uint verticalMargin = (this->height()-met.height())/2;

	_painter.setBrush(this->palette().button());
	if (!this->isChecked()) {
		_painter.setPen(Qt::NoPen);
		_painter.drawEllipse(0, 0, this->width(), this->height());
	} else
		_painter.drawEllipse(0, 0, this->width()-1, this->height()-1);
	if (!this->isChecked())
		_painter.setPen(this->palette().buttonText().color());
	_painter.drawText(horizontalMargin, met.height()+verticalMargin, this->text());
	
	_painter.end();
}

bool DigitButton::hitButton(const QPoint& pos) const
{
	return (true);
}
