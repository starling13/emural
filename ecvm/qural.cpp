#include "qural.hpp"
#include <QThread>
#include <QDebug>

URALWrapper::URALWrapper(URAL::CPU &ural) :
    _ural(ural)
{
    QObject::connect(&_timer, SIGNAL(timeout()), this,
        SLOT(timerSignaled()));
}

void URALWrapper::singleStep()
{
    qDebug() << "Single step" << QThread::currentThreadId();
    _ural.tact();
    qDebug() << "end";
    emit tactFinished();
    emit stopped();
}

void URALWrapper::start()
{
    _timer.start(10);
}

void URALWrapper::stop()
{
    _timer.stop();
}

void URALWrapper::timerSignaled()
{
    if (!_ural.tact()) {
        _timer.stop();
        emit tactFinished();
        emit stopped();
    } else
        emit tactFinished();
}
