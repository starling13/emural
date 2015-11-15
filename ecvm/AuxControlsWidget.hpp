/*
 *   Данная программа является свободным программным обеспечением. Вы
 *   вправе распространять её и/или модифицировать в соответствии с
 *   условиями версии 2, либо по вашему выбору с условиями более поздней
 *   версии Стандартной Общественной Лицензии GNU, опубликованной Free
 *   Software Foundation.

 *   Мы распространяем данную программу в надежде на то, что она будет
 *   вам полезной, однако НЕ ПРЕДОСТАВЛЯЕМ НА НЕЁ НИКАКИХ ГАРАНТИЙ, в том
 *   числе ГАРАНТИИ ТОВАРНОГО СОСТОЯНИЯ ПРИ ПРОДАЖЕ и ПРИГОДНОСТИ ДЛЯ
 *   ИСПОЛЬЗОВАНИЯ В КОНКРЕТНЫХ ЦЕЛЯХ. Для получения более подробной
 *   информации ознакомьтесь со Стандартной Общественной Лицензией GNU.

 *   Вместе с данной программой вы должны были получить экземпляр
 *   Стандартной Общественной Лицензии GNU. Если вы его не получили,
 *   сообщите об этом в Free Software Foundation, Inc.,
 *   51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
 */

#ifndef _AUXCONTROLSWIDGET_HPP
#define	_AUXCONTROLSWIDGET_HPP

#include "ural_cpu.hpp"

#include "ui_AuxControlsWidget.h"

class AuxControlsWidget : public QWidget
{
	Q_OBJECT

signals:	
	
	void controlRegisterAddressChanged(size_t);

    void printMode(bool);

public:
	
	AuxControlsWidget(URAL::CPU&);
	
	~AuxControlsWidget();
	
private slots:
	
	void on_controlRegisterGroup_buttonClicked(QAbstractButton*);
	
	void on_addressBlockGroup_buttonClicked(QAbstractButton*);
    
    void on_controlSwitchGroup_buttonClicked(QAbstractButton*);
	
	void on_blockPhiBtn_toggled(bool);
	
	void on_stopOnPhiBtn_toggled(bool);

    void on_prinAdderBtn_clicked();

    void on_printModeSwitch_toggled(bool);

    void on_printMode1_toggled(bool);

    void on_printMode2_toggled(bool);
	
private:
	
	Ui::AuxControlsWidget	 widget;
	
	uint16_t		_controlRegisterPosition;
	
	uint16_t		_addrStopRegister;
    
    u_int8_t        _controlSwitchRegister;
	
	URAL::CPU		&_ural;
};

#endif	/* _AUXCONTROLSWIDGET_HPP */
