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

#ifndef _PULTWIDGET_HPP
#define	_PULTWIDGET_HPP

#include "ui_PultWIdget.h"

#include <QTimer>

#include "controls.hpp"
#include "ural.hpp"

class PultWIdget : public QWidget
{
	Q_OBJECT
	
signals:

	void tactFinished();

    void stopped();
	
public:
	
	PultWIdget(URAL::CPU&);
	
	~PultWIdget();
	
private slots:
	
	void on_singleStepButton_clicked();
	
	void on_resetButton_clicked();
	
	void on_startButton_clicked();
	
	void on_stopButton_clicked();
	
	void on_commandResetButton_clicked();
	
	void on_commandSetButton_clicked();
	
	void on_addr1group_buttonClicked(int);
	
	void on_addr2group_buttonClicked(int);
	
	void on_addr3group_buttonClicked(int);
	
	void on_addr4group_buttonClicked(int);
	
	void on_addr5group_buttonClicked(int);
	
	void on_addr6group_buttonClicked(int);

    void on_reg8group_buttonClicked(int);

    void on_reg9group_buttonClicked(int);

    void on_reg10group_buttonClicked(int);

    void on_reg11group_buttonClicked(int);

    void on_reg12group_buttonClicked(int);

    void on_adderSetButton_clicked();

    void on_adderResetButton_clicked();
	
	void timerSignaled();
	
private:
	
	uint8_t _tactSkip;
	
	Ui::PultWIdget widget;
	
	URAL::CPU	&_ural;
	
	QTimer		_timer;
	
	URAL::HalfWord_t	_commandWord;

    URAL::Word_t        _adderWord;
	
	QVector<QButtonGroup*>	_commandButtons;

    QVector<QButtonGroup*>	_adderButtons;
};

#endif	/* _PULTWIDGET_HPP */
