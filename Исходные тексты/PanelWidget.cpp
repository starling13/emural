/*
 * File:   PanelWidget.cpp
 * Author: starling13
 *
 * Created on 28 Октябрь 2015 г., 17:51
 */

#include "PanelWidget.hpp"

PanelWidget::PanelWidget(const URAL::CPU &ural) :
_ural(ural)
{
	widget.setupUi(this);
	widget.controlRegisterPanel->setValue(URAL::Word_t());
}

PanelWidget::~PanelWidget()
{
}
