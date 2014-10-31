#ifndef CONTENTMANAGERFORM_H
#define CONTENTMANAGERFORM_H

#include <QWidget>
#include "mainwindow.h"

#include <QCloseEvent>

class MainWindow;

namespace Ui {
class ContentManagerForm;
}

class ContentManagerForm : public QWidget
{
    Q_OBJECT

public:
    explicit ContentManagerForm(QWidget *parent = 0);
    ~ContentManagerForm();

    MainWindow *parentForm;

protected:
    void closeEvent(QCloseEvent *event);

private slots:
    void on_backButton_clicked();

private:
    Ui::ContentManagerForm *ui;
};

#endif // CONTENTMANAGERFORM_H
