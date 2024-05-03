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

#ifndef INTDELEGATE_H
#define	INTDELEGATE_H

#include <QItemDelegate>
#include <QSpinBox>
#include <QStyleOptionViewItem>

class IntDelegate : public QItemDelegate
{
	Q_OBJECT

	int min;
	int max;
	int step;

public:
	/**
	* Инициализирующий конструктор
	* @param parent родительский объект
	* @param iMin минимальное значение поля
	* @param iMax максимальное значение
	* @param iStep шаг значения
	*/
	IntDelegate(QObject*, int, int, int);
	
	~IntDelegate();

	QWidget* createEditor(QWidget*, const QStyleOptionViewItem&,
	    const QModelIndex&) const;
	void setEditorData(QWidget*, const QModelIndex&) const;
	void setModelData(QWidget*, QAbstractItemModel*, const QModelIndex&) const;
public slots:
	void commitAndCloseEditor();
};

#endif	/* INTDELEGATE_H */

