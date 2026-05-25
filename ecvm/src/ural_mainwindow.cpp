#include "ural_mainwindow.hpp"

#include "ui_mainwindow.h"

namespace ural
{

MainWindow::MainWindow() :
    __ui(*(new Ui::MainWindow))
{
}

MainWindow::~MainWindow()
{
}

} // namespace ural
