#ifndef PRINTDEVICE_HPP
#define PRINTDEVICE_HPP

#include "ural_cpu.hpp"

#include <QWidget>
#include <QMetaType>
#include <QThread>
#include <QMutex>
#include <QWaitCondition>
#include <QTime>

Q_DECLARE_METATYPE(URAL::Word_t);
Q_DECLARE_METATYPE(URAL::HalfWord_t);

namespace Ui {
class PrintDevice;
}

class QtPrintDevice : public QWidget, public URAL::IPrintDevice
{
    Q_OBJECT

public:

    QtPrintDevice(QWidget *parent = 0);
    ~QtPrintDevice();

    void start();
    void printWord(URAL::Word_t) override;
    void printCommand(quint16, URAL::HalfWord_t) override;

public slots:

    void setMode(bool);

private slots:

    void printBuffer(QString);

private:

    QString wordToString(URAL::Word_t);
    QString commandToString(URAL::HalfWord_t);

    class Worker;
    friend class Worker;

    QMutex               _cpuLock;
    QWaitCondition       _uralCondition,    _cpuCondition;
    Ui::PrintDevice     &ui;
    URAL::Format         _mode;
    quint16              _counter;
    Worker              &_worker;
    QTime               _startTime;
    QString             _buffer;
};

class QtPrintDevice::Worker : public QThread
{
    Q_OBJECT

signals:

    void print(QString);

public:

    Worker(QtPrintDevice&);

protected:

    void run() override;

private:

    QtPrintDevice   &_owner;

};

#endif // PRINTDEVICE_HPP
