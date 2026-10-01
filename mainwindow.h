#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "databasemanager.h"

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui
{
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget* parent = nullptr);
    ~MainWindow() override;

private:
    void updateStatus();

    Ui::MainWindow* ui;
    DatabaseManager databaseManager;
};

#endif // MAINWINDOW_H
