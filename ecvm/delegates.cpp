/*
 * This file is part of EMURAL - emulator for Ural computer from 1950s
 * Copyright (C) 2015-2024 Andrey V. Skvortsov <starling13@gmail.com>
 *
 * EMURAL is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "delegates.hpp"

#include <QDebug>

NumberDelegate::NumberDelegate(int bitCount, URAL::Format format, QObject *parent) :
	QItemDelegate(parent),
	_bitCount(bitCount),
	_format(format)
{
	switch (_format) {
	case URAL::BIN :
		_mask.fill('B', _bitCount);
		_validator = new QRegExpValidator(QRegExp(QString("[01]{%1}").arg(
								  _bitCount)), this);
		break;
	case URAL::OCT :
		_mask.fill('9', _bitCount / 3);
		_validator = new QRegExpValidator(QRegExp(QString("[0-7]{%1}").arg(
								  _bitCount / 3)), this);
		break;
	case URAL::DEC :
		_mask.fill('9', _bitCount / 4);
		_validator = new QRegExpValidator(QRegExp(QString("[0-9]{%1}").arg(
								  _bitCount / 4)), this);
		break;
	}
}

NumberDelegate::~NumberDelegate()
{

}

QWidget *NumberDelegate::createEditor(QWidget *parent, const QStyleOptionViewItem &,
	const QModelIndex &) const
{
	ReplaceLineEdit *edit = new ReplaceLineEdit(parent);
	edit->setInputMask(_mask);
	QObject::connect(edit, SIGNAL(editingFinished()), this, SLOT(commitAndCloseEditor()));
	edit->setValidator(_validator);
	return (edit);
}

void NumberDelegate::setEditorData(QWidget *editor, const QModelIndex &index) const
{
	QString str = index.model()->data(index, Qt::DisplayRole).toString();
	ReplaceLineEdit *edit = qobject_cast<ReplaceLineEdit*>(editor);
	edit->setText(str);
}

void NumberDelegate::setModelData(QWidget *editor, QAbstractItemModel *model,
	const QModelIndex &index) const
{
	ReplaceLineEdit *edit = qobject_cast<ReplaceLineEdit*>(editor);
	model->setData(index, edit->text());
	qDebug() << edit->text();
}

void NumberDelegate::commitAndCloseEditor()
{
	ReplaceLineEdit *editor = qobject_cast<ReplaceLineEdit*>(sender());
	emit commitData(editor);
	emit closeEditor(editor);
}
