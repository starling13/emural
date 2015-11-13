#ifndef QURAL_HPP
#define QURAL_HPP

#include "ural_cpu.hpp"
#include <QObject>
#include <QTimer>

class URALWrapper : public QObject
{
    Q_OBJECT

public:

    URALWrapper(URAL::CPU&);

signals:

    void stopped();

    void tactFinished();

public slots:

    void singleStep();

    void start();

    void stop();

private slots:

    void timerSignaled();

private:

    URAL::CPU   &_ural;

    QTimer		_timer;
};

#endif // QURAL_HPP
