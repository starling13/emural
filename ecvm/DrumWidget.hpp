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

#ifndef _DRUMWIDGET_HPP
#define	_DRUMWIDGET_HPP

#include "ui_DrumWidget.h"

#include "ural.hpp"

class DrumWidget : public QWidget
{
	Q_OBJECT
public:
	
	DrumWidget(URAL::Word_t (&drum)[URAL::drumWordsNumber]);
	
	~DrumWidget();
	
	void resizeEvent(QResizeEvent*) override;

public slots:
	
	void setPosition(int);

    void updateView();
	
private slots:
	
	void on_drumScroll_valueChanged(int);
	
	void on_formatGroup_buttonClicked(int);
	
	void on_drumView_cellChanged(int, int);
	
	void on_clearButton_clicked();

private:

    QString formatValue(quint64);
	
    URAL::Format	_format;
	
	URAL::Word_t (&_drum)[URAL::drumWordsNumber];
	
	size_t _position;
	
	Ui::DrumWidget widget;
};

#endif	/* _DRUMWIDGET_HPP */
