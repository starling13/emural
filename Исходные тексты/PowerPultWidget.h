/* 
 * File:   PowerPultWidget.h
 * Author: starling13
 *
 * Created on 1 Ноябрь 2015 г., 0:36
 */

#ifndef _POWERPULTWIDGET_H
#define	_POWERPULTWIDGET_H

#include "ui_PowerPultWidget.h"

class PowerPultWidget : public QWidget
{
	Q_OBJECT
public:
	PowerPultWidget();
	
	~PowerPultWidget();
private:
	Ui::PowerPultWidget widget;
};

#endif	/* _POWERPULTWIDGET_H */
