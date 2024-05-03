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

#include "intdelegate.hpp"

IntDelegate::IntDelegate(QObject *parent,
        int iMin, int iMax, int iStep) : QItemDelegate(parent),
        min(iMin),
        max(iMax),
        step(iStep)
{

}

IntDelegate::~IntDelegate()
{
}

QWidget *IntDelegate::createEditor(QWidget *parent, const
QStyleOptionViewItem&, const QModelIndex&) const
{
   QSpinBox *edit = new QSpinBox(parent);
   edit->setValue(0);
   edit->setMinimum(min);
   edit->setMaximum(max);
   edit->setSingleStep(step);

   connect(edit, SIGNAL(editingFinished()),
           this, SLOT(commitAndCloseEditor()));

   return edit;
}


void IntDelegate::setEditorData(QWidget *editor, const QModelIndex &index) const
{
	int kk = index.model()->data(index, Qt::DisplayRole).toInt();

	QSpinBox *edit = qobject_cast<QSpinBox*>(editor);
	edit->setValue(kk);
}


void IntDelegate::setModelData(QWidget *editor, QAbstractItemModel *model,
const QModelIndex &index) const
{
	QSpinBox *edit = qobject_cast<QSpinBox*>(editor);
	model->setData(index, QString::number(edit->value()) );
}

void IntDelegate::commitAndCloseEditor()
{
	QSpinBox *editor = qobject_cast<QSpinBox*>(sender());
	emit commitData(editor);
	emit closeEditor(editor);
}
