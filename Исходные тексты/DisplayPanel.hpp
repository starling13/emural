/* 
 * File:   DisplayPanel.hpp
 * Author: starling13
 *
 * Created on 21 Октябрь 2015 г., 15:50
 */

#ifndef _DISPLAYPANEL_HPP
#define	_DISPLAYPANEL_HPP

#include <QtGui/QFrame>
#include <QtGui/QPainter>
#include <QtGui/QBitmap>
#include <qwt/qwt_analog_clock.h>

#include "ural.hpp"

class LampArray : public QWidget
{
	Q_OBJECT
	    
public:
	
	LampArray(const URAL::Word_t&, const QString&, QWidget *parent = NULL);
	
protected :
	
	void paintEvent(QPaintEvent*);
	
private :
	
	const URAL::Word_t	&_value;
	
	QString	_label;
	
	QPainter	_painter;
};

class DisplayPanel : public QFrame
{
	Q_OBJECT
	
public:
	
	DisplayPanel(const URAL::CPU&);
	
	~DisplayPanel();
	
public slots:
	
	void tact();
	
protected:
	
	//void paintEvent(QPaintEvent*) override;
	
	QBitmap		_buffer;
	
	QPainter	_painter;
	
	const URAL::CPU	_ural;
	
	QwtAnalogClock	_clock;
	
	LampArray	_S;
};

#endif	/* _DISPLAYPANEL_HPP */
