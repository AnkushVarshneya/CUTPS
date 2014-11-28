#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "ContentManagerInterfaceWindow.h"
#include "StudentInterfaceWindow.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_studentInterfaceButton_clicked();

    void on_contentManagerInterfaceButton_clicked();

private:
    Ui::MainWindow *ui;
    ContentManagerInterfaceWindow contentManagerUI;
    StudentInterfaceWindow studentInterface;


};

#endif // MAINWINDOW_H
