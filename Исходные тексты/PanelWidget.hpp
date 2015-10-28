/* 
 * File:   PanelWidget.hpp
 * Author: starling13
 *
 * Created on 28 Октябрь 2015 г., 17:51
 */

#ifndef _PANELWIDGET_HPP
#define	_PANELWIDGET_HPP

#include "ui_PanelWidget.h"

#include "ural.hpp"

class PanelWidget : public QWidget
{
	Q_OBJECT
	
public:
	
	PanelWidget(const URAL::CPU&);
	
	~PanelWidget();
	
private:
	
	Ui::PanelWidget widget;
	
	const URAL::CPU &_ural;
};

#endif	/* _PANELWIDGET_HPP */
