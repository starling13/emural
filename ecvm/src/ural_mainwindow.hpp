#pragma once

#include <QMainWindow>

namespace Ui {
    class MainWindow;
} // namespace Ui

namespace ural
{

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:

    MainWindow();
    ~MainWindow();

private:

    Ui::MainWindow& __ui;
};

} // namespace ural
