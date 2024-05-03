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

#ifndef DELEGATES_HPP
#define DELEGATES_HPP

#include <QItemDelegate>
#include <QStyleOptionViewItem>
#include <QValidator>
#include <QLineEdit>
#include <QKeyEvent>

#include "ural.hpp"

/**
 * Объект LineEdit с нестираемыми символами
 */
class ReplaceLineEdit : public QLineEdit
{
    Q_OBJECT

public:
    ReplaceLineEdit(QWidget *parent=0) : QLineEdit(parent) {}
protected:
    void keyPressEvent(QKeyEvent *event)
    {
        if ((event->key() != Qt::Key_Backspace)
            &&	(event->key() != Qt::Key_Delete))
        QLineEdit::keyPressEvent(event);
    }
};

/**
 * Объект делегат для редактирования bitset<64>
 * @return
 */
class NumberDelegate : public QItemDelegate
{
    Q_OBJECT

public:

   /**
    * Инициализирующий конструктор
    * @param parent родительский объект
    */
    NumberDelegate(int, URAL::Format, QObject*);
    ~NumberDelegate();

    QWidget* createEditor(QWidget*, const QStyleOptionViewItem&, const QModelIndex&) const;
    void setEditorData(QWidget*, const QModelIndex&) const;
    void setModelData(QWidget*, QAbstractItemModel*, const QModelIndex&) const;

public slots:

    void commitAndCloseEditor();

private:

    int _bitCount;

    URAL::Format    _format;

    QString         _mask;

    QValidator      *_validator;
};
#endif // DELEGATES_HPP
