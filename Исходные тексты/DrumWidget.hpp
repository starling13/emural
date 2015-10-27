/* 
 * File:   DrumWidget.hpp
 * Author: starling13
 *
 * Created on 27 Октябрь 2015 г., 16:40
 */

#ifndef _DRUMWIDGET_HPP
#define	_DRUMWIDGET_HPP

#include "ui_DrumWidget.h"

#include "ural.hpp"

class DrumWidget : public QWidget
{
	Q_OBJECT
public:
	DrumWidget(URAL::Word_t (&drum)[1024]);
	
	virtual ~DrumWidget();
	
	void resizeEvent(QResizeEvent*) override;

public slots:
	
	void setPosition(int);
	
private slots:
	
	void on_drumScroll_valueChanged(int);
	
	void on_formatGroup_buttonClicked(int);
	
	void on_drumView_cellChanged(int, int);

private:
	
	enum Format { BIN, OCT };
	
	void updateView();
	
	Format	_format;
	
	URAL::Word_t (&_drum)[1024];
	
	size_t _position;
	
	Ui::DrumWidget widget;
};

#endif	/* _DRUMWIDGET_HPP */
