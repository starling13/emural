#ifndef PRINTDEVICE_HPP
#define PRINTDEVICE_HPP

#include <QWidget>

#include "ural_cpu.hpp"

namespace Ui {
class PrintDevice;
}

class PrintDevice : public QWidget, public URAL::CPU::IPrintDevice
{
    Q_OBJECT

public:

    PrintDevice(QWidget *parent = 0);

    ~PrintDevice();

public slots:

    void setMode(bool);

    void printWord(quint64) override;

    void printCommand(URAL::HalfWord_t) override;

private:

    QString wordToString(URAL::Word_t);

    Ui::PrintDevice &ui;

    URAL::Format    _mode;

    quint16     _counter;
};

#endif // PRINTDEVICE_HPP
