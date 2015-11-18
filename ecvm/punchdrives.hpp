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

#ifndef PUNCHDRIVES_HPP
#define PUNCHDRIVES_HPP

#include "ural.hpp"
#include "qcommon.hpp"

#include <QWidget>
#include <QAbstractTableModel>

namespace Ui {
    class PunchTapeWidget;
} // namespace Ui

class QtPunchDrive : public QWidget, public TapeLoader, public URAL::IExtMemoryDevice
{
	Q_OBJECT

public:

	QtPunchDrive();
	~QtPunchDrive();

	URAL::Word_t	readWord() override;
	bool readHalfWord(URAL::HalfWord_t&) override;

private slots:

	void on_loadTapeButton_clicked();

private:

	Q_DISABLE_COPY(QtPunchDrive)

	class	TapeTableModel;
	friend class	TapeTableModel;

	Ui::PunchTapeWidget	&widget;
	ssize_t			 _tapePosition;
	TapeTableModel		&_tapeModel;
};

class QtPunchDrive::TapeTableModel : public QAbstractTableModel
{
	Q_OBJECT

public:

	TapeTableModel(QtPunchDrive&);

	int rowCount(const QModelIndex&) const override;
	int columnCount(const QModelIndex&) const override;
	QVariant data(const QModelIndex&, int) const override;
	QVariant headerData(int, Qt::Orientation, int) const override;

	void updateData()
	{
		this->reset();
	}

private:

	enum Columns_t
	{
		ZONE = 0,
		NUMBER = 1,
	};

	QtPunchDrive	&_owner;
};

#endif // PUNCHDRIVES_HPP
