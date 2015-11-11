#include "mainwindow.hpp"
#include "ui_mainwindow.h"

KeyDevice::KeyDevice(ControlReadDevice &crd, QWidget *parent) :
    QWidget(parent),
    ui(*(new Ui::KeyDevice)),
    _controlRead(crd)
{
    ui.setupUi(this);

    _buttons.push_back(this->ui.keys1group);
    _buttons.push_back(this->ui.keys2group);
    _buttons.push_back(this->ui.keys3group);
    _buttons.push_back(this->ui.keys4group);
    _buttons.push_back(this->ui.keys5group);
    _buttons.push_back(this->ui.keys6group);
    _buttons.push_back(this->ui.keys7group);
    _buttons.push_back(this->ui.keys8group);

    this->ui.keys1group->setId(this->ui.reg1_0button, 0);
    this->ui.keys1group->setId(this->ui.reg1_1button, 1);
    this->ui.keys1group->setId(this->ui.reg1_2button, 2);
    this->ui.keys1group->setId(this->ui.reg1_3button, 3);
    this->ui.keys1group->setId(this->ui.reg1_4button, 4);
    this->ui.keys1group->setId(this->ui.reg1_5button, 5);
    this->ui.keys1group->setId(this->ui.reg1_6button, 6);
    this->ui.keys1group->setId(this->ui.reg1_7button, 7);
    this->ui.keys1group->setId(this->ui.reg1_8button, 8);
    this->ui.keys1group->setId(this->ui.reg1_9button, 9);

    this->ui.keys2group->setId(this->ui.reg2_0button, 0);
    this->ui.keys2group->setId(this->ui.reg2_1button, 1);
    this->ui.keys2group->setId(this->ui.reg2_2button, 2);
    this->ui.keys2group->setId(this->ui.reg2_3button, 3);
    this->ui.keys2group->setId(this->ui.reg2_4button, 4);
    this->ui.keys2group->setId(this->ui.reg2_5button, 5);
    this->ui.keys2group->setId(this->ui.reg2_6button, 6);
    this->ui.keys2group->setId(this->ui.reg2_7button, 7);
    this->ui.keys2group->setId(this->ui.reg2_8button, 8);
    this->ui.keys2group->setId(this->ui.reg2_9button, 9);

    this->ui.keys3group->setId(this->ui.reg3_0button, 0);
    this->ui.keys3group->setId(this->ui.reg3_1button, 1);
    this->ui.keys3group->setId(this->ui.reg3_2button, 2);
    this->ui.keys3group->setId(this->ui.reg3_3button, 3);
    this->ui.keys3group->setId(this->ui.reg3_4button, 4);
    this->ui.keys3group->setId(this->ui.reg3_5button, 5);
    this->ui.keys3group->setId(this->ui.reg3_6button, 6);
    this->ui.keys3group->setId(this->ui.reg3_7button, 7);
    this->ui.keys3group->setId(this->ui.reg3_8button, 8);
    this->ui.keys3group->setId(this->ui.reg3_9button, 9);

    this->ui.keys4group->setId(this->ui.reg4_0button, 0);
    this->ui.keys4group->setId(this->ui.reg4_1button, 1);
    this->ui.keys4group->setId(this->ui.reg4_2button, 2);
    this->ui.keys4group->setId(this->ui.reg4_3button, 3);
    this->ui.keys4group->setId(this->ui.reg4_4button, 4);
    this->ui.keys4group->setId(this->ui.reg4_5button, 5);
    this->ui.keys4group->setId(this->ui.reg4_6button, 6);
    this->ui.keys4group->setId(this->ui.reg4_7button, 7);
    this->ui.keys4group->setId(this->ui.reg4_8button, 8);
    this->ui.keys4group->setId(this->ui.reg4_9button, 9);

    this->ui.keys5group->setId(this->ui.reg5_0button, 0);
    this->ui.keys5group->setId(this->ui.reg5_1button, 1);
    this->ui.keys5group->setId(this->ui.reg5_2button, 2);
    this->ui.keys5group->setId(this->ui.reg5_3button, 3);
    this->ui.keys5group->setId(this->ui.reg5_4button, 4);
    this->ui.keys5group->setId(this->ui.reg5_5button, 5);
    this->ui.keys5group->setId(this->ui.reg5_6button, 6);
    this->ui.keys5group->setId(this->ui.reg5_7button, 7);
    this->ui.keys5group->setId(this->ui.reg5_8button, 8);
    this->ui.keys5group->setId(this->ui.reg5_9button, 9);

    this->ui.keys6group->setId(this->ui.reg6_0button, 0);
    this->ui.keys6group->setId(this->ui.reg6_1button, 1);
    this->ui.keys6group->setId(this->ui.reg6_2button, 2);
    this->ui.keys6group->setId(this->ui.reg6_3button, 3);
    this->ui.keys6group->setId(this->ui.reg6_4button, 4);
    this->ui.keys6group->setId(this->ui.reg6_5button, 5);
    this->ui.keys6group->setId(this->ui.reg6_6button, 6);
    this->ui.keys6group->setId(this->ui.reg6_7button, 7);
    this->ui.keys6group->setId(this->ui.reg6_8button, 8);
    this->ui.keys6group->setId(this->ui.reg6_9button, 9);

    this->ui.keys7group->setId(this->ui.reg7_0button, 0);
    this->ui.keys7group->setId(this->ui.reg7_1button, 1);
    this->ui.keys7group->setId(this->ui.reg7_2button, 2);
    this->ui.keys7group->setId(this->ui.reg7_3button, 3);
    this->ui.keys7group->setId(this->ui.reg7_4button, 4);
    this->ui.keys7group->setId(this->ui.reg7_5button, 5);
    this->ui.keys7group->setId(this->ui.reg7_6button, 6);
    this->ui.keys7group->setId(this->ui.reg7_7button, 7);
    this->ui.keys7group->setId(this->ui.reg7_8button, 8);
    this->ui.keys7group->setId(this->ui.reg7_9button, 9);

    this->ui.keys8group->setId(this->ui.reg8_0button, 0);
    this->ui.keys8group->setId(this->ui.reg8_1button, 1);
    this->ui.keys8group->setId(this->ui.reg8_2button, 2);
    this->ui.keys8group->setId(this->ui.reg8_3button, 3);
    this->ui.keys8group->setId(this->ui.reg8_4button, 4);
    this->ui.keys8group->setId(this->ui.reg8_5button, 5);
    this->ui.keys8group->setId(this->ui.reg8_6button, 6);
    this->ui.keys8group->setId(this->ui.reg8_7button, 7);
    this->ui.keys8group->setId(this->ui.reg8_8button, 8);
    this->ui.keys8group->setId(this->ui.reg8_9button, 9);

    this->ui.keys9group->setId(this->ui.reg9_0button, 0);
    this->ui.keys9group->setId(this->ui.reg9_1button, 1);
    this->ui.keys9group->setId(this->ui.reg9_2button, 2);
    this->ui.keys9group->setId(this->ui.reg9_3button, 3);
    this->ui.keys9group->setId(this->ui.reg9_4button, 4);
    this->ui.keys9group->setId(this->ui.reg9_5button, 5);
    this->ui.keys9group->setId(this->ui.reg9_6button, 6);
    this->ui.keys9group->setId(this->ui.reg9_7button, 7);
    this->ui.keys9group->setId(this->ui.reg9_8button, 8);
    this->ui.keys9group->setId(this->ui.reg9_9button, 9);
}

KeyDevice::~KeyDevice()
{
    delete &ui;
}

void KeyDevice::on_keys1group_buttonClicked(int value)
{
    _number.data[10] = value;
}

void KeyDevice::on_keys2group_buttonClicked(int value)
{
    _number.data[9] = value;
}

void KeyDevice::on_keys3group_buttonClicked(int value)
{
    _number.data[8] = value;
}

void KeyDevice::on_keys4group_buttonClicked(int value)
{
    _number.data[7] = value;
}

void KeyDevice::on_keys5group_buttonClicked(int value)
{
    _number.data[6] = value;
}

void KeyDevice::on_keys6group_buttonClicked(int value)
{
    _number.data[5] = value;
}

void KeyDevice::on_keys7group_buttonClicked(int value)
{
    _number.data[4] = value;
}

void KeyDevice::on_keys8group_buttonClicked(int value)
{
    _number.data[3] = value;
}

void KeyDevice::on_keys9group_buttonClicked(int value)
{
    _number.data[2] = value;
}

void KeyDevice::on_andButton_clicked()
{
    _number.data[0] = 8;
}

void KeyDevice::on_punchButton_clicked()
{
    _controlRead.punchNumber(_number);
}
