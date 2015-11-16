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

#include "PanelWidget.hpp"
#include "ui_PanelWidget.h"

PanelWidget::PanelWidget(const URAL::CPU &ural) :
widget(*(new Ui::PanelWidget)),
_ural(ural)
{
	widget.setupUi(this);
	
	this->updateRegisters();
}

PanelWidget::~PanelWidget()
{
    delete &widget;
}

void PanelWidget::controlRegisterUpdated()
{
	this->widget.controlRegisterPanel->setValue(_ural.controlRegister().data);
}

void PanelWidget::updateRegisters()
{
	this->widget.controlRegisterPanel->setValue(_ural.controlRegister().data);
	this->widget.adderRegisterPanel->setValue(_ural.S.data);
	this->widget.programCounterPanel->setValue(_ural.regSCHK());
	this->widget.arithmUnitRegisterPanel->setValue(_ural.R.data);
	this->widget.commandRegisterPanel->setValue(_ural._RGK.data);
	this->widget.commandDecoderPanel->setValue(_ural.regDSHK());
	this->widget.statusRegisterPanel->setValue(_ural.statusRegister());
    this->widget.modesPanel->setValue(_ural.statusRegister() >> 8);
}
