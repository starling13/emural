#include "printdevice.hpp"
#include "ui_printdevice.h"

#include <unistd.h>

#include <QDebug>

QtPrintDevice::Worker::Worker(QtPrintDevice &owner) :
    _owner(owner)
{
}

void QtPrintDevice::Worker::run()
{
    while (true) {
        qDebug() << "Worker locking";
        QMutexLocker    locker(&_owner._cpuLock);
        qDebug() << "Worker locked";

        qDebug() << "Wait" << _owner._buffer;
        while (_owner._buffer.isEmpty())
            _owner._cpuCondition.wait(&_owner._cpuLock);
        qDebug() << "Received" << _owner._buffer;
        emit print(_owner._buffer);

        int elapsed = _owner._startTime.elapsed();
        if (elapsed < 600)
            QThread::msleep(600-elapsed);
        _owner._buffer = "";
        _owner._uralCondition.wakeAll();
    }
}

QtPrintDevice::QtPrintDevice(QWidget *parent) :
    QWidget(parent),
    ui(*(new Ui::PrintDevice)),
    _mode(URAL::DEC),
    _counter(0),
    _worker(*(new Worker(*this)))
{
    ui.setupUi(this);

    QObject::connect(&_worker, SIGNAL(print(QString)), this, SLOT(printBuffer(QString)),
        Qt::QueuedConnection);
}

QtPrintDevice::~QtPrintDevice()
{
    _worker.terminate();
    while (_worker.isRunning());

    delete &_worker;
    delete &ui;
}

void QtPrintDevice::start()
{
    _worker.start();
}

void QtPrintDevice::setMode(bool newVal)
{
    if (newVal)
        _mode = URAL::OCT;
    else
        _mode = URAL::DEC;
}

void QtPrintDevice::printBuffer(QString buffer)
{
     ui.textArea->appendPlainText(buffer);
}

void QtPrintDevice::printWord(URAL::Word_t word)
{
    QMutexLocker    locker(&_cpuLock);
    _startTime.start();

    Q_ASSERT(_buffer.isEmpty());
    _buffer = QString('\t').append(wordToString(word));
    _cpuCondition.wakeAll();

    while (!_buffer.isEmpty())
        _uralCondition.wait(&_cpuLock);
    qDebug() << "Sent" << _buffer;
}

void QtPrintDevice::printCommand(quint16 addr, URAL::HalfWord_t command)
{
    QMutexLocker    locker(&_cpuLock);
    _startTime.start();

    Q_ASSERT(_buffer.isEmpty());
    for (int i=9; i>=0; i-=3)
        _buffer.append(QString::number((addr >> i)&7));
    _buffer.append('\t').append(commandToString(command));
    _cpuCondition.wakeAll();

    while (!_buffer.isEmpty())
        _uralCondition.wait(&_cpuLock);
    qDebug() << "Sent" << _buffer;
}

QString QtPrintDevice::wordToString(URAL::Word_t word)
{
    QString         buf;

    if (_mode == URAL::OCT) {
        buf.append(QString::number(word.triplets.t12));
        buf.append(QString::number(word.triplets.t11));
        buf.append(QString::number(word.triplets.t10));
        buf.append(QString::number(word.triplets.t9));
        buf.append(QString::number(word.triplets.t8));
        buf.append(QString::number(word.triplets.t7));
        buf.append(' ');
        buf.append(QString::number(word.triplets.t6));
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
        buf.append(QString::number(word.quartets.q9 % 10));
        buf.append(QString::number(word.quartets.q8 % 10));
        buf.append(QString::number(word.quartets.q7 % 10));
        buf.append(QString::number(word.quartets.q6 % 10));
        buf.append(QString::number(word.quartets.q5 % 10));
        buf.append(QString::number(word.quartets.q4 % 10));
        buf.append(QString::number(word.quartets.q3 % 10));
        buf.append(QString::number(word.quartets.q2 % 10));
        buf.append(QString::number(word.quartets.q1 * 2 % 10));
    }

    return (buf);
}

QString QtPrintDevice::commandToString(URAL::HalfWord_t command)
{
    QString buf;

    if (command.command.indexFlag)
        buf.append('-');
    else
        buf.append(' ');

    buf.append(QString::number((command.command.opCode >> 3) & 7));
    buf.append(QString::number(command.command.opCode & 7));
    buf.append(' ');
    buf.append(QString::number(command.triplets.t4 & 3));
    buf.append(QString::number(command.triplets.t3));
    buf.append(QString::number(command.triplets.t2));
    buf.append(QString::number(command.triplets.t1));

    return (buf);
}
