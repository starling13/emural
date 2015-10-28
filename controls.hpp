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

#ifndef BLASKBUTTON_HPP
#define	BLASKBUTTON_HPP

#include <QWidget>
#include <QPainter>

class BlackButton : public QWidget
{
	Q_OBJECT
	
	Q_PROPERTY(bool state READ state WRITE setState NOTIFY toggled)

signals:

	void toggled(bool);
	
public:
	
	BlackButton(QWidget *parent = NULL);
	
	bool state() const
	{
		return (_state);
	}

public slots:
	
	void setState(bool newVal);
	
	void setChecked(bool);
	
	void setUnckecked(bool);
	
protected:
	
	void paintEvent(QPaintEvent*);
	
	void mousePressEvent(QMouseEvent*);

	void mouseReleaseEvent(QMouseEvent*);
	
private:
	
	QRadialGradient	_gradient;
	QBrush	_solid;
	QPainter	_painter;
	bool	_state;
	bool	_fixed;
};

#endif	/* BLASKBUTTON_HPP */
