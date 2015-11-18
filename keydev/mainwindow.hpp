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
