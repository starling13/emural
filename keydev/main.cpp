#include "mainwindow.hpp"
#include "controlreaddevice.hpp"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    ControlReadDevice crd;
    KeyDevice w(crd);
    w.show();
    crd.show();

    return a.exec();
}
