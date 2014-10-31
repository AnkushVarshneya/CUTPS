#ifndef STUDENTFORM_H
#define STUDENTFORM_H

#include <QWidget>
#include "mainwindow.h"

#include <QCloseEvent>

class MainWindow;

namespace Ui {
class StudentForm;
}

class StudentForm : public QWidget
{
    Q_OBJECT

public:
    explicit StudentForm(QWidget *parent = 0);
    ~StudentForm();

    MainWindow *parentForm;

protected:
    void closeEvent(QCloseEvent *event);

private slots:
    void on_backButton_clicked();

    void on_StudentForm_destroyed();

private:
    Ui::StudentForm *ui;


};

#endif // STUDENTFORM_H
