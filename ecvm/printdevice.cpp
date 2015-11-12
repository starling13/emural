#include "printdevice.hpp"
#include "ui_printdevice.h"

PrintDevice::PrintDevice(QWidget *parent) :
    QWidget(parent),
    ui(*(new Ui::PrintDevice)),
    _mode(URAL::DEC),
    _counter(0)
{
    ui.setupUi(this);
}

PrintDevice::~PrintDevice()
{
    delete &ui;
}

void PrintDevice::setMode(bool newVal)
{
    if (newVal)
        _mode = URAL::OCT;
    else
        _mode = URAL::DEC;
}

void PrintDevice::printWord(quint64 newVal)
{
    URAL::Word_t    word;

    word.data = newVal;

    ui.textArea->appendPlainText(QString('\t').append(wordToString(word)));
}

QString PrintDevice::wordToString(URAL::Word_t word)
{
    QString         buf;

    if (_mode == URAL::OCT) {
        buf.append(QString::number(word.triplets.t12));
        buf.append(QString::number(word.triplets.t10));
        buf.append(QString::number(word.triplets.t9));
        buf.append(QString::number(word.triplets.t8));
        buf.append(QString::number(word.triplets.t7));
        buf.append(QString::number(word.triplets.t6));
        buf.append(' ');
        buf.append(QString::number(word.triplets.t5));
        buf.append(QString::number(word.triplets.t4));
        buf.append(QString::number(word.triplets.t3));
        buf.append(QString::number(word.triplets.t2));
        buf.append(QString::number(word.triplets.t1));
    } else {
        if (word.dPrec.sign())
            buf.append('-');
        else
            buf.append(' ');
        buf.append(QString::number(word.quartets.q9));
        buf.append(QString::number(word.quartets.q8));
        buf.append(QString::number(word.quartets.q7));
        buf.append(QString::number(word.quartets.q6));
        buf.append(QString::number(word.quartets.q5));
        buf.append(QString::number(word.quartets.q4));
        buf.append(QString::number(word.quartets.q3));
        buf.append(QString::number(word.quartets.q2));
        buf.append(QString::number(word.quartets.q1 * 2));
    }

    return (buf);
}
