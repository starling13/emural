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

#ifndef MAINWINDOW_HPP
#define MAINWINDOW_HPP

#include <QMainWindow>
#include <QVector>

#include "controlreaddevice.hpp"

namespace Ui {
class KeyDevice;
}

class QButtonGroup;

class KeyDevice : public QWidget
{
    Q_OBJECT

public:

    KeyDevice(ControlReadDevice&, QWidget *parent = NULL);

    ~KeyDevice();

private slots:

    void on_keys1group_buttonClicked(int);
    void on_keys2group_buttonClicked(int);
    void on_keys3group_buttonClicked(int);
    void on_keys4group_buttonClicked(int);
    void on_keys5group_buttonClicked(int);
    void on_keys6group_buttonClicked(int);
    void on_keys7group_buttonClicked(int);
    void on_keys8group_buttonClicked(int);
    void on_keys9group_buttonClicked(int);

    void on_andButton_clicked();

    void on_punchButton_clicked();

    void on_zoneButton_clicked();

    void on_returnButton_clicked();

    void on_minusButton_clicked();

private:

    Q_DISABLE_COPY(KeyDevice)

    URAL::Number   _number;

    Ui::KeyDevice &ui;

    QVector<QButtonGroup*>   _buttons;

    ControlReadDevice   &_controlRead;
};

#endif // MAINWINDOW_HPP
