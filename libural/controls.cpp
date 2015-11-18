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

#include "controls.hpp"

#include <QPaintEvent>
#include <QMouseEvent>
#include <QDebug>

AbstractSwitch::AbstractSwitch(QWidget* parent) :
QWidget(parent),
_state(false)
{
}

void BlackButton::paintEvent(QPaintEvent*)
{
	uint border = this->width() / 6;
	
	_painter.begin(this);
    _painter.setRenderHint(QPainter::Antialiasing);
	
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

bool BlackButton::hitButton(const QPoint&) const
{
	return (true);
}

void AbstractSwitch::mousePressEvent(QMouseEvent *event)
{
	if (event->buttons() & Qt::LeftButton)
		this->setState(!_state);
}

void AbstractSwitch::mouseReleaseEvent(QMouseEvent*)
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

void BlackPushButton::paintEvent(QPaintEvent*)
{
	uint border = this->width() / 6;
	
	_painter.begin(this);
    _painter.setRenderHint(QPainter::Antialiasing);
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

bool BlackPushButton::hitButton(const QPoint&) const
{
	return (true);
}

Switch::Switch(QWidget* parent) :
QCheckBox(parent)
{
    _images[0].load(QString::fromUtf8(u8":/images/switch_off_24px.png"));
    _images[1].load(QString::fromUtf8(u8":/images/switch_on_24px.png"));
}

void Switch::paintEvent(QPaintEvent*)
{
	//float chord = this->width() / 8;
	const QPixmap *pm;
	_painter.begin(this);
	
	/*
	_painter.setBrush(Qt::lightGray);
	_painter.drawConvexPolygon(_poly);
	_painter.drawEllipse(2*chord, 2*chord, 4*chord, 4*chord);
	_painter.setBrush(Qt::white);
	_painter.setPen(Qt::NoPen);*/
	if (this->isChecked())
		pm = &_images[1];
	else
		pm = &_images[0];
	_painter.drawPixmap((this->width()-pm->width()) / 2,
	    (this->height() - pm->height()) / 2, pm->width(), pm->height(), *pm);
	
	_painter.end();
}

void Switch::resizeEvent(QResizeEvent *event)
{
	QCheckBox::resizeEvent(event);
/*	
	uint chord = this->width() / 6;
	
	_poly.clear();
	_poly.append(QPoint(2*chord, chord));
	_poly.append(QPoint(4*chord, chord));
	_poly.append(QPoint(5*chord, 3*chord));
	_poly.append(QPoint(4*chord, 5*chord));
	_poly.append(QPoint(2*chord, 5*chord));
	_poly.append(QPoint(chord, 3*chord));*/
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
	_painter.begin(this);
    _painter.setRenderHint(QPainter::Antialiasing);
	
	QFontMetrics met(this->font());
    double horizontalMargin = (this->width()-met.width(this->text()))/2.0;
    double verticalMargin = (this->height()-met.height())/2.0;

	_painter.setBrush(this->palette().button());
	if (!this->isChecked()) {
		_painter.setPen(Qt::NoPen);
        _painter.drawEllipse(1, 1, this->width()-1, this->height()-1);
    } else {
        _painter.setPen(QPen(this->palette().buttonText().color(),2));
        _painter.drawEllipse(1, 1, this->width()-2, this->height()-2);
    }
	if (!this->isChecked())
		_painter.setPen(this->palette().buttonText().color());
    _painter.drawText(horizontalMargin+0.5, met.height()+verticalMargin-1.5, this->text());
	
	_painter.end();
}

bool DigitButton::hitButton(const QPoint&) const
{
	return (true);
}
