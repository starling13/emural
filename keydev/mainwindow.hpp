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

private:

    Q_DISABLE_COPY(KeyDevice)

    PunchTape::Number   _number;

    Ui::KeyDevice &ui;

    QVector<QButtonGroup*>   _buttons;

    ControlReadDevice   &_controlRead;
};

#endif // MAINWINDOW_HPP
