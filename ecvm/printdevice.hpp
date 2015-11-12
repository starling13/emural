#ifndef PRINTDEVICE_HPP
#define PRINTDEVICE_HPP

#include <QWidget>

#include "ural.hpp"

namespace Ui {
class PrintDevice;
}

class PrintDevice : public QWidget
{
    Q_OBJECT

public:

    PrintDevice(QWidget *parent = 0);

    ~PrintDevice();

public slots:

    void setMode(bool);

    void printWord(quint64);

private:

    Ui::PrintDevice &ui;

    URAL::Format    _mode;

    quint16     _counter;
};

#endif // PRINTDEVICE_HPP
