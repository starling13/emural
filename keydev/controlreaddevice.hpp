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

#ifndef CONTROLREADDEVICE_HPP
#define CONTROLREADDEVICE_HPP

#include <QWidget>
#include <QMenu>
#include <QPainter>

#include "ural.hpp"
#include "qcommon.hpp"

namespace Ui {
class ControlReadDevice;
}

/**
 * @brief Виджет просмотра перфоленты
 */
class PunchTapeViewWidget : public QWidget
{
	Q_OBJECT

public:

	PunchTapeViewWidget(QWidget *parent = NULL);
	~PunchTapeViewWidget();

	void setTape(URAL::PunchTape*);

public slots:

	void setPosition(int newVal)
	{
		_position = newVal;
		this->update();
	}

protected:

	void paintEvent(QPaintEvent*) override;

private:

	void	drawFrame(size_t);

	URAL::PunchTape	*_tape;
	QPainter	 _painter;
	size_t		 _position;
};

/**
 * @brief Виджет контрольно-считывающего устройства
 */
class ControlReadDevice : public QWidget, public TapeLoader
{
	Q_OBJECT

public:

	ControlReadDevice(QWidget *parent = NULL);

	~ControlReadDevice();

	void punchNumber(URAL::Number);

protected:

	void contextMenuEvent(QContextMenuEvent*) override;

private slots:

	void newTape();
	void loadTape();
	void saveTape();

private:

	Ui::ControlReadDevice	&ui;

	QMenu			 _contextMenu;
};

#endif // CONTROLREADDEVICE_HPP
