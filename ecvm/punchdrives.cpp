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

#include "punchdrives.hpp"

#include <QDebug>
#include <ctime>

#include "ui_punchtapewidget.h"

QtPunchDrive::QtPunchDrive() :
	widget(*(new Ui::PunchTapeWidget)),
	_tapePosition(-1),
	_tapeModel(*(new TapeTableModel(*this)))
{
	widget.setupUi(this);
	widget.tapeView->setModel(&_tapeModel);
}

QtPunchDrive::~QtPunchDrive()
{
	delete &_tapeModel;
	delete &widget;
}

void QtPunchDrive::on_loadTapeButton_clicked()
{
	this->loadTapeFromFile();
	this->_tapePosition = 0;
	this->_tapeModel.updateData();
}

URAL::Word_t QtPunchDrive::readWord()
{
	URAL::Word_t	result;

	if (_tapePosition >= 0) {
		URAL::Number number =
		    _tape.tapeData().at(_tapePosition);
		result.quartets.q1 = number.data[10] >> 1;
		result.quartets.q2 = number.data[9];
		result.quartets.q3 = number.data[8];
		result.quartets.q4 = number.data[7];
		result.quartets.q5 = number.data[6];
		result.quartets.q6 = number.data[5];
		result.quartets.q7 = number.data[4];
		result.quartets.q8 = number.data[3];
		result.quartets.q9 = number.data[2];
		if (number.data[1] == 4)
			result.bits.b36 = 1;
		else
			result.bits.b36 = 0;
		if (_tapePosition >= _tape.tapeData().size()-1)
			_tapePosition = 0;
		else
			++_tapePosition;
	}

	return (result);
}

bool QtPunchDrive::readHalfWord(URAL::HalfWord_t &result)
{
	bool res = false;

	if (_tapePosition >= 0) {
		URAL::Number number =
		    _tape.tapeData().at(_tapePosition);
		result.triplets.t1 = number.data[7];
		result.triplets.t2 = number.data[6];
		result.triplets.t3 = number.data[5];
		result.triplets.t4 = number.data[4];
		result.triplets.t5 = number.data[3];
		result.triplets.t6 = number.data[2];
		if (number.data[1] == 4)
			result.bits.b18 = 1;
		else if (number.data[1] == 2)
			result.bits.b18 = 0;
			res = true;
		if (_tapePosition >= _tape.tapeData().size()-1)
			_tapePosition = 0;
		else
			++_tapePosition;
	}

	return (res);
}

QtPunchDrive::TapeTableModel::TapeTableModel(QtPunchDrive &owner) :
	_owner(owner)
{
}

int QtPunchDrive::TapeTableModel::rowCount(const QModelIndex&) const
{
	return (_owner._tape.tapeData().size());
}

int QtPunchDrive::TapeTableModel::columnCount(const QModelIndex&) const
{
	return (2);
}

QVariant QtPunchDrive::TapeTableModel::data(const QModelIndex &index, int role) const
{
	Q_ASSERT(index.row() < _owner._tape.tapeData().size());

	if (role != Qt::DisplayRole)
		return (QVariant());
	switch (index.column()) {
	case int(ZONE) :
		if (_owner._tape.tapeData()[index.row()].data[1] == 2)
			return (QString::fromUtf8(u8"З"));
		else if (_owner._tape.tapeData()[index.row()].data[1] == 4)
			return ('-');
		break;
	case int(NUMBER) : {
		QString res;
		for (size_t i=2; i<11; ++i)
			res.append(QString::number(
			    _owner._tape.tapeData()[index.row()].data[i]));
		return (res);
	}
		break;
	default:
		qWarning() << QString::fromUtf8(u8"Неизвестная графа");
	}
	return (QVariant());
}

QVariant QtPunchDrive::TapeTableModel::headerData(int section,
    Qt::Orientation orientation, int role) const
{
	if (role != Qt::DisplayRole)
		return (QVariant());

	if (orientation == Qt::Horizontal) {
		if (section == ZONE)
			return (QString::fromUtf8(u8"Зона/знак"));
		else if (section == NUMBER)
			return (QString::fromUtf8(u8"Значение"));
	}

	return (QVariant());
}
