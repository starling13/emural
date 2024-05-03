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
