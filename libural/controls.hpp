/*
 *   emural - эмулятор ЭЦВМ семейства "Урал"
 *
 *   Copyright (C) 2015-2019 А.В. Скворцов <starling13@gmail.com>
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

#ifndef BLASKBUTTON_HPP
#define	BLASKBUTTON_HPP

#include <QWidget>
#include <QRadioButton>
#include <QPushButton>
#include <QCheckBox>
#include <QPainter>

class AbstractSwitch : public QWidget
{
	Q_OBJECT
	
	Q_PROPERTY(bool state READ state WRITE setState NOTIFY toggled)

signals:

	void toggled(bool);
	
public:
	
	AbstractSwitch(QWidget *parent = NULL);
	
	bool state() const
	{
		return (_state);
	}

public slots:
	
	void setState(bool newVal);
	
	void setChecked(bool);
	
	void setUnckecked(bool);
	
protected:
	
	void mousePressEvent(QMouseEvent*) override;

	void mouseReleaseEvent(QMouseEvent*) override;
	
private:
	
	bool	_state;
	bool	_fixed;
};

class BlackButton : public QRadioButton
{
	Q_OBJECT
	    
public:
	
	BlackButton(QWidget *parent = NULL);
	
protected:
	
	void paintEvent(QPaintEvent*) override;

	bool hitButton(const QPoint&) const override;

private:
	
	QRadialGradient	_gradient;
	QBrush	_solid;
	QPainter	_painter;
};

class BlackPushButton : public QPushButton
{
	Q_OBJECT
	    
public:
	
	BlackPushButton(QWidget *parent = 0);
	
protected:
	
	void paintEvent(QPaintEvent*) override;

	bool hitButton(const QPoint& pos) const override;

private:
	
	QRadialGradient	_gradient;
	QPainter	_painter;
};

class Switch : public QCheckBox
{
	Q_OBJECT
	    
public:
	
	Switch(QWidget *parent = NULL);
	
protected:

	bool hitButton(const QPoint& pos) const override;

	void paintEvent(QPaintEvent*) override;
	
	void resizeEvent(QResizeEvent*) override;
	
private:
	
	QPixmap		_images[2];
	
	QPainter	_painter;
};

class DigitButton : public QRadioButton
{
	Q_OBJECT
	    
public:
	
	DigitButton(QWidget *parent = NULL);
	
protected:
	
	void paintEvent(QPaintEvent*) override;
	
	bool hitButton(const QPoint& pos) const override;
	
private:
	
	QBrush		_brush;
	QPainter	_painter;
};

#endif	/* BLASKBUTTON_HPP */
